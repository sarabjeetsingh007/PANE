/*
PANE/controller.cc
Controller is responsible for managing the control of PANE simulation. The handshake model with the synchronous simulator allows it to execute once per epoch. Controller also manages the generation of packets into the network, bookkeeping the Core statistics, inter process channel connection (UNIX DOMAIN SOCKET), and the termination of simulation. Moreover, controller links the counter of data sent through the socket with the epoch increment socket.
*/
#include <omnetpp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <iostream>
#include<stdlib.h>
#include <poll.h>
#include "packets_m.h"
#include "socket_lib.h"
#include "outputbuffer.h"
#include <sys/ioctl.h>

#define numRouters 16		//Represents the number of Routers in the network
#define numClients 4		//Represents the division of a Router

using namespace omnetpp;
using namespace std;

bool fin=false;		//Triggers when Simulation Finishes
struct pollfd fds_src;		//(UNIX DOMAIN SOCKET) Holds the set of file descriptors(Core->GenFlit) to be monitored by poll (http://man7.org/linux/man-pages/man2/poll.2.html)
struct pollfd fds_timer;		//(UNIX DOMAIN SOCKET) Holds the set of file descriptors(epoch handshake with synchronous simulator) to be monitored by poll (http://man7.org/linux/man-pages/man2/poll.2.html)
FILE *fp_src;		//(UNIX DOMAIN SOCKET) file pointer
FILE *fp_timer;		//(UNIX DOMAIN SOCKET) file pointer
int fromlen_src;		//(UNIX DOMAIN SOCKET: addrlen) contains the size of structure pointed by the socket address 
int fromlen_timer;		//(UNIX DOMAIN SOCKET: addrlen) contains the size of structure pointed by the socket address
int s_src, ns_src, len_src;		//(UNIX DOMAIN SOCKET parameters)
struct sockaddr_un saun_src, fsaun_src;	//(UNIX DOMAIN SOCKET parameters)
int s_timer, ns_timer, len_timer;		//(UNIX DOMAIN SOCKET parameters)
struct sockaddr_un saun_timer, fsaun_timer;		//(UNIX DOMAIN SOCKET parameters)
fd_set readset_timer;		//(UNIX DOMAIN SOCKET) Represents the file descriptors set
char const *str_tbs_timer = "Junk\n";		//(UNIX DOMAIN SOCKET) Message to be sent through the socket
static bool wasExecuted_timer = false;		//To ensure handshake enforcement only after initialization of both PANE and BookSim2

namespace patch				//Patch for std::to_string()
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

class controller_src : public cSimpleModule
{
    public:
        int countgen = 0;		//Records the number of flits generated in the network
        SimTime current_time;		//Keeps track of the last timestamp at which controller was called
        int countret[numRouters];		//Records the number of flits retired at each Router of the network
        cOutVector RetireVector;		//Records vector simulation results for retired flits
        cLongHistogram RetireStats;		//Generates equidistant histogram for retired flits
  protected:
    virtual void initialize();		//Initialization
    virtual void handleMessage(cMessage *msg);		//Called whenever a new event arrives on controller
    int invoke_src();		//Figures out the source router of generated packet
    void init_socket();			//Initializes the IPC connection between PANE and BookSim2
    void timer();			//Epoch increament handshake
    void generateMessage();			//Generates a new packet of data
    void displayRouterLinkStats();		//Displays Router-Link Statistics
    void displayCoreStats();		//Displays Core Statistics
    virtual void finish() override;		//Fin
};
Define_Module(controller_src);

void controller_src::initialize()
{
    	for(int R=0;R<numRouters;R++)
    	{
    	    countret[R]=0;
    	    for(int C=0;C<4;C++)
    	    {
    	        for(int P=0;P<5;P++)
    	            resethasvalue(R,C,P);
    	    }
    	}
         init_socket();
         current_time = simTime() - 100.0;
         setcontrollertime(current_time);
         cMessage *timer_msg = new cMessage();
         handleMessage(timer_msg);
}

void controller_src::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("countret"))		/*If the message arrived through the "countret" gate, it's recorded as a retired flit*/
    {
        countret[msg->getArrivalGate()->getIndex()]++;
        RetireVector.record(check_and_cast<Packet *>(msg)->getDelay());
        RetireStats.collect(check_and_cast<Packet *>(msg)->getDelay());
//        EV<<"Count["<<msg->getArrivalGate()->getIndex()<<"] = "<<countret[msg->getArrivalGate()->getIndex()]<<endl;
    }
    else
    {
        if(((int)(simTime().dbl()) - (int)(current_time.dbl())) >= 1.0)		/*Checks if the message trigging the event is in the same epoch. Removes redundancy of multiple events in the same epoch*/
        {
            generateMessage();		
            timer();
	   	    current_time = (int)(simTime().dbl());		//Updates its timestamp
			int countret_all = 0;
			for(int i=0;i<numRouters;i++)               
				countret_all += countret[i];
			if((countgen == countret_all) && fin==false)		/*Keeps the simulation going even if there exists no packet of data in the network, by scheduling a null message to itself at the next epoch*/
			{
				cMessage *timer_msg = new cMessage();
				scheduleAt(simTime() + 1.0 , timer_msg);
			}
        }
        
    }
    delete msg;
}

void controller_src::init_socket()
{
	/*Sets up IPC connection (UNIX DOMAIN SOCKET) between PANE and BookSim2. We have three types of sockets: epoch increment socket, packet generation socket, and RCP-data socket.*/
	
	//Epoch increment socket
	const char * ADDR_TIMER = "../socket_timer";
    if ((s_timer = socket(AF_UNIX, SOCK_STREAM , 0)) < 0)	//creates a socket
    {
        perror("server: socket");
        exit(1);
    }
    saun_timer.sun_family = AF_UNIX;		//set type of socket to be UNIX DOMAIN
    strcpy(saun_timer.sun_path, ADDR_TIMER);

    unlink(ADDR_TIMER);		//unlink from any other connection
    len_timer = sizeof(saun_timer.sun_family) + strlen(saun_timer.sun_path);

    if (bind(s_timer,(struct sockaddr *) &saun_timer, len_timer) < 0)	//binds socket to the address
    {
        perror("Timer:server: bind");
        exit(1);
    }

    if (listen(s_timer, 5) < 0)		//listen for incoming connections from any client programs
    {
        perror("server: listen");
        exit(1);
    }

    if ((ns_timer = accept(s_timer, (struct sockaddr *) &fsaun_timer,(socklen_t*) &fromlen_timer)) < 0)		//accept a connection from a client
    {
        perror("server: accept");
        exit(1);
    }
    fp_timer = fdopen(ns_timer, "r");

    FD_ZERO(&readset_timer);		// Resets the file descriptor set
    FD_SET(ns_timer, &readset_timer);		// Assigns the socket file descriptor to the set


	//Packet generation socket
	const char * ADDR_SRC = "../socket_src";
	if ((s_src = socket(AF_UNIX, SOCK_STREAM , 0)) < 0)		//creates a socket
    {
        perror("server: socket");
        exit(1);
    }
    saun_src.sun_family = AF_UNIX;		//set type of socket to be UNIX DOMAIN
    strcpy(saun_src.sun_path, ADDR_SRC);

    unlink(ADDR_SRC);	//unlink from any other connection
    len_src = sizeof(saun_src.sun_family) + strlen(saun_src.sun_path);

    if (bind(s_src,(struct sockaddr *) &saun_src, len_src) < 0)	//binds socket to the address
    {
        perror("SRC:server: bind");
        exit(1);
    }

    if (listen(s_src, 5) < 0)		//listen for incoming connections from any client programs
    {
        perror("server: listen");
        exit(1);
    }

    if ((ns_src = accept(s_src, (struct sockaddr *) &fsaun_src,(socklen_t*) &fromlen_src)) < 0)		//accept a connection from a client
    {
        perror("server: accept");
        exit(1);
    }
    fp_src = fdopen(ns_src, "r");


     fds_src.fd = ns_src;
     fds_src.events = POLLIN;
     fds_timer.fd = ns_timer;
     fds_timer.events = POLLIN;

    //RCP-data Sockets
    assignsocklist();		//Defining address
    for(int R=0;R<numRouters;R++)
    {
        for(int C=0;C<numClients;C++)
        {
            for(int P=0;P<5;P++)
            {
                create_socket(R,C,P);	//Setup RCP-data sockets
            }
        }
    }
	setup_pollfd();
}

int controller_src::invoke_src()
{
	/*Returns the number held at the top of the socket buffer. Returns -1 when the synchronous simulator (BookSim2) terminates*/
    int output=0;
	char c_src;
    while((c_src=fgetc(fp_src))!=EOF)
    {
        if (c_src == '\n')
            break;
        if(c_src == 'q')
        {
            output = -1;
            break;
        }
        output = output*10 + (c_src-48);
    }
    return output;
}

void controller_src::timer()
{
	/* Responsible for maintaining the epoch increament handshake. Sends out data once every epoch. Moreover, the sent data serves as a counter for how much data have been written to each of the RCP-data sockets in the respective epoch. */
	char c_timer;
    if ((wasExecuted_timer == true)/* && (current_time != simTime())*/)
    {
        while ((c_timer = fgetc(fp_timer)) != EOF)		//Stalls until data available from the BookSim2 side, maintaining the epoch handshake
        {
            if (c_timer == '\n')
                    break;
        }
        for(int R=0;R<numRouters;R++)
        {
	        for(int C=0;C<4;C++)
	        {
	            for(int P=0;P<5;P++)
	            {
	                if(gethasvalue(R,C,P)>0)
	                {
                        std::string myvariable_timer = patch::to_string(R);
                        myvariable_timer.append("\n");
                        myvariable_timer.append(patch::to_string(C));
                        myvariable_timer.append("\n");
                        myvariable_timer.append(patch::to_string(P));
                        myvariable_timer.append("\n");
                        myvariable_timer.append(patch::to_string(gethasvalue(R,C,P)));
                        myvariable_timer.append("\n");
                        str_tbs_timer = &myvariable_timer[0];
                        ::send(ns_timer, str_tbs_timer, strlen(str_tbs_timer),0);		//Sending over socket "#R,#C,#P,#(data written in RCP socket)"
                        resethasvalue(R,C,P);		//Reset RCP-data counter
	                }
	            }
	        }
        }
        ::send(ns_timer, "*", strlen("*"),0);		//Appending the socket data with "*", representing the end-of-data
    }
    else if(wasExecuted_timer == false)
    {
        wasExecuted_timer = true;
        current_time = (int)(simTime().dbl());
    }
}

void controller_src::generateMessage()
{
	/* Responsible for reading through socket for any generation of new packets and creating them. Also, responsible for noting down the router number at which the packet is generated and its packet size. Uses the poll function to monitor over the file descriptors for data. (http://man7.org/linux/man-pages/man2/select.2.html) */
    int rv,dest,size,num;
    while((rv = poll(&fds_src,1,0))>0)
    {
        num = invoke_src();		//num gives number of packets generated. If num = -1, BookSim2 has terminated
        if(num == -1)
        {
            cout<<"Simulation End!\n";
            finish();
            break;
        }
        else
        {
            while(num)
            {
                size = invoke_src();		//size gives the packet size
                dest = invoke_src();		//dest gives the router number at which packet is generated
                int hid;
                for(int i = 0; i<size ; i++)
                {
                    Packet *msg = new Packet();		//Creating new packet with each flits having parameters defined in "packets.msg"
                    if(i==0)
                        hid=countgen;
                    msg->setPid(countgen);
                    msg->setDelay(simTime().dbl());
                    msg->setPacket_type(0);
                    msg->setSize(size);
                    msg->setHid(hid);
//                  EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ CONTROLLER: Creating new message with ID: "<<msg->getPid()<<" \n";
                    countgen++;
                    sendDelayed(msg,0.0/*(double)(intuniform(0,10)/100.0)*/,"out",(dest));
                }
                --num;
            }
        }
    }
}

void controller_src::displayRouterLinkStats()
{
	/* Displays the Router-Link Statistics of the network. Currently working for Mesh topology only.*/
    cout<<"\nRouter Link Stats:\n";
    int link[numRouters][numRouters];
    for(int R1=0;R1<numRouters;R1++)
    {
       for(int R2=0;R2<numRouters;R2++)
       {
           link[R1][R2]=0;
       }
    }
    int maxH=sqrt(numRouters);
    int maxV=sqrt(numRouters);
    int r = 0;   //right
    int l = 1;  //left
    int d = 2;  //down
    int u = 3;  //up
    for(int H=0; H<maxH; H++)
    {
       for(int V=0; V<maxV; V++)
       {
           if((H-1)>=0)
               link[V*maxH + H][V*maxH + (H-1)] += check_and_cast<outputbuffer *>(this->getParentModule()->getSubmodule("router", (V*maxH + H))->getSubmodule("outputbuff", l))->count;
           if((V-1)>=0)
               link[V*maxH + H][(V-1)*maxH + H] += check_and_cast<outputbuffer *>(this->getParentModule()->getSubmodule("router", (V*maxH + H))->getSubmodule("outputbuff", u))->count;
           if((H+1)<maxH)
               link[V*maxH + H][V*maxH + (H+1)] += check_and_cast<outputbuffer *>(this->getParentModule()->getSubmodule("router", (V*maxH + H))->getSubmodule("outputbuff", r))->count;
           if((V+1)<maxV)
               link[V*maxH + H][(V+1)*maxH + H] += check_and_cast<outputbuffer *>(this->getParentModule()->getSubmodule("router", (V*maxH + H))->getSubmodule("outputbuff", d))->count;

       }
    }
	int totaltraffic=0;
    for(int R1=0;R1<numRouters;R1++)
	{
	  for(int R2=0;R2<numRouters;R2++)
	  {
		  if(link[R1][R2]!=0)
		   {
			   cout<<"Router:["<<R1<<"]\t->\t["<<R2<<"] = "<<link[R1][R2]<<endl;
				totaltraffic +=link[R1][R2];
			}
	  }
	}
	cout<<"Link Activity Factor = "<<totaltraffic/simTime()<<endl;
}

void controller_src::displayCoreStats()
{
	/* Displays the Core Statistics of each router in the network. */
    cout<<"\nRouter[#]\t\t\t# Generated\t\t# Retired"<<endl;
    for(int R=0; R<numRouters; R++)
    {
       cout<<"Router["<<R<<"]\t\t\t";
       this->getParentModule()->getSubmodule("src", R)->callFinish();
       this->getParentModule()->getSubmodule("sink", R)->callFinish();
//       for(int C=0; C<numClients; C++)
//           this->getParentModule()->getSubmodule("router", R)->getSubmodule("client", C)->callFinish();
    }
}

void controller_src::finish()
{
	/* Fin. Called upon when BookSim2 terminates. Responsible for generating statistics.*/
    fin=true;
    cout<<"End Time = "<<simTime()<<"s\n";
   cout<<"FINISH:\nTotal Number of packets generated = "<<countgen<<"\n";
   int countret_all = 0;
   for(int i=0;i<numRouters;i++)
      countret_all += countret[i];
   cout<<"FINISH:\nTotal Number of packets retired = "<<countret_all<<"\n";
   cout<<"Overall minimum flit latency = " << RetireStats.getMin() <<"s \n";
   cout<<"Overall maximum flit latency = " << RetireStats.getMax() <<"s \n";
   cout<<"Overall average flit latency = " << RetireStats.getMean() <<"s \n";
   displayCoreStats();          //For number of packets generated and retired at each Router
   displayRouterLinkStats();    //For Statistics of Links between Routers, TODO: This is only for mesh network
   RetireStats.recordAs("Retire Stats");
   exit(0);
}
