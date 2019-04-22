// $Id$

#include "iq_router.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <limits>

#include "globals.hpp"
#include "random_utils.hpp"
#include "vc.hpp"
#include "routefunc.hpp"
#include "outputset.hpp"
#include "buffer.hpp"
#include "buffer_state.hpp"
#include "roundrobin_arb.hpp"
#include "allocator.hpp"
#include "switch_monitor.hpp"
#include "buffer_monitor.hpp"
//*PANE support
#include <sys/types.h>
#include <sys/un.h>		
#include <sys/time.h>	
#include <unistd.h>
#include <sys/socket.h>		
#include <algorithm> 
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "socket_lib.hpp"
#define numRouters 16		//Represents the number of Routers in the network
#define numClients 4		//Represents the division of a Router

namespace patch			//Patch for std::to_string()
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}				
using namespace std;

FILE *fp[numRouters][numClients][5];		//(UNIX Domain Sockets) File pointers
struct pollfd fds[numRouters][numClients][5];		//(UNIX DOMAIN SOCKET) Holds the set of file descriptors(epoch handshake with synchronous simulator) to be monitored by poll (http://man7.org/linux/man-pages/man2/poll.2.html)
std::deque<int> buffer[numRouters][numClients];		//Structure to record flits received through the sockets from PANE
std::deque<pair<Buffer *, pair<int, pair<int, int> > > > buffer_routeup[numRouters];		//Structure to record flits forwarded by BookSim2 at RouteUpdate 
char *str_tbs = "Junk\n";		//(UNIX DOMAIN SOCKET) Message to be sent through the socket	
char *str_tbs_router = "Junk\n";		//(UNIX DOMAIN SOCKET) Message to be sent through the socket	
//PANE support*

IQRouter::IQRouter( Configuration const & config, Module *parent, string const & name, int id, int inputs, int outputs )
: Router( config, parent, name, id, inputs, outputs ), _active(false)
{
		//*PANE support
		for(int R = 0; R<numRouters; R++)
		{
			for(int C = 0; C<numClients; C++)
			{
				for(int P = 0; P<5; P++)
				{
					fds[R][C][P].fd = getfd(R,C,P);
					fds[R][C][P].events = POLLIN;
					fp[R][C][P] = fdopen(getfd(R,C,P),"r");
				}
			}
		}
		//PANE support*

  _vcs         = config.GetInt( "num_vcs" );

  _vc_busy_when_full = (config.GetInt("vc_busy_when_full") > 0);
  _vc_prioritize_empty = (config.GetInt("vc_prioritize_empty") > 0);
  _vc_shuffle_requests = (config.GetInt("vc_shuffle_requests") > 0);

  _speculative = (config.GetInt("speculative") > 0);
  _spec_check_elig = (config.GetInt("spec_check_elig") > 0);
  _spec_check_cred = (config.GetInt("spec_check_cred") > 0);
  _spec_mask_by_reqs = (config.GetInt("spec_mask_by_reqs") > 0);

  _routing_delay    = config.GetInt( "routing_delay" );
  _vc_alloc_delay   = config.GetInt( "vc_alloc_delay" );
  if(!_vc_alloc_delay)
  {
    Error("VC allocator cannot have zero delay.");
  }
  _sw_alloc_delay   = config.GetInt( "sw_alloc_delay" );
  if(!_sw_alloc_delay)
  {
    Error("Switch allocator cannot have zero delay.");
  }

  // Routing
  string const rf = config.GetStr("routing_function") + "_" + config.GetStr("topology");
  map<string, tRoutingFunction>::const_iterator rf_iter = gRoutingFunctionMap.find(rf);
  if(rf_iter == gRoutingFunctionMap.end())
  {
    Error("Invalid routing function: " + rf);
  }
  _rf = rf_iter->second;

  // Alloc VC's
  _buf.resize(_inputs);
  for ( int i = 0; i < _inputs; ++i )
  {
    ostringstream module_name;
    module_name << "buf_" << i;
    _buf[i] = new Buffer(config, _outputs, this, module_name.str( ) );
    module_name.str("");
  }

  // Alloc next VCs' buffer state
  _next_buf.resize(_outputs);
  for (int j = 0; j < _outputs; ++j)
  {
    ostringstream module_name;
    module_name << "next_vc_o" << j;
    _next_buf[j] = new BufferState( config, this, module_name.str( ) );
    module_name.str("");
  }

  // Alloc allocators
  string vc_alloc_type = config.GetStr( "vc_allocator" );
  if(vc_alloc_type == "piggyback")
  {
    if(!_speculative)
    {
      Error("Piggyback VC allocation requires speculative switch allocation to be enabled.");
    }
    _vc_allocator = NULL;
    _vc_rr_offset.resize(_outputs*_classes, -1);
  }
  else
  {
    _vc_allocator = Allocator::NewAllocator( this, "vc_allocator", vc_alloc_type, _vcs*_inputs, _vcs*_outputs );
    if ( !_vc_allocator )
    {
      Error("Unknown vc_allocator type: " + vc_alloc_type);
    }
  }
  
  string sw_alloc_type = config.GetStr( "sw_allocator" );
  _sw_allocator = Allocator::NewAllocator( this, "sw_allocator", sw_alloc_type, _inputs*_input_speedup, _outputs*_output_speedup );

  if ( !_sw_allocator )
  {
    Error("Unknown sw_allocator type: " + sw_alloc_type);
  }
  
  string spec_sw_alloc_type = config.GetStr( "spec_sw_allocator" );
  if ( _speculative && ( spec_sw_alloc_type != "prio" ) )
  {
    _spec_sw_allocator = Allocator::NewAllocator( this, "spec_sw_allocator", spec_sw_alloc_type, _inputs*_input_speedup, _outputs*_output_speedup );
    if ( !_spec_sw_allocator )
    {
      Error("Unknown spec_sw_allocator type: " + spec_sw_alloc_type);
    }
  }
  else
  {
    _spec_sw_allocator = NULL;
  }

  _sw_rr_offset.resize(_inputs*_input_speedup);
  for(int i = 0; i < _inputs*_input_speedup; ++i)
    _sw_rr_offset[i] = i % _input_speedup;
  
  _noq = config.GetInt("noq") > 0;
  if(_noq)
  {
    if(_routing_delay)
    {
      Error("NOQ requires lookahead routing to be enabled.");
    }
    if(_vcs < _outputs)
    {
      Error("NOQ requires at least as many VCs as router outputs.");
    }
  }
  _noq_next_output_port.resize(_inputs, vector<int>(_vcs, -1));
  _noq_next_vc_start.resize(_inputs, vector<int>(_vcs, -1));
  _noq_next_vc_end.resize(_inputs, vector<int>(_vcs, -1));

  // Output queues
  _output_buffer_size = config.GetInt("output_buffer_size");
  _output_buffer.resize(_outputs); 
  _credit_buffer.resize(_inputs); 

  // Switch configuration (when held for multiple cycles)
  _hold_switch_for_packet = (config.GetInt("hold_switch_for_packet") > 0);
  _switch_hold_in.resize(_inputs*_input_speedup, -1);
  _switch_hold_out.resize(_outputs*_output_speedup, -1);
  _switch_hold_vc.resize(_inputs*_input_speedup, -1);

  _bufferMonitor = new BufferMonitor(inputs, _classes);
  _switchMonitor = new SwitchMonitor(inputs, outputs, _classes);
}

IQRouter::~IQRouter( )
{
  if(gPrintActivity)
  {
    cout << Name() << ".bufferMonitor:" << endl ; 
    cout << *_bufferMonitor << endl ;
    
    cout << Name() << ".switchMonitor:" << endl ; 
    cout << "Inputs=" << _inputs ;
    cout << "Outputs=" << _outputs ;
    cout << *_switchMonitor << endl ;
  }

  for(int i = 0; i < _inputs; ++i)
    delete _buf[i];
  
  for(int j = 0; j < _outputs; ++j)
    delete _next_buf[j];

  delete _vc_allocator;
  delete _sw_allocator;
  if(_spec_sw_allocator)
    delete _spec_sw_allocator;

  delete _bufferMonitor;
  delete _switchMonitor;
}
  
void IQRouter::AddOutputChannel(FlitChannel * channel, CreditChannel * backchannel)
{
  int alloc_delay = _speculative ? max(_vc_alloc_delay, _sw_alloc_delay) : (_vc_alloc_delay + _sw_alloc_delay);
  int min_latency = 1 + _crossbar_delay + channel->GetLatency() + _routing_delay + alloc_delay + backchannel->GetLatency()  + _credit_delay;
  _next_buf[_output_channels.size()]->SetMinLatency(min_latency);
  Router::AddOutputChannel(channel, backchannel);
}

void IQRouter::ReadInputs( )
{
  bool have_flits = _ReceiveFlits( );
  bool have_credits = _ReceiveCredits( );
  _active =  _active || have_flits || have_credits;
	
}

void IQRouter::_InternalStep( )
{	
	//*PANE support
	//Read data written by PANE from socket file
	char char_rcv;	
	int counter;		//Represents number of data written in the socket by PANE in the that epoch, i.e. # of data to be read
	int temp;
	for(int P = 0; P<5; P++)		
	{
		for(int C=0; C<4; C++)
		{
			if(C==0 || C==3)
			{
				counter=getTransferCounter(this->GetID(),C,P);		// number of data to be read
				if(counter>0)
				{
					temp = 0;
					while ((char_rcv = fgetc(fp[this->GetID()][C][P])) != EOF)		
					{
						if (char_rcv == '\n')
						{
//							cout<<"s: R,C,P:["<<this->GetID()<<"]["<<C<<"]["<<P<<"]->ID:"<<temp<<endl;
							buffer[this->GetID()][C].push_back(temp);		//Adding the flit read to the buffer
							temp=0;
							--counter;
							if(counter==0)
								break;
						}
						else 
							temp = temp*10 + (char_rcv-48);
					}
					setTransferCounter(this->GetID(),C,P,0);		//Reset the counter 
				}
			}
			else
			{
				if(poll(&fds[this->GetID()][C][P],1,0) >0)
				{
					temp = 0;
					while ((char_rcv = fgetc(fp[this->GetID()][C][P])) != EOF)		
					{
						if (char_rcv == '\n')
							break;
						temp = temp*10 + (char_rcv-48);
					}
					buffer[this->GetID()][C].push_back(temp);		//Adding the flit read to the buffer
//					cout<<"s: R,C,P:["<<this->GetID()<<"]["<<C<<"]["<<P<<"]->ID:"<<temp<<endl;
				}
				setTransferCounter(this->GetID(),C,P,0);
			}
		}
	}
	//PANE support*
  if(!_active)
  {return;}

	if(!buffer[this->GetID()][0].empty())			
		_InputQueuing( );			
  
  bool activity = !_proc_credits.empty();

  if(!_route_vcs.empty())
    _RouteEvaluate( );
  if(_vc_allocator)
  {
    _vc_allocator->Clear();
    if(!_vc_alloc_vcs.empty())
      _VCAllocEvaluate( );
  }
  
  _sw_allocator->Clear();
  if(!_sw_alloc_vcs.empty())
    _SWAllocEvaluate( );
  if(!_crossbar_flits.empty())
    _SwitchEvaluate( );

  if(!_route_vcs.empty() || !buffer[this->GetID()][1].empty() || !buffer_routeup[this->GetID()].empty())		//PANE support
  {
	if(!buffer[this->GetID()][1].empty())			
			_RouteUpdate( );				
    
    activity = activity || !_route_vcs.empty() || !buffer[this->GetID()][1].empty() || !buffer_routeup[this->GetID()].empty();
  }

  if(!_vc_alloc_vcs.empty())
  {
	if(!buffer[this->GetID()][2].empty())
			_VCAllocUpdate( );				
    activity = activity || !_vc_alloc_vcs.empty();
  }

  if(_hold_switch_for_packet)
  {
    if(!_sw_hold_vcs.empty())
    {
      _SWHoldUpdate( );
      activity = activity || !_sw_hold_vcs.empty();
    }
  }

  if(!_sw_alloc_vcs.empty())
  {
    _SWAllocUpdate( );
    activity = activity || !_sw_alloc_vcs.empty();
  }
  if(!_crossbar_flits.empty() || !buffer[this->GetID()][3].empty())		//PANE support
  {
	if(!buffer[this->GetID()][3].empty())
		_SwitchUpdate( );						
    
    activity = activity || !_crossbar_flits.empty();
  }

	activity = activity || (!_in_queue_flits.empty());
  _active = activity;
  _OutputQueuing( );
  _bufferMonitor->cycle( );
  _switchMonitor->cycle( );
}

void IQRouter::WriteOutputs( )
{
  _SendFlits( );
  _SendCredits( );
}


//------------------------------------------------------------------------------
// read inputs
//------------------------------------------------------------------------------

bool IQRouter::_ReceiveFlits( )
{
  bool activity = false;
  for(int input = 0; input < _inputs; ++input)
  { 
    Flit * const f = _input_channels[input]->Receive();
    if(f)
    {
		_in_queue_flits.push_back(make_pair(input, f));
      activity = true;
//      printf("\nTime: %d, routerid: %d,f->id: [%d],ReceiveFlit, f->vc: %d, f->src: %d, f->dest: %d, input port: %d\n", GetSimTime(), this->GetID(), f->id, f->vc, f->src, f->dest, input); //Sneha
//	printf("\nTime: %d, routerid: [%d][%d],ReceiveFlit,f->id: [%d], f->vc: %d, f->src: %d, f->dest: %d\n", GetSimTime(), this->GetID(),input, f->id, f->vc, f->src, f->dest);//Debug
    }
  }
  return activity;
}

bool IQRouter::_ReceiveCredits( )
{
  bool activity = false;
  for(int output = 0; output < _outputs; ++output)
  {  
Credit * const c = _output_credits[output]->Receive();
    if(c)
    {
      _proc_credits.push_back(make_pair(GetSimTime() + _credit_delay, make_pair(c, output)));
      activity = true;
    }
  }
  return activity;
}

//-----------------------------------------------------------
// Proc_credits (after permission buffer empty)			//PANE support
//-----------------------------------------------------------
void IQRouter::CallLeftOverCredits( )
{
	while(!_proc_credits.empty())
	{	
	    pair<int, pair<Credit *, int> > const & item = _proc_credits.front();
	    int const time = item.first;
	    if(GetSimTime() < time)
	    {
	      break;
	    }
	    Credit * const c = item.second.first;
	    int const output = item.second.second;
	    BufferState * const dest_buf = _next_buf[output];
	    dest_buf->ProcessCredit(c);
	    c->Free();
	    _proc_credits.pop_front();
	}
}
//------------------------------------------------------------------------------
// input queuing		//PANE Support
//------------------------------------------------------------------------------

void IQRouter::_InputQueuing( )
{
	int flag[5]={0,0,0,0,0};		//Responsible for allowing only one flit per input-port
  std::deque<pair<int, Flit *> >::iterator iter = _in_queue_flits.begin();
  while(iter != _in_queue_flits.end())					
  {
	
	    int const input = iter->first;
	    Flit * const f = iter->second;
		if((flag[input] == 0) && (std::find(buffer[this->GetID()][0].begin(), buffer[this->GetID()][0].end(), f->id) != buffer[this->GetID()][0].end()))
		{
			int const vc = f->vc;
			    Buffer * const cur_buf = _buf[input];
			if(f->head==true && f->tail==true)		//For packet size = 1
			{
			    if(_buf[input]->GetState(vc) == VC::idle)
			    {
					cur_buf->AddFlit(vc, f);	
					_bufferMonitor->write(input, f) ;			
					cur_buf->SetState(vc, VC::routing);
					_route_vcs.push_back(make_pair(-1, make_pair(input, vc)));
					flag[input]=1;
					std::string myvariable_router = patch::to_string(f->id);		//FlitID
					myvariable_router.append("\n");
					str_tbs_router = &myvariable_router[0];	
					::send(getfd((this->GetID()),(0),(input)),str_tbs_router , strlen(str_tbs_router), 0);
//				    printf("\nTime: %d, routerid: %d,f->id: [%d],InputQueuing, f->vc: %d, f->src: %d, f->dest: %d, input port: %d\n", GetSimTime(), this->GetID(), f->id, f->vc, f->src, f->dest, input); //Sneha
//				printf("\nTime: %d, routerid: [%d][%d],IQ,f->id: [%d], f->vc: %d, f->src: %d, f->dest: %d\n", GetSimTime(), this->GetID(),input, f->id, f->vc, f->src, f->dest);//Debug
			    }
			    else 
			    {
					iter++;
					continue;
			    }
			}
			else		//For packet size >1
			{
				if(_buf[input]->GetState(vc) == VC::idle && f->head==true)
		    	{
					cur_buf->AddFlit(vc, f);	
					_bufferMonitor->write(input, f) ;		
					cur_buf->SetState(vc, VC::routing);	
					_route_vcs.push_back(make_pair(-1, make_pair(input, vc)));
					flag[input]=1;
					std::string myvariable_router = patch::to_string(f->id);		//FlitID
					myvariable_router.append("\n");
					str_tbs_router = &myvariable_router[0];	
					::send(getfd((this->GetID()),(0),(input)),str_tbs_router , strlen(str_tbs_router), 0);
//				    printf("\nTime: %d, routerid: %d,f->id: [%d],InputQueuing, f->vc: %d, f->src: %d, f->dest: %d, input port: %d\n", GetSimTime(), this->GetID(), f->id, f->vc, f->src, f->dest, input); //Sneha
//			printf("\nTime: %d, routerid: [%d][%d],IQ,f->id: [%d], f->vc: %d, f->src: %d, f->dest: %d\n", GetSimTime(), this->GetID(),input, f->id, f->vc, f->src, f->dest);//Debug
	
			   	}
			   	else if((_buf[input]->GetState(vc) == VC::active) && (_buf[input]->FrontFlit(vc) == f))
		    	{
					iter++;
					continue;
		    	}	
		    	else if(f->head==false)
		     	{
					bool flag2=false;
					std::deque<pair<int, Flit *> >::iterator iter2 = _in_queue_flits.begin();
 					while(iter2 != _in_queue_flits.end())
					{
						if(((f->id)-1) == iter2->second->id)
						{
							flag2=true;
							break;
						}
						else
							iter2++;
					}
					if(flag2==false)
					{
						cur_buf->AddFlit(vc, f);	
						_bufferMonitor->write(input, f) ;
						flag[input]=1;
//						printf("\nTime: %d, routerid: %d,f->id: [%d],InputQueuing(body/tail), f->vc: %d, f->src: %d, f->dest: %d, input port: %d\n", GetSimTime(), this->GetID(), f->id, f->vc, f->src, f->dest, input); //Sneha
//					printf("\nTime: %d, routerid: [%d][%d],IQ,f->id: [%d], f->vc: %d, f->src: %d, f->dest: %d\n", GetSimTime(), this->GetID(),input, f->id, f->vc, f->src, f->dest);//Debug
					}
					else
					{
						iter++;
						continue;
					}
				}
				else
				{
					iter++;
					continue;
				}
			}
			buffer[this->GetID()][0].erase(std::find(buffer[this->GetID()][0].begin(), buffer[this->GetID()][0].end(), f->id) );
			std::deque<pair<int, Flit *> >::iterator j = iter;
			_in_queue_flits.erase(iter);
			if((j == iter) && (iter !=_in_queue_flits.end()))
				iter++;
			if(buffer[this->GetID()][0].empty())
				break;
			if(_in_queue_flits.empty())
				break;
		}
		else
		{
			iter++;
		}
  }

  while(!_proc_credits.empty())
  {
    pair<int, pair<Credit *, int> > const & item = _proc_credits.front();
    int const time = item.first;
    if(GetSimTime() < time)
    {
      break;
    }

    Credit * const c = item.second.first;
    int const output = item.second.second;
    BufferState * const dest_buf = _next_buf[output];
    dest_buf->ProcessCredit(c);
    c->Free();
    _proc_credits.pop_front();
  }
}


//------------------------------------------------------------------------------
// routing		//PANE Support
//------------------------------------------------------------------------------

void IQRouter::_RouteEvaluate( )
{
  for(deque<pair<int, pair<int, int> > >::iterator iter = _route_vcs.begin(); iter != _route_vcs.end(); ++iter)
  {
    int const time = iter->first;
    if(time >= 0)
    {
      break;
    }
    iter->first = GetSimTime() + _routing_delay - 1;
  }    
}

void IQRouter::_RouteUpdate( )
{
	while(!_route_vcs.empty())		//Transferring flits from _route_vcs to buffer_routeup
	{
	    pair<int, pair<int, int> > const & item = _route_vcs.front();
	    int const time = item.first;
	    int const input = item.second.first;
	    int const vc = item.second.second;
	    if((time < 0) || (GetSimTime() < time))
	    {
	      break;
	    }
		buffer_routeup[this->GetID()].push_back(make_pair(_buf[input],_route_vcs.front()));
		_route_vcs.pop_front();
	}
	 deque<pair<Buffer *, pair<int, pair<int, int> > > >::iterator iter = buffer_routeup[this->GetID()].begin();
 	 while(iter != buffer_routeup[this->GetID()].end())
	{
		pair<int, pair<int, int> > const & item = iter->second;
		int const time = item.first;
		int const input = item.second.first;
		int const vc = item.second.second;
		Buffer * const cur_buf = _buf[input];
		if((std::find(buffer[this->GetID()][1].begin(), buffer[this->GetID()][1].end(), cur_buf->FrontFlit(vc)->id) != buffer[this->GetID()][1].end()))
		{
		    Flit * const f = cur_buf->FrontFlit(vc);
			::send(getfd((this->GetID()),(1),(input)),str_tbs, strlen(str_tbs), 0);
//		    printf("\nTime: %d, routerid: %d,f->id: [%d],RouteUpdate, f->vc: %d, f->src: %d, f->dest: %d, input port: %d\n", GetSimTime(), this->GetID(), f->id, f->vc, f->src, f->dest, input); //Sneha
//		printf("\nTime: %d, routerid: [%d][%d],RU,f->id: [%d], f->vc: %d, f->src: %d, f->dest: %d\n", GetSimTime(), this->GetID(),input, f->id, f->vc, f->src, f->dest);//Debug
		    cur_buf->Route(vc, _rf, this, f, input);
		    cur_buf->SetState(vc, VC::vc_alloc);
		    if(_vc_allocator)
		    {
		      _vc_alloc_vcs.push_back(make_pair(-1, make_pair(-1,make_pair(iter->first,iter->second))));
		    }
		    // NOTE: No need to handle NOQ here, as it requires lookahead routing!
			buffer[this->GetID()][1].erase(std::find(buffer[this->GetID()][1].begin(), buffer[this->GetID()][1].end(), cur_buf->FrontFlit(vc)->id) );
			std::deque<pair<Buffer *, pair<int, pair<int, int> > > >::iterator j = iter;
			buffer_routeup[this->GetID()].erase(iter);
			if((j == iter) && (iter !=buffer_routeup[this->GetID()].end()))
			{	
				iter++;
			}
			if(buffer[this->GetID()][1].empty())
				break;
			if(buffer_routeup[this->GetID()].empty())
				break;
		}
		else
		{
			iter++;
		}
	}
}

//------------------------------------------------------------------------------
// VC allocation		//PANE Support
//------------------------------------------------------------------------------

void IQRouter::_VCAllocEvaluate( )
{
  for(deque<pair<int, pair<int, pair<Buffer *, pair<int, pair<int, int> > > > > >::iterator iter = _vc_alloc_vcs.begin(); iter != _vc_alloc_vcs.end(); ++iter)
  {
    int const time = iter->first;
    if(time >= 0)
    {
      break;
    }
	pair<int, pair<int, int> > const & item = iter->second.second.second;
    int const input = item.second.first;
    int const vc = item.second.second;
	Buffer const * const cur_buf = _buf[input];
    OutputSet const * const route_set = cur_buf->GetRouteSet(vc);
    int const out_priority = cur_buf->GetPriority(vc);
    set<OutputSet::sSetElement> const setlist = route_set->GetSet();
    bool elig = false;
    bool cred = false;
    bool reserved = false;
    for(set<OutputSet::sSetElement>::const_iterator iset = setlist.begin(); iset != setlist.end(); ++iset)
    {
      int const out_port = iset->output_port;
      BufferState const * const dest_buf = _next_buf[out_port];
      int vc_start;
      int vc_end;
      if(_noq && _noq_next_output_port[input][vc] >= 0)
      {
	vc_start = _noq_next_vc_start[input][vc];
	vc_end = _noq_next_vc_end[input][vc];
      }
      else
      {
	vc_start = iset->vc_start;
	vc_end = iset->vc_end;
      }

      for(int out_vc = vc_start; out_vc <= vc_end; ++out_vc)
      {
	int in_priority = iset->pri;
	if(_vc_prioritize_empty && !dest_buf->IsEmptyFor(out_vc))
	{
	  in_priority += numeric_limits<int>::min();
	}

	// On the input input side, a VC might request several output VCs. 
	// These VCs can be prioritized by the routing function, and this is 
	// reflected in "in_priority". On the output side, if multiple VCs are 
	// requesting the same output VC, the priority of VCs is based on the 
	// actual packet priorities, which is reflected in "out_priority".
	
	if(!dest_buf->IsAvailableFor(out_vc))
	{
	}
	else
	{
	  elig = true;
	  if(_vc_busy_when_full && dest_buf->IsFullFor(out_vc))
	  {
	    reserved |= !dest_buf->IsFull();
	  }
	  else
	  {
	    cred = true;
	    int const input_and_vc = _vc_shuffle_requests ? (vc*_inputs + input) : (input*_vcs + vc);
	    _vc_allocator->AddRequest(input_and_vc, out_port*_vcs + out_vc, 0, in_priority, out_priority);
	  }
	}
      }
    }
    if(!elig)
    {
      iter->second.first = STALL_BUFFER_BUSY;
    }
    else if(_vc_busy_when_full && !cred)
    {
      iter->second.first = reserved ? STALL_BUFFER_RESERVED : STALL_BUFFER_FULL;
    }
  }

  _vc_allocator->Allocate();

  for(deque<pair<int, pair<int, pair<Buffer *, pair<int, pair<int, int> > > > > >::iterator iter = _vc_alloc_vcs.begin(); iter != _vc_alloc_vcs.end(); ++iter)
  {
    int const time = iter->first;
    if(time >= 0)
    {
      break;
    }
    iter->first = GetSimTime() + _vc_alloc_delay - 1;
	pair<int, pair<int, int> > const & item = iter->second.second.second;
    int const input = item.second.first;
    int const vc = item.second.second;
    if(iter->second.first < -1)
    {
      continue;
    }
	Buffer const * const cur_buf = _buf[input];
	
    Flit * f = cur_buf->FrontFlit(vc);
    int const input_and_vc = _vc_shuffle_requests ? (vc*_inputs + input) : (input*_vcs + vc);
    int const output_and_vc = _vc_allocator->OutputAssigned(input_and_vc);
    if(output_and_vc >= 0)
    {
      int const match_vc = output_and_vc % _vcs;
      if(match_vc != vc)
      {
      	f->repeat_change++;
      }
      iter->second.first = output_and_vc;
    }
    else
    {
      iter->second.first = STALL_BUFFER_CONFLICT;
    }
  }

  if(_vc_alloc_delay <= 1)
  {
    return;
  }

  for(deque<pair<int, pair<int, pair<Buffer *, pair<int, pair<int, int> > > > > >::iterator iter = _vc_alloc_vcs.begin(); iter != _vc_alloc_vcs.end(); ++iter)
  {
    int const time = iter->first;
    if(GetSimTime() < time)
    {
      break;
    }
	pair<int, pair<int, int> > const & item = iter->second.second.second;
    int const output_and_vc = iter->second.first;
    if(output_and_vc >= 0)
    {
      int const match_output = output_and_vc / _vcs;
      int const match_vc = output_and_vc % _vcs;
      BufferState const * const dest_buf = _next_buf[match_output];
      int const input = item.second.first;
      if(!dest_buf->IsAvailableFor(match_vc))
      {
	iter->second.first = STALL_BUFFER_BUSY;
      }
      else if(_vc_busy_when_full && dest_buf->IsFullFor(match_vc))
      {
	iter->second.first = dest_buf->IsFull() ? STALL_BUFFER_FULL : STALL_BUFFER_RESERVED;
      }
    }
  }
}

void IQRouter::_VCAllocUpdate( )				//PANE Support
{
	int size = _vc_alloc_vcs.size();
  for(int i = 0; i < size ; i++)
  {
    pair<int, pair<int, pair<Buffer *, pair<int, pair<int, int> > > > >  const & item = _vc_alloc_vcs.front();
    int const time = item.first;
    if((time < 0) || (GetSimTime() < time))
    {
	break;
    }
    int const input = item.second.second.second.second.first;
    int const vc = item.second.second.second.second.second;
	Buffer * const cur_buf = _buf[input];
	if((std::find(buffer[this->GetID()][2].begin(), buffer[this->GetID()][2].end(), cur_buf->FrontFlit(vc)->id) != buffer[this->GetID()][2].end()))
	{
		
	    Flit const * const f = cur_buf->FrontFlit(vc);
	    int const output_and_vc = item.second.first;
	    if(output_and_vc >= 0)
	    {
	      int const match_output = output_and_vc / _vcs;
	      int const match_vc = output_and_vc % _vcs;
	      BufferState * const dest_buf = _next_buf[match_output];
	      dest_buf->TakeBuffer(match_vc, input*_vcs + vc);
	      cur_buf->SetOutput(vc, match_output, match_vc);
	      cur_buf->SetState(vc, VC::active);
	      if(!_speculative)
	      {
		::send(getfd((this->GetID()),(2),(input)),str_tbs, strlen(str_tbs), 0);
//	    printf("\nTime: %d, routerid: %d,f->id: [%d],VCUpdate, f->vc: %d, f->src: %d, f->dest: %d, input port: %d\n", GetSimTime(), this->GetID(), f->id, f->vc, f->src, f->dest, input); //Sneha
//		printf("\nTime: %d, routerid: [%d][%d],VC,f->id: [%d], f->vc: %d, f->src: %d, f->dest: %d\n", GetSimTime(), this->GetID(),input, f->id, f->vc, f->src, f->dest);//Debug
		buffer[this->GetID()][2].erase(std::find(buffer[this->GetID()][2].begin(), buffer[this->GetID()][2].end(), cur_buf->FrontFlit(vc)->id));
		_sw_alloc_vcs.push_back(make_pair(-1, make_pair(-1,make_pair(item.second.second.first,item.second.second.second.second))));
	      }

	    }
	    else
	    {
	      _vc_alloc_vcs.push_back(make_pair(-1, make_pair(-1,item.second.second)));
	    }
	    _vc_alloc_vcs.pop_front();
	}
	else
	{
		_vc_alloc_vcs.push_back(make_pair(-1, make_pair(-1,item.second.second)));	
		_vc_alloc_vcs.pop_front();
	}
  }
}

//------------------------------------------------------------------------------
// switch holding
//------------------------------------------------------------------------------

void IQRouter::_SWHoldEvaluate( )
{
}

void IQRouter::_SWHoldUpdate( )
{
}


//------------------------------------------------------------------------------
// switch allocation
//------------------------------------------------------------------------------

bool IQRouter::_SWAllocAddReq(int input, int vc, int output)
{
  // When input_speedup > 1, the virtual channel buffers are interleaved to 
  // create multiple input ports to the switch. Similarily, the output ports 
  // are interleaved based on their originating input when output_speedup > 1.
  int const expanded_input = input * _input_speedup + vc % _input_speedup;
  int const expanded_output = output * _output_speedup + input % _output_speedup;
  Buffer const * const cur_buf = _buf[input];
  Flit const * const f = cur_buf->FrontFlit(vc);
  if((_switch_hold_in[expanded_input] < 0) && (_switch_hold_out[expanded_output] < 0))
  {
    Allocator * allocator = _sw_allocator;
    int prio = cur_buf->GetPriority(vc);
    if(_speculative && (cur_buf->GetState(vc) == VC::vc_alloc))
    {
      if(_spec_sw_allocator)
      {
	allocator = _spec_sw_allocator;
      }
      else
      {
	prio += numeric_limits<int>::min();
      }
    }
    Allocator::sRequest req;
    if(allocator->ReadRequest(req, expanded_input, expanded_output))
    {
      if(RoundRobinArbiter::Supersedes(vc, prio, req.label, req.in_pri, _sw_rr_offset[expanded_input], _vcs))
      {
	allocator->RemoveRequest(expanded_input, expanded_output, req.label);
	allocator->AddRequest(expanded_input, expanded_output, vc, prio, prio);
	return true;
      }
      return false;
    }
    allocator->AddRequest(expanded_input, expanded_output, vc, prio, prio);
    return true;
  }
  return false;
}

void IQRouter::_SWAllocEvaluate( )		//PANE Support
{
  bool watched = false;

  for(deque<pair<int, pair<int, pair<Buffer *, pair<int, int> > > > >::iterator iter = _sw_alloc_vcs.begin(); iter != _sw_alloc_vcs.end(); ++iter)
  {
    int const time = iter->first;
    if(time >= 0)
    {
      break;
    }
    int const input = iter->second.second.second.first;
    int const vc = iter->second.second.second.second;
	Buffer const * const cur_buf = _buf[input];
    Flit const * const f = cur_buf->FrontFlit(vc);
    if(cur_buf->GetState(vc) == VC::active) {
      int const dest_output = cur_buf->GetOutputPort(vc);
      int const dest_vc = cur_buf->GetOutputVC(vc);
      BufferState const * const dest_buf = _next_buf[dest_output];
      if(dest_buf->IsFullFor(dest_vc) || ( _output_buffer_size!=-1  && _output_buffer[dest_output].size()>=(size_t)(_output_buffer_size)))
      {
		iter->second.first = dest_buf->IsFull() ? STALL_BUFFER_FULL : STALL_BUFFER_RESERVED;
		continue;
      }
      bool const requested = _SWAllocAddReq(input, vc, dest_output);
      watched |= requested && f->watch;
      continue;
    }
    // The following models the speculative VC allocation aspects of the pipeline. An input VC with a request in for an egress virtual channel 
    // will also speculatively bid for the switch regardless of whether the VC  allocation succeeds.
    
    OutputSet const * const route_set = cur_buf->GetRouteSet(vc);
    set<OutputSet::sSetElement> const setlist = route_set->GetSet();
    
    for(set<OutputSet::sSetElement>::const_iterator iset = setlist.begin(); iset != setlist.end(); ++iset)
    {
      int const dest_output = iset->output_port;
      // for lower levels of speculation, ignore credit availability and always issue requests for all output ports in route set
      
      BufferState const * const dest_buf = _next_buf[dest_output];
      bool elig = false;
      bool cred = false;

      if(_spec_check_elig)
      {
	// for higher levels of speculation, check if at least one suitable VC is available at the current output
	int vc_start;
	int vc_end;
	
	if(_noq && _noq_next_output_port[input][vc] >= 0)
	{
	  vc_start = _noq_next_vc_start[input][vc];
	  vc_end = _noq_next_vc_end[input][vc];
	}
	else
	{
	  vc_start = iset->vc_start;
	  vc_end = iset->vc_end;
	}
	for(int dest_vc = vc_start; dest_vc <= vc_end; ++dest_vc)
	{
	  if(dest_buf->IsAvailableFor(dest_vc) && ( _output_buffer_size==-1 || _output_buffer[dest_output].size()<(size_t)(_output_buffer_size)))
	  {
	    elig = true;
	    if(!_spec_check_cred || !dest_buf->IsFullFor(dest_vc))
	    {
	      cred = true;
	      break;
	    }
	  }
	}
      }
      
      if(_spec_check_elig && !elig)
      {
	iter->second.first = STALL_BUFFER_BUSY;
      }
      else if(_spec_check_cred && !cred)
      {
	iter->second.first = dest_buf->IsFull() ? STALL_BUFFER_FULL : STALL_BUFFER_RESERVED;
      }
      else
      {
	bool const requested = _SWAllocAddReq(input, vc, dest_output);
	watched |= requested && f->watch;
      }
    }
  }
  _sw_allocator->Allocate();
  
  if(_spec_sw_allocator)
    _spec_sw_allocator->Allocate();
  
  for(deque<pair<int, pair<int, pair<Buffer *, pair<int, int> > > > >::iterator iter = _sw_alloc_vcs.begin(); iter != _sw_alloc_vcs.end(); ++iter)
  {
    int const time = iter->first;
    if(time >= 0)
    {
      break;
    }
    iter->first = GetSimTime() + _sw_alloc_delay - 1;

    int const input = iter->second.second.second.first;
    int const vc = iter->second.second.second.second;
    if(iter->second.first < -1)
    {
      continue;
    }
	Buffer const * const cur_buf = _buf[input];
    Flit const * const f = cur_buf->FrontFlit(vc);
    int const expanded_input = input * _input_speedup + vc % _input_speedup;
    int expanded_output = _sw_allocator->OutputAssigned(expanded_input);
    if(expanded_output >= 0)
    {
      int const granted_vc = _sw_allocator->ReadRequest(expanded_input, expanded_output);
      if(granted_vc == vc)
      {
	_sw_rr_offset[expanded_input] = (vc + _input_speedup) % _vcs;
	iter->second.first = expanded_output;
      }
      else
      {
	iter->second.first = STALL_CROSSBAR_CONFLICT;
      }
    }
    else if(_spec_sw_allocator)
    {
      expanded_output = _spec_sw_allocator->OutputAssigned(expanded_input);
      if(expanded_output >= 0)
      {
	if(_spec_mask_by_reqs && _sw_allocator->OutputHasRequests(expanded_output))
	{
	  iter->second.first = STALL_CROSSBAR_CONFLICT;
	}
	else if(!_spec_mask_by_reqs && (_sw_allocator->InputAssigned(expanded_output) >= 0))
	{
	  iter->second.first = STALL_CROSSBAR_CONFLICT;
	}
	else
	{
	  int const granted_vc = _spec_sw_allocator->ReadRequest(expanded_input, expanded_output);
	  if(granted_vc == vc)
	  {
	    _sw_rr_offset[expanded_input] = (vc + _input_speedup) % _vcs;
	    iter->second.first = expanded_output;
	  }
	  else
	  {
	    iter->second.first = STALL_CROSSBAR_CONFLICT;
	  }
	}
      }
      else
      {
	iter->second.first = STALL_CROSSBAR_CONFLICT;
      }
    } 
    else
    {
      iter->second.first = STALL_CROSSBAR_CONFLICT;
    }
  }
  
  if(!_speculative && (_sw_alloc_delay <= 1))
  {
    return;
  }

  for(deque<pair<int, pair<int, pair<Buffer *, pair<int, int> > > > >::iterator iter = _sw_alloc_vcs.begin(); iter != _sw_alloc_vcs.end(); ++iter)
  {
    int const time = iter->first;
    if(GetSimTime() < time)
    {
      break;
    }
    int const expanded_output = iter->second.first;
    if(expanded_output >= 0)
    {
      int const output = expanded_output / _output_speedup;
      BufferState const * const dest_buf = _next_buf[output];
      int const input = iter->second.second.second.first;
      int const vc = iter->second.second.second.second;
      int const expanded_input = input * _input_speedup + vc % _input_speedup;
		Buffer const * const cur_buf = _buf[input];
      Flit const * const f = cur_buf->FrontFlit(vc);
      if((_switch_hold_in[expanded_input] >= 0) || (_switch_hold_out[expanded_output] >= 0))
      {
		iter->second.first = STALL_CROSSBAR_CONFLICT;
      }
      else if(_speculative && (cur_buf->GetState(vc) == VC::vc_alloc))
      {
	if(_vc_allocator)
	{ // separate VC and switch allocators
	  int const input_and_vc = _vc_shuffle_requests ? (vc*_inputs + input) : (input*_vcs + vc);
	  int const output_and_vc = _vc_allocator->OutputAssigned(input_and_vc);
	  if(output_and_vc < 0)
	  {
	    iter->second.first = -1; // stall is counted in VC allocation path!
	  }
	  else if((output_and_vc / _vcs) != output)
	  {
	    iter->second.first = STALL_BUFFER_CONFLICT; // count this case as if we had failed allocation
	  }
	  else if(dest_buf->IsFullFor((output_and_vc % _vcs)))
	  {
	    iter->second.first = dest_buf->IsFull() ? STALL_BUFFER_FULL : STALL_BUFFER_RESERVED;
	  }
	}
	else
	{ // VC allocation is piggybacked onto switch allocation
	  OutputSet const * const route_set = cur_buf->GetRouteSet(vc);
	  set<OutputSet::sSetElement> const setlist = route_set->GetSet();
	  bool busy = true;
	  bool full = true;
	  bool reserved = false;
	  for(set<OutputSet::sSetElement>::const_iterator iset = setlist.begin(); iset != setlist.end(); ++iset)
	  {
	    if(iset->output_port == output)
	    {
	      int vc_start;
	      int vc_end;
	      if(_noq && _noq_next_output_port[input][vc] >= 0)
	      {
		vc_start = _noq_next_vc_start[input][vc];
		vc_end = _noq_next_vc_end[input][vc];
	      }
	      else
	      {
		vc_start = iset->vc_start;
		vc_end = iset->vc_end;
	      }
	      for(int out_vc = vc_start; out_vc <= vc_end; ++out_vc)
	      {
		if(dest_buf->IsAvailableFor(out_vc))
		{
		  busy = false;
		  if(!dest_buf->IsFullFor(out_vc))
		  {
		    full = false;
		    break;
		  }
		  else if(!dest_buf->IsFull())
		  {
		    reserved = true;
		  }
		}
	      }
	      if(!full)
	      {
		break;
	      }
	    }
	  }

	  if(busy)
	  {
	    iter->second.first = STALL_BUFFER_BUSY;
	  }
	  else if(full)
	  {
	    iter->second.first = reserved ? STALL_BUFFER_RESERVED : STALL_BUFFER_FULL;
	  }

	}

      }
      else
      {
	int const match_vc = cur_buf->GetOutputVC(vc);
	if(dest_buf->IsFullFor(match_vc))
	{
	  iter->second.first = dest_buf->IsFull() ? STALL_BUFFER_FULL : STALL_BUFFER_RESERVED;
	}
      }
    }
  }
}

void IQRouter::_SWAllocUpdate( )			//PANE Support
{
  while(!_sw_alloc_vcs.empty())
  {
    pair<int, pair<int, pair<Buffer *, pair<int, int> > > > const & item = _sw_alloc_vcs.front();
    int const time = item.first;
    if((time < 0) || (GetSimTime() < time))
    {
      break;
    }
    int const input = item.second.second.second.first;
    int const vc = item.second.second.second.second;
	Buffer * const cur_buf = _buf[input];
    Flit * const f = cur_buf->FrontFlit(vc);
	if(cur_buf->Empty(vc))
	{
			_sw_alloc_vcs.push_back(make_pair(-1, make_pair(-1,item.second.second)));
		_sw_alloc_vcs.pop_front();
		continue;
	}
    int const expanded_output = item.second.first;
	bool flag=false;
	if(f && f->tail==true && (expanded_output >= 0))		//PANE Support		
	{		
		for(deque<pair<int, pair<Flit *, pair<int, int> > > >::iterator iterc = _crossbar_flits.begin(); iterc != _crossbar_flits.end(); ++iterc)
		{
			 Flit const * const fc = iterc->second.first;
			if(f->pid == fc->pid)
			{
				flag = true;
				break;
			}
		}
	}					
    if((expanded_output >= 0) && (flag == false))		
    {
      int const expanded_input = input * _input_speedup + vc % _input_speedup;
      int const output = expanded_output / _output_speedup;
      BufferState * const dest_buf = _next_buf[output];
      int match_vc;
      match_vc = cur_buf->GetOutputVC(vc);
      cur_buf->RemoveFlit(vc);
      _bufferMonitor->read(input, f) ;
      f->hops++;
      f->vc = match_vc;
      dest_buf->SendingFlit(f);
	_crossbar_flits.push_back(make_pair(-1, make_pair(f, make_pair(expanded_input, expanded_output))));	
      if(_out_queue_credits.count(input) == 0)
      {
	_out_queue_credits.insert(make_pair(input, Credit::New()));
      }
      _out_queue_credits.find(input)->second->vc.insert(vc);
      if(cur_buf->Empty(vc))
      {
	if(f->tail)
	{
	  cur_buf->SetState(vc, VC::idle);
	}
      }
      else
      {							
	Flit * const nf = cur_buf->FrontFlit(vc);
	if(f->tail)
	{
	    cur_buf->SetState(vc, VC::routing);
	    _route_vcs.push_back(make_pair(-1, item.second.second.second));		
	}
	else
	{
	    _sw_alloc_vcs.push_back(make_pair(-1, make_pair(-1,item.second.second)));
	}
      }
    }
    else
    {
      _sw_alloc_vcs.push_back(make_pair(-1, make_pair(-1,item.second.second)));
    }
	if(cur_buf->Empty(vc) && f->tail==false)
	{
		_sw_alloc_vcs.push_back(make_pair(-1, make_pair(-1,item.second.second)));
	}
	_sw_alloc_vcs.pop_front();
  }
}


//------------------------------------------------------------------------------
// switch traversal		//PANE Support
//------------------------------------------------------------------------------

void IQRouter::_SwitchEvaluate( )
{
  for(deque<pair<int, pair<Flit *, pair<int, int> > > >::iterator iter = _crossbar_flits.begin(); iter != _crossbar_flits.end(); ++iter)
  {
    int const time = iter->first;
    if(time >= 0)
    {
      break;
    }
    
    Flit const * const f = iter->second.first;
    int const expanded_input = iter->second.second.first;
    int const expanded_output = iter->second.second.second;
		iter->first = GetSimTime() + _crossbar_delay - 1;
  }
}

void IQRouter::_SwitchUpdate( )			//PANE Support
{
	int size = _crossbar_flits.size();
  for(int i = 0; i < size ; i++)
  {
    pair<int, pair<Flit *, pair<int, int> > > const & item = _crossbar_flits.front();
    int const time = item.first;
	 Flit * const f = item.second.first;
	int const expanded_input = item.second.second.first;
	int const input = expanded_input / _input_speedup;
    if((time < 0) || (GetSimTime() < time))
    {
	_crossbar_flits.push_back(make_pair(time,item.second));
	 _crossbar_flits.pop_front();
      		continue;
    }
    if((std::find(buffer[this->GetID()][3].begin(), buffer[this->GetID()][3].end(), f->id) != buffer[this->GetID()][3].end()))
    {
	    int const expanded_output = item.second.second.second;
	    int const output = expanded_output / _output_speedup;
		if(f->head == true)
		{	
			std::string myvariable_router = patch::to_string(output+1);		//Output port
			myvariable_router.append("\n");
			str_tbs_router = &myvariable_router[0];		
			::send(getfd((this->GetID()),(3),(input)),str_tbs_router, strlen(str_tbs_router), 0);			
//		printf("\nTime: %d, routerid: %d,f->id: [%d],SwitchUpdate, f->vc: %d, f->src: %d, f->dest: %d, input port: %d, output_port = %d\n", GetSimTime(), this->GetID(), f->id, f->vc, f->src, f->dest, input, output); //Sneha
//		printf("\nTime: %d, routerid: [%d][%d],SW,f->id: [%d], f->vc: %d, f->src: %d, f->dest: %d, output_port = %d\n", GetSimTime(), this->GetID(),input, f->id, f->vc, f->src, f->dest, output);//Debug
		}
		else
		{
//			printf("\nTime: %d, routerid: %d,f->id: [%d],SwitchUpdate(body/tail), f->vc: %d, f->src: %d, f->dest: %d, input port: %d, output_port = %d\n", GetSimTime(), this->GetID(), f->id, f->vc, f->src, f->dest, input, output); //Sneha
//			printf("\nTime: %d, routerid: [%d][%d],SW,f->id: [%d], f->vc: %d, f->src: %d, f->dest: %d, output_port = %d\n", GetSimTime(), this->GetID(),input, f->id, f->vc, f->src, f->dest, output);//Debug
		}
	    _switchMonitor->traversal(input, output, f) ;
	    _output_buffer[output].push(f);
	    //the output buffer size isn't precise due to flits in flight but there is a maximum bound based on output speed up and ST traversal
		buffer[this->GetID()][3].erase(std::find(buffer[this->GetID()][3].begin(), buffer[this->GetID()][3].end(), f->id));
	    _crossbar_flits.pop_front();
		if(_crossbar_flits.size() == 0)
			break;
     }	
     else
     {
	 _crossbar_flits.push_back(make_pair(-1,item.second));
	 _crossbar_flits.pop_front();
     }
  }
}


//------------------------------------------------------------------------------
// output queuing
//------------------------------------------------------------------------------

void IQRouter::_OutputQueuing( )
{
  for(map<int, Credit *>::const_iterator iter = _out_queue_credits.begin(); iter != _out_queue_credits.end(); ++iter)
  {
    int const input = iter->first;
    Credit * const c = iter->second;
    _credit_buffer[input].push(c);
  }
  _out_queue_credits.clear();
}

//------------------------------------------------------------------------------
// write outputs
//------------------------------------------------------------------------------

void IQRouter::_SendFlits( )
{
  for ( int output = 0; output < _outputs; ++output )
  {
    if ( !_output_buffer[output].empty( ) )
    {
      Flit * const f = _output_buffer[output].front( );
      _output_buffer[output].pop( );

      
//      printf("\nTime: %d, routerid: %d,f->id: [%d],SendFlits, f->src: %d, f->dest: %d, output port = %d\n", GetSimTime(), this->GetID(), f->id, f->src, f->dest, output); //Sneha
//	printf("\nTime: %d, routerid: [%d],SendFlits,f->id: [%d], f->src: %d, f->dest: %d, output_port = %d\n", GetSimTime(), this->GetID(), f->id, f->src, f->dest, output);//Debug

	_output_channels[output]->Send( f );
    }
  }
}

void IQRouter::_SendCredits( )
{
  for ( int input = 0; input < _inputs; ++input )
  {
    if ( !_credit_buffer[input].empty( ) )
    {
      Credit * const c = _credit_buffer[input].front( );
      _credit_buffer[input].pop( );
      _input_credits[input]->Send( c );
    }
  }
}


//------------------------------------------------------------------------------
// misc.
//------------------------------------------------------------------------------

void IQRouter::Display( ostream & os ) const
{
  for ( int input = 0; input < _inputs; ++input )
  {
    _buf[input]->Display( os );
  }
}

int IQRouter::GetUsedCredit(int o) const
{
  BufferState const * const dest_buf = _next_buf[o];
  return dest_buf->Occupancy();
}

int IQRouter::GetBufferOccupancy(int i) const
{
  return _buf[i]->GetOccupancy();
}

vector<int> IQRouter::UsedCredits() const
{
  vector<int> result(_outputs*_vcs);
  for(int o = 0; o < _outputs; ++o)
  {
    for(int v = 0; v < _vcs; ++v)
    {
      result[o*_vcs+v] = _next_buf[o]->OccupancyFor(v);
    }
  }
  return result;
}

vector<int> IQRouter::FreeCredits() const
{
  vector<int> result(_outputs*_vcs);
  for(int o = 0; o < _outputs; ++o)
  {
    for(int v = 0; v < _vcs; ++v)
    {
      result[o*_vcs+v] = _next_buf[o]->AvailableFor(v);
    }
  }
  return result;
}

vector<int> IQRouter::MaxCredits() const
{
  vector<int> result(_outputs*_vcs);
  for(int o = 0; o < _outputs; ++o)
  {
    for(int v = 0; v < _vcs; ++v)
    {
      result[o*_vcs+v] = _next_buf[o]->LimitFor(v);
    }
  }
  return result;
}

void IQRouter::_UpdateNOQ(int input, int vc, Flit const * f)
{
  set<OutputSet::sSetElement> sl = f->la_route_set.GetSet();
  int out_port = sl.begin()->output_port;
  const FlitChannel * channel = _output_channels[out_port];
  const Router * router = channel->GetSink();
  if(router)
  {
    int in_channel = channel->GetSinkPort();
    OutputSet nos;
    _rf(router, f, in_channel, &nos, false);
    sl = nos.GetSet();
    OutputSet::sSetElement const & se = *sl.begin();
    int next_output_port = se.output_port;
    _noq_next_output_port[input][vc] = next_output_port;
    int next_vc_count = (se.vc_end - se.vc_start + 1) / router->NumOutputs();
    int next_vc_start = se.vc_start + next_output_port * next_vc_count;
    _noq_next_vc_start[input][vc] = next_vc_start;
    int next_vc_end = se.vc_start + (next_output_port + 1) * next_vc_count - 1;
    _noq_next_vc_end[input][vc] = next_vc_end;
  }
}
