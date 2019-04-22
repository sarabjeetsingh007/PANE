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

#define numRouters 64
#define numClients 4

using namespace omnetpp;
using namespace std;

bool fin=false;
char c_src;
FILE *fp_src;
int fromlen_src;
/*register*/ int s_src, ns_src, len_src;
struct sockaddr_un saun_src, fsaun_src;
struct pollfd fds_src;

struct pollfd fds_timer;
char c_timer;
FILE *fp_timer;
int fromlen_timer;
/*register*/ int s_timer, ns_timer, len_timer;
struct sockaddr_un saun_timer, fsaun_timer;
fd_set readset_timer;
char const *str_tbs_timer = "Junk\n";
static bool wasExecuted_timer = false;

namespace patch
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
        int countgen = 0;
        SimTime current_time;
        int countret[numRouters];
        cOutVector RetireVector;
        cLongHistogram RetireStats;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    int invoke_src();
    void init_socket();
    void timer();
    void generateMessage();
    void displayRouterLinkStats();
    void displayCoreStats();
    virtual void finish() override;
};
Define_Module(controller_src);

void controller_src::initialize()
{
    static bool wasExecuted_src = false;
    if (wasExecuted_src)
    {
    //             return;
    }
    else
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
         wasExecuted_src = true;
         init_socket();
         current_time = simTime() + 100.0;
         setcontrollertime(current_time);
         cMessage *timer_msg = new cMessage();
         handleMessage(timer_msg);
    }
}

void controller_src::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("countret"))
    {
        countret[msg->getArrivalGate()->getIndex()]++;
        RetireVector.record(check_and_cast<Packet *>(msg)->getDelay());
        RetireStats.collect(check_and_cast<Packet *>(msg)->getDelay());
//        EV<<"Count["<<msg->getArrivalGate()->getIndex()<<"] = "<<countret[msg->getArrivalGate()->getIndex()]<<endl;
    }
    else
    {
//	cout<<simTime()<<"s\n";
        if(((int)(current_time.dbl()) != (int)(simTime().dbl())))
        {
//            EV<<"RESET----\n";
//            timer();      //TODO: (Correct one), but poll fail
            generateMessage();
            timer();
   	    current_time = (int)(simTime().dbl());
		int count_temp = 0;
		for(int i=0;i<numRouters;i++)               
		    count_temp += countret[i];
		if((countgen == count_temp) && fin==false)
		{
//		    cout<<simTime()<<"s\n";
		    cMessage *timer_msg = new cMessage();
		    scheduleAt(simTime() + 1.0 /*+ time_slot + double(intuniform(0, 100))/100.0*/ , timer_msg);
		}
        }
        
    }
    delete msg;
}

void controller_src::init_socket()
{


        const char * ADDR_TIMER = "../socket_timer";
            if ((s_timer = socket(AF_UNIX, SOCK_STREAM , 0)) < 0)
                {
                    perror("server: socket");
                    exit(1);
                }
                saun_timer.sun_family = AF_UNIX;
                strcpy(saun_timer.sun_path, ADDR_TIMER);

                unlink(ADDR_TIMER);
                len_timer = sizeof(saun_timer.sun_family) + strlen(saun_timer.sun_path);



                if (bind(s_timer,(struct sockaddr *) &saun_timer, len_timer) < 0)
                {
                    perror("Timer:server: bind");
                    exit(1);
                }

                if (listen(s_timer, 5) < 0)
                {
                    perror("server: listen");
                    exit(1);
                }

                if ((ns_timer = accept(s_timer, (struct sockaddr *) &fsaun_timer,(socklen_t*) &fromlen_timer)) < 0)
                    {
                        perror("server: accept");
                        exit(1);
                    }
                fp_timer = fdopen(ns_timer, "r");
            FD_ZERO(&readset_timer);
                FD_SET(ns_timer, &readset_timer);

//SRC
                const char * ADDR_SRC = "../socket_src";
                    if ((s_src = socket(AF_UNIX, SOCK_STREAM , 0)) < 0)
                        {
                            perror("server: socket");
                            exit(1);
                        }
                        saun_src.sun_family = AF_UNIX;
                        strcpy(saun_src.sun_path, ADDR_SRC);

                        unlink(ADDR_SRC);
                        len_src = sizeof(saun_src.sun_family) + strlen(saun_src.sun_path);



                        if (bind(s_src,(struct sockaddr *) &saun_src, len_src) < 0)
                        {
                            perror("SRC:server: bind");
                            exit(1);
                        }

                        if (listen(s_src, 5) < 0)
                        {
                            perror("server: listen");
                            exit(1);
                        }

                        if ((ns_src = accept(s_src, (struct sockaddr *) &fsaun_src,(socklen_t*) &fromlen_src)) < 0)
                            {
                                perror("server: accept");
                                exit(1);
                            }
                        fp_src = fdopen(ns_src, "r");


                         fds_src.fd = ns_src;
                         fds_src.events = POLLIN;
                         fds_timer.fd = ns_timer;
                          fds_timer.events = POLLIN;

                          //RCP Sockets
                        assignsocklist();
                        for(int R=0;R<numRouters;R++)
                        {
                            for(int C=0;C<numClients;C++)
                            {
                                for(int P=0;P<5;P++)
                                {
                                    create_socket(R,C,P);
                                }
                            }
                        }
//			printf("\t\tSockets Created\n");
			setup_pollfd();

}

int controller_src::invoke_src()
{
    int output=0;
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
//	cout<<"Timer: Called at t="<<simTime()<<endl;
        if ((wasExecuted_timer == true)/* && (current_time != simTime())*/)
        {
            while ((c_timer = fgetc(fp_timer)) != EOF)
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
                            ::send(ns_timer, str_tbs_timer, strlen(str_tbs_timer),0);
                            resethasvalue(R,C,P);
		                }
		            }
		        }
            }
            ::send(ns_timer, "*", strlen("*"),0);
        }
        else if(wasExecuted_timer == false)
        {
            wasExecuted_timer = true;
            current_time = (int)(simTime().dbl());
        }
}

void controller_src::generateMessage()
{
    //GENERATION
//	cout<<"Generation: Called at t="<<simTime()<<endl;
    int rv,dest,size,num;
    while((rv = poll(&fds_src,1,0))>0)
    {
//		    cout<<"Generation: Successful at t="<<simTime()<<endl;
            num = invoke_src();
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
                    size = invoke_src();
                    dest = invoke_src();
                    int hid;
                    for(int i = 0; i<size ; i++)
                    {
                        Packet *msg = new Packet();
                        if(i==0)
                            hid=countgen;
                        msg->setPid(countgen);
                        msg->setDelay(simTime().dbl());
                        msg->setPacket_type(0);
                        msg->setSize(size);
                        msg->setHid(hid);
    //                  EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ CONTROLLER: Creating new message with ID: "<<msg->getPid()<<" \n";
//                        cout<<"GenFlit("<<msg->getPid()<<") to Router["<<dest<<"] at t="<<simTime()<<"s\n";
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
    for(int R1=0;R1<numRouters;R1++)
      {
          for(int R2=0;R2<numRouters;R2++)
          {
              if(link[R1][R2]!=0)
                  cout<<"Router:["<<R1<<"]\t->\t["<<R2<<"] = "<<link[R1][R2]<<endl;
          }
      }
}

void controller_src::displayCoreStats()
{
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
    fin=true;
    cout<<"End Time = "<<simTime()<<"s\n";
   cout<<"FINISH:\nTotal Number of packets generated = "<<countgen<<"\n";
   int count_temp = 0;
   for(int i=0;i<numRouters;i++)
      count_temp += countret[i];
   cout<<"FINISH:\nTotal Number of packets retired = "<<count_temp<<"\n";
   cout<<"Overall minimum flit latency = " << RetireStats.getMin() <<"s \n";
   cout<<"Overall maximum flit latency = " << RetireStats.getMax() <<"s \n";
   cout<<"Overall average flit latency = " << RetireStats.getMean() <<"s \n";
   displayCoreStats();          //For number of packets generated and retired at each Router
   displayRouterLinkStats();    //For Statistics of Links between Routers, TODO: This is only for mesh network
   RetireStats.recordAs("Retire Stats");
   exit(0);
}
