/*
 * Copyright (c) 2010-2011 The University of Texas at Austin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"
#include "netrace.h"

#define L2_LATENCY 8

unsigned long long int calc_packet_timing( nt_packet_t* );

nt_header_t* header;
nt_context_t* ctx;
int x_nodes, y_nodes;
unsigned long long int cycle;

typedef struct queue_node queue_node_t;
struct queue_node {
	nt_packet_t* packet;
	unsigned long long int cycle;
};

int main( int argc, char** argv ) {

	int i;
	int ignore_dependencies = 0;
	int start_region = 0;
	int reader_throttling = 0;
	char* tracefile;
	if( argc > 1 ) {
		tracefile = argv[1];
		for( i = 2; i < argc; ++i ) {
			if( strcmp(argv[i], "-d") == 0 ) {
				ignore_dependencies = 1;
			} else if( strcmp(argv[i], "-r") == 0 ) {
				if( argc > ++i ) {
					start_region = atoi(argv[i]);
				} else {
					fprintf( stderr, "ERROR: Need to specify parameter to -r option\n" );
					exit(0);
				}
			} else if( strcmp(argv[i], "-t") == 0 ) {
				reader_throttling = 1;
			} else {
				fprintf( stderr, "ERROR: Unknown parameter %s\n", argv[i] );
				exit(0);
			}
		}
	} else {
		printf( "ERROR: Please specify trace file\n" );
		exit(0);
	}

	int packets_left = 0;
	cycle = 0;
	nt_packet_t* trace_packet = NULL;
	nt_packet_t* packet = NULL;
	queue_t** waiting;
	queue_t** inject;
	queue_t** traverse;
	ctx = calloc( 1, sizeof(nt_context_t) );
	nt_open_trfile( ctx, tracefile );
	if( ignore_dependencies ) {
		nt_disable_dependencies( ctx );
	}
	nt_print_trheader( ctx );
	header = nt_get_trheader( ctx );
	nt_seek_region( ctx, &header->regions[start_region] );
	for( i = 0; i < start_region; i++ ) {
		cycle += header->regions[i].num_cycles;
	}

	x_nodes = sqrt( header->num_nodes );
	y_nodes = header->num_nodes / x_nodes;
	waiting = (queue_t**) malloc( header->num_nodes * sizeof(queue_t*) );
	inject = (queue_t**) malloc( header->num_nodes * sizeof(queue_t*) );
	traverse = (queue_t**) malloc( header->num_nodes * sizeof(queue_t*) );
	if( (waiting == NULL) || (inject == NULL) || (traverse == NULL) ) {
		printf( "malloc fail queues\n" );
		exit(0);
	}
	for( i = 0; i < header->num_nodes; ++i ) {
		waiting[i] = queue_new();
		inject[i] = queue_new();
		traverse[i] = queue_new();
	}

	if( !reader_throttling ) {
		trace_packet = nt_read_packet( ctx );
	} else if( !ignore_dependencies ) {
		nt_init_self_throttling( ctx );
	}

	while( ( cycle <= header->num_cycles ) || packets_left ) {

		// Reset packets remaining check
		packets_left = 0;

		// Get packets for this cycle
		if( reader_throttling ) {
			nt_packet_list_t* list;
			for( list = nt_get_cleared_packets_list( ctx ); list != NULL; list = list->next ) {
				if( list->node_packet != NULL ) {
					trace_packet = list->node_packet;
					queue_node_t* new_node = (queue_node_t*) nt_checked_malloc( sizeof(queue_node_t) );
					new_node->packet = trace_packet;
					new_node->cycle = (trace_packet->cycle > cycle) ? trace_packet->cycle : cycle;
					queue_push( inject[trace_packet->src], new_node, new_node->cycle );
				} else {
					printf( "Malformed packet list" );
					exit(-1);
				}
			}
			nt_empty_cleared_packets_list( ctx );
		} else {
			while( (trace_packet != NULL) && (trace_packet->cycle == cycle) ) {
				// Place in appropriate queue
				queue_node_t* new_node = (queue_node_t*) nt_checked_malloc( sizeof(queue_node_t) );
				new_node->packet = trace_packet;
				new_node->cycle = (trace_packet->cycle > cycle) ? trace_packet->cycle : cycle;
				if( ignore_dependencies || nt_dependencies_cleared( ctx, trace_packet ) ) {
					// Add to inject queue
					queue_push( inject[trace_packet->src], new_node, new_node->cycle );
				} else {
					// Add to waiting queue
					queue_push( waiting[trace_packet->src], new_node, new_node->cycle );
				}
				// Get another packet from trace
				trace_packet = nt_read_packet( ctx );
			}
			if( (trace_packet != NULL) && (trace_packet->cycle < cycle) ) {
				// Error check: Crash and burn
				printf( "Invalid trace_packet cycle time: %llu, current cycle: %llu\n", trace_packet->cycle, cycle );
				exit(-1);
			}
		}

		// Inject where possible (max one per node)
		for( i = 0; i < header->num_nodes; ++i ) {
			packets_left |= !queue_empty( inject[i] );
			queue_node_t* temp_node = queue_peek_front( inject[i] );
			if( temp_node != NULL ) {
				packet = temp_node->packet;
				if( (packet != NULL) && (temp_node->cycle <= cycle) ) {
					printf( "Inject: %llu ", cycle );
					nt_print_packet( packet );
					temp_node = queue_pop_front( inject[i] );
					temp_node->cycle = cycle + calc_packet_timing( packet );
					queue_push( traverse[packet->dst], temp_node, temp_node->cycle );
				}
			}
		}

		// Step all network components, Eject where possible
		for( i = 0; i < header->num_nodes; ++i ) {
			packets_left |= !queue_empty( traverse[i] );
			queue_node_t* temp_node = queue_peek_front( traverse[i] );
			if( temp_node != NULL ) {
				packet = temp_node->packet;
				if( (packet != NULL) && (temp_node->cycle <= cycle) ) {
					printf( "Eject: %llu ", cycle );
					nt_print_packet( packet );
					nt_clear_dependencies_free_packet( ctx, packet );
					temp_node = queue_pop_front( traverse[i] );
					free( temp_node );
				}
			}
		}

		// Check for cleared dependences... or not
		if( !reader_throttling ) {
			for( i = 0; i < header->num_nodes; ++i ) {
				packets_left |= !queue_empty( waiting[i] );
				node_t* temp = waiting[i]->head;
				while( temp != NULL ) {
					queue_node_t* temp_node = (queue_node_t*) temp->elem;
					packet = temp_node->packet;
					temp = temp->next;
					if( nt_dependencies_cleared( ctx, packet ) ) {
						// remove from waiting
						queue_remove( waiting[i], temp_node );
						// add to inject
						queue_node_t* new_node = (queue_node_t*) nt_checked_malloc( sizeof(queue_node_t) );
						new_node->packet = packet;
						new_node->cycle = cycle + L2_LATENCY;
						queue_push( inject[i], new_node, new_node->cycle );
						free( temp_node );
					}
				}
			}
		}

		cycle++;
	}
	for( i = 0; i < header->num_nodes; ++i ) {
		queue_delete( waiting[i] );
		queue_delete( inject[i] );
		queue_delete( traverse[i] );
	}
	free( waiting );
	free( inject );
	free( traverse );
	nt_close_trfile( ctx );
	free( ctx );

	return 0;

}

unsigned long long int calc_packet_timing( nt_packet_t* packet ) {
	int src_x = packet->src % x_nodes;
	int src_y = packet->src / x_nodes;
	int dst_x = packet->dst % x_nodes;
	int dst_y = packet->dst / x_nodes;
	int n_hops = abs( src_x - dst_x ) + abs( src_y - dst_y );
	if( n_hops <= 0 ) n_hops = 1;
	return 3*n_hops;
}
