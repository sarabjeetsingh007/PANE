// $Id$


/*main.cpp
 *
 *The starting point of the network simulator
 *-Include all network header files
 *-initilize the network
 *-initialize the traffic manager and set it to run
 *
 *
 */
#include <sys/time.h>	

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <sstream>
#include "booksim.hpp"
#include "routefunc.hpp"
#include "traffic.hpp"
#include "booksim_config.hpp"
#include "trafficmanager.hpp"
#include "random_utils.hpp"
#include "network.hpp"
#include "injection.hpp"
#include "power_module.hpp"


#include <sys/types.h>	//*Sarab		
#include <sys/socket.h>		
#include <sys/un.h>		
#include <unistd.h>
#include "socket_lib.hpp"
#define numRouters 16
#define numClients 4

int s_src;
int s_timer;	
int s[numRouters][5][5];
			//Sarab*

///////////////////////////////////////////////////////////////////////////////
//Global declarations
//////////////////////

 /* the current traffic manager instance */
TrafficManager * trafficManager = NULL;

int GetSimTime() {
  return trafficManager->getTime();
}

class Stats;
Stats * GetStats(const std::string & name) {
  Stats* test =  trafficManager->getStats(name);
  if(test == 0){
    cout<<"warning statistics "<<name<<" not found"<<endl;
  }
  return test;
}

/* printing activity factor*/
bool gPrintActivity;

int gK;//radix
int gN;//dimension
int gC;//concentration

int gNodes;

//generate nocviewer trace
bool gTrace;

ostream * gWatchOut;



/////////////////////////////////////////////////////////////////////////////

bool Simulate( BookSimConfig const & config )
{
  vector<Network *> net;

  int subnets = config.GetInt("subnets");
  /*To include a new network, must register the network here
   *add an else if statement with the name of the network
   */
  net.resize(subnets);
  for (int i = 0; i < subnets; ++i) {
    ostringstream name;
    name << "network_" << i;
    net[i] = Network::New( config, name.str() );
//    net[i]->DumpChannelMap();		//Sneha
//    net[i]->DumpNodeMap();		//Sneha
  }
	
  /*tcc and characterize are legacy not sure how to use them */

  trafficManager = TrafficManager::New( config, net ) ;

  /*Start the simulation run */

  double total_time; /* Amount of time we've run */
  struct timeval start_time, end_time; /* Time before/after user code */
  total_time = 0.0;
  gettimeofday(&start_time, NULL);

  bool result = trafficManager->Run() ;


  gettimeofday(&end_time, NULL);
  total_time = ((double)(end_time.tv_sec) + (double)(end_time.tv_usec)/1000000.0) - ((double)(start_time.tv_sec) + (double)(start_time.tv_usec)/1000000.0);

  cout<<"Total run time "<<total_time<<endl;

  for (int i=0; i<subnets; ++i) {

    ///Power analysis
    if(config.GetInt("sim_power") > 0){
      Power_Module pnet(net[i], config);
      pnet.run();
    }

    delete net[i];
  }

  delete trafficManager;
  trafficManager = NULL;

  return result;
}


int main( int argc, char **argv )
{
	//Assigning Address			//*Sarab
	assignsocklist();
	//Timer					
	setfd_timer(create_socket_timer());
	usleep(10000);

	//Src					
	setfd_src(create_socket_src());
	usleep(10000);
	
	//Clients
	for(int R=0;R<numRouters;R++)
	{
		for(int C=0;C<numClients;C++)
		{
		    for(int P=0;P<5;P++)
		    {
			setfd(create_socket(R,C,P),R,C,P);
		    }
		}
	}
//	cout<<"Clients Done\n";
						//Sarab*

  BookSimConfig config;


  if ( !ParseArgs( &config, argc, argv ) ) {
    cerr << "Usage: " << argv[0] << " configfile... [param=value...]" << endl;
    return 0;
 } 
  /*initialize routing, traffic, injection functions  */
  InitializeRoutingMap( config );

  gPrintActivity = (config.GetInt("print_activity") > 0);
  gTrace = (config.GetInt("viewer_trace") > 0);
  
  string watch_out_file = config.GetStr( "watch_out" );
  if(watch_out_file == "") {
    gWatchOut = NULL;
  } else if(watch_out_file == "-") {
    gWatchOut = &cout;
  } else {
    gWatchOut = new ofstream(watch_out_file.c_str());
  }
  

  /*configure and run the simulator */
  bool result = Simulate( config );
  return result ? -1 : 0;
}
