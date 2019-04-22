/*
 * client.cc
 *
 *  Created on: Aug 3, 2016
 *      Author: sarab
	Client[0]:	IQ
	Client[1]:	RU
	Client[2]:	VC
	Client[3]:	SW
 */
#include "packets_m.h"
//#include<string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fstream>
#include <iostream>
#include <omnetpp.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <queue>
#include <stdlib.h>
#include "socket_lib.h"
using namespace omnetpp;
using namespace std;
#define numRouters 16		//Represents the number of Routers in the network
#define numClients 4		//Represents the division of a Router

std::deque<Packet *> buffer_body[numRouters][5];		//Buffer to hold Body Flits while Head routes through the router
std::deque<Packet *> buffer_tail[numRouters][5];		//Buffer to hold Tail Flits while Head routes through the router
bool tail[numRouters][5];		//Flag to keep track of packet being completely flushed in/out the router.
int lastbody[numRouters][5];		//Keeps track of the last token sent to the next router
int lasthead[numRouters][5];		//Keeps track of the last head sent to the next router
SimTime lastsent[numRouters][5];	//Time at which last token was sent to the next router
bool justarrived[numRouters][5];	//TODO
int replyfrombooksim;		//Records the message received at the socket for Client[1 or 2]
std::deque<pair<Packet *, SimTime> > buffer_head[numRouters][5];		//Records the flit IDs received from previous router (representing InputQueue) 
std::queue<int> buff_reply[numRouters][5];     //Records the head flits received from BookSim2 at Client[0] //TODO: Remove Reply Buffer
char const *str_tbs = "Junk\n";		//Message to be sent through the socket
double k[numClients]={0.0,0.0,0.0,0.0};     //Time Delays in the channels between the Clients
int replyfrombooksim_C0[numRouters][5];	//Message received at the client[0] from BookSim2
int replyfrombooksim_C3[numRouters][5];	//Message received at the client[3] from BookSim2
bool hasvalue_C0[numRouters][5];		//Flag recording status of Message being available at Client[0]
bool hasvalue_C3[numRouters][5];		//Flag recording status of Message being available at Client[3]

namespace patch					//Patch for std::to_string()
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
class mod : public cSimpleModule
{
    private:
       Packet *somemsg[5];		//Holds the current token at the Client
       cMessage *timer_msg;		//Poll msg
       bool ack[5];		//Status of acknowledgement of next module/Client of being able to accept new tokens
       double time_slot;	//Defines the time gap for which a token is held before sending out 
       SimTime current_time[5];		//Represents the last time a token was evaluated at the Client
    public:
       mod();
       virtual ~mod();
	void setupclockdomain();	//Assigns time_slots for each module of the network
    protected:
        virtual void initialize() override;		//Initialization
        void notifyBookSim(int id, int port);		//Send messages to BookSim2 through RCP-data sockets
        int replyfromBookSim(int port);		//Read messages from RCP-data sockets (written by BookSim2)
        virtual void handleMessage(cMessage *msg) override;		//Called whenever a new message arrives at the module
        virtual void finish() override;		//Finish
};
Define_Module(mod);

mod::mod()
{
	/*Constructor*/
}

mod::~mod()
{
	/*Destructor*/
    for(int i = 0; i < 5; i++)
    {
        delete somemsg[i];
    }
    delete timer_msg;
}

void mod::initialize()
{
		setupclockdomain();
      for(int P = 0; P < 5; P++)
      {
//		    resethasvalue(this->getParentModule()->getIndex(),this->getIndex(),P);
		ack[P] = true;
		somemsg[P]=nullptr;
		if(this->getIndex()==0)
			hasvalue_C0[this->getParentModule()->getIndex()][P]=false;
		if(this->getIndex()==3)
			hasvalue_C3[this->getParentModule()->getIndex()][P]=false;
      }
}

void mod::setupclockdomain()
{
	/*Assigns time_slots for each module of the network.*/
	if(this->getParentModule()->getIndex()<numRouters/2)
	{
		if(this->getIndex()==0)
	      {
		  time_slot = 1;
//		  EV<<"Client 0 time_slot = "<<time_slot<<" s\n";
	      }
		  else if(this->getIndex()==1)
	      {
		  time_slot = 2;
//		  EV<<"Client 1 time_slot = "<<time_slot<<" s\n";
	      }
	      else if(this->getIndex()==2)
	      {
		  time_slot = 3;
//		  EV<<"Client 2 time_slot = "<<time_slot<<" s\n";
	      }
	      else if(this->getIndex()==3)
	      {
		  time_slot = 5;
//		  EV<<"Client 3 time_slot = "<<time_slot<<" s\n";
	      }
	}
	else
	{
		if(this->getIndex()==0)
	      {
		  time_slot = 3;
//		  EV<<"Client 0 time_slot = "<<time_slot<<" s\n";
	      }
		  else if(this->getIndex()==1)
	      {
		  time_slot = 3;
//		  EV<<"Client 1 time_slot = "<<time_slot<<" s\n";
	      }
	      else if(this->getIndex()==2)
	      {
		  time_slot = 3;
//		  EV<<"Client 2 time_slot = "<<time_slot<<" s\n";
	      }
	      else if(this->getIndex()==3)
	      {
		  time_slot = 3;
//		  EV<<"Client 3 time_slot = "<<time_slot<<" s\n";
	      }
	}
}

void mod::handleMessage(cMessage *msg)
{
        if(msg->arrivedOn("Ack_in"))
        {
			/*Triggers when message received is an acknowledgement token. Responsible for changing "ack" status and sending out a poll msg.*/
            ack[msg->getArrivalGate()->getIndex()] = true;
//            EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ "<<this->getParentModule()->getFullName()<<"."<<this->getFullName()<<": Received, Acknowledgement, ID: "<<check_and_cast<Packet *>(msg)->getPid()<<", Port:"<<msg->getArrivalGate()->getIndex()<<" \n";
            if((int)(getcontrollertime().dbl()) != (int)(simTime().dbl()))
            {
                setcontrollertime(simTime());
                cMessage *tt_msg = new cMessage();
                sendDelayed(tt_msg,0.0,"poll");
            }
			delete (msg);
			return;
        }

        if(msg->arrivedOn("in"))
        {
			/*Triggers when message received is an data token from the previous module/Client. */
            if(this->getIndex() == 0)
            {
				/*Triggers when message is received at Client[0]*/
            	Packet *ack_msg= new Packet();		//Create and send an acknowledgement token to the previous module/Client
				ack_msg->setPid(check_and_cast<Packet *>(msg)->getPid());
				ack_msg->setPacket_type(1);
				ack_msg->setKind(1);
    			sendDelayed(ack_msg,0.0/* (double)(intuniform(0,k)/100.0)*/,"Ack_out",msg->getArrivalGate()->getIndex());    
                if(check_and_cast<Packet *>(msg)->getPid() != check_and_cast<Packet *>(msg)->getHid())
                {
					/*For Body and Tail flits, notify BookSim2 of the FlitID and add them to the respective buffers*/
                    notifyBookSim(check_and_cast<Packet *>(msg)->getPid(),msg->getArrivalGate()->getIndex());
                    if(check_and_cast<Packet *>(msg)->getPid()==(check_and_cast<Packet *>(msg)->getHid() + check_and_cast<Packet *>(msg)->getSize() - 1))
                    {
                        buffer_tail[this->getParentModule()->getIndex()][msg->getArrivalGate()->getIndex()].push_back(check_and_cast<Packet *>(msg));
                        return;
                    }
                    else
                    {
                        buffer_body[this->getParentModule()->getIndex()][msg->getArrivalGate()->getIndex()].push_back(check_and_cast<Packet *>(msg));
                        return;
                    }
                }
                else
                    buffer_head[this->getParentModule()->getIndex()][msg->getArrivalGate()->getIndex()].push_back(make_pair(check_and_cast<Packet *>(msg),simTime()));		//Add head flits to the respective Head Buffer
            }
            somemsg[msg->getArrivalGate()->getIndex()] = check_and_cast<Packet *>(msg);
            notifyBookSim(somemsg[msg->getArrivalGate()->getIndex()]->getPid(),msg->getArrivalGate()->getIndex());		//Notify BookSim2 of the FlitID
//            EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ "<<this->getParentModule()->getFullName()<<"."<<this->getFullName()<<":  Received, Message, ID: "<<somemsg[msg->getArrivalGate()->getIndex()]->getPid()<<", Port:"<<msg->getArrivalGate()->getIndex()<<" \n";
            current_time[msg->getArrivalGate()->getIndex()] = simTime();		//Update timestamp
            if(this->getIndex() == 3)
            {
				/*Triggers when message is received at Client[3]*/
                tail[this->getParentModule()->getIndex()][msg->getArrivalGate()->getIndex()] = true;
            }
        }
        
        for(int port = 0;port < 5; port++)
        {
        	/*Evaluating each port.*/
              if(this->getIndex()==3)		
              {
              	/*For Client[3]. Each port takes up the head token, sends forward it and it's body until port receives it's tail token. Only after sending forward the tail (the whole packet), it resets its status and triggers the acknowledgement. */
                  if(((simTime() - current_time[port]) >= time_slot) && (somemsg[port]!=nullptr))		//If Message token has expired its time_slot
                  {
                      if(hasvalue_C3[this->getParentModule()->getIndex()][port]==false)		//If message doesn't have its counter-message received from BookSim2, it tries to read the RCP-data socket for any
                      {
                          if((replyfrombooksim_C3[this->getParentModule()->getIndex()][port] = replyfromBookSim(port)) >= 0)		//Read RCP-data socket for any data
                          {
                              hasvalue_C3[this->getParentModule()->getIndex()][port] = true;
                              lastsent[this->getParentModule()->getIndex()][port] = simTime();
          		  			}
                      }
                       if((hasvalue_C3[this->getParentModule()->getIndex()][port]==true) && (ack[replyfrombooksim_C3[this->getParentModule()->getIndex()][port] - 1]==true))		//If message is received from RCP socket and ack is true, forward the message
                       {
                             if(tail[this->getParentModule()->getIndex()][port] == true)
                             {
                         		/*Head Flits are routed here*/
                                 tail[this->getParentModule()->getIndex()][port] = false;		//Indicating it now waits for tail
                                 ack[replyfrombooksim_C3[this->getParentModule()->getIndex()][port] - 1]=false;
                         		sendDelayed(somemsg[port],k[this->getIndex()]/* (double)(intuniform(0,k)/100.0)*/,"out",(replyfrombooksim_C3[this->getParentModule()->getIndex()][port]-1));		//Send Tokens ahead
                                 lastbody[this->getParentModule()->getIndex()][port] = somemsg[port]->getPid();
                                 lasthead[this->getParentModule()->getIndex()][port] = somemsg[port]->getPid();
                                 justarrived[this->getParentModule()->getIndex()][port]=true;
                                 if(somemsg[port]->getSize()==1)
                                 {
                                 		/*Triggered when packet size is 1. Resets status and sends back acknowledgement.*/
                                       hasvalue_C3[this->getParentModule()->getIndex()][port]=false;
                                       ack[replyfrombooksim_C3[this->getParentModule()->getIndex()][port] - 1] = false;
                                       current_time[port] = simTime();
                                       Packet *ack_msg= new Packet();
                                       ack_msg->setPid(somemsg[port]->getPid());
                                       ack_msg->setPacket_type(1);
                                       ack_msg->setKind(1);
                                       sendDelayed(ack_msg,0.0/* (double)(intuniform(0,k)/100.0)*/,"Ack_out",port/*0*/);
                                       somemsg[port] = nullptr;
                                       tail[this->getParentModule()->getIndex()][port] = true;

                                 }
                             }
                             if(tail[this->getParentModule()->getIndex()][port] == false)		//If tail has not been received
                             {
                                std::deque<Packet *>::iterator iter = buffer_body[this->getParentModule()->getIndex()][port].begin();
                                while(iter!=buffer_body[this->getParentModule()->getIndex()][port].end())
                                {
                		    		int flag2=0;
                                    if((*iter)->getHid()==lasthead[this->getParentModule()->getIndex()][port] && (*iter)->getPid()==(lastbody[this->getParentModule()->getIndex()][port] + 1))		//Finding the respective body
                                    {
                                    	if(justarrived[this->getParentModule()->getIndex()][port]==true)
                                    	{
                                    		lastsent[this->getParentModule()->getIndex()][port] = simTime();
                                    		justarrived[this->getParentModule()->getIndex()][port] = false;
                    					}
				            			if((simTime() - lastsent[this->getParentModule()->getIndex()][port] >= time_slot) && (ack[replyfrombooksim_C3[this->getParentModule()->getIndex()][port] - 1]==true))		//If Message token has expired its time_slot and ack is true, send token ahead
				            			{
				            				justarrived[this->getParentModule()->getIndex()][port] = true;
				    						somemsg[port] = new Packet();
				                            somemsg[port]->setPid((*iter)->getPid());
				                            somemsg[port]->setHid((*iter)->getHid());
				                            somemsg[port]->setPacket_type((*iter)->getPacket_type());
				                            somemsg[port]->setSize((*iter)->getSize());
				                            somemsg[port]->setDelay((*iter)->getDelay());
				                            delete (*iter);
				                            lastbody[this->getParentModule()->getIndex()][port] = somemsg[port]->getPid();
				                            notifyBookSim(somemsg[port]->getPid(),port);
				                            ack[replyfrombooksim_C3[this->getParentModule()->getIndex()][port] - 1]=false;
									     	sendDelayed(somemsg[port],k[this->getIndex()]/* (double)(intuniform(0,k)/100.0)*/,"out",(replyfrombooksim_C3[this->getParentModule()->getIndex()][port]-1));
											std::deque<Packet *>::iterator j = iter;		//TODO: Better fix for iter segF
				                            buffer_body[this->getParentModule()->getIndex()][port].erase(iter);
				                            if(j==iter && iter!=buffer_body[this->getParentModule()->getIndex()][port].end())
				                            	flag2=0;
			                            	else
				                            	flag2=1;
				                            if(buffer_body[this->getParentModule()->getIndex()][port].empty())
				                                break;
				            			}
				            			else
				            				break;
                                }
            						if(flag2==0)
                                    		iter++;
                                }
                                if(tail[this->getParentModule()->getIndex()][port] == false)				//If tail has not been received
                                {
                                    std::deque<Packet *>::iterator iter2 = buffer_tail[this->getParentModule()->getIndex()][port].begin();
                                    while(iter2!=buffer_tail[this->getParentModule()->getIndex()][port].end())
                                    {
                                        if((*iter2)->getHid()==lasthead[this->getParentModule()->getIndex()][port] && (*iter2)->getPid()==(lastbody[this->getParentModule()->getIndex()][port] + 1))		//Finding the respective tail
                                        {
		                            		if(justarrived[this->getParentModule()->getIndex()][port]==true)
				                        	{
				                        		lastsent[this->getParentModule()->getIndex()][port] = simTime();
				                        		justarrived[this->getParentModule()->getIndex()][port] = false;
				        					}
											if((simTime() - lastsent[this->getParentModule()->getIndex()][port] >= time_slot) && (ack[replyfrombooksim_C3[this->getParentModule()->getIndex()][port] - 1]==true))		//If Message token has expired its time_slot and ack is true, send token ahead, reset status and send back acknowledgement
											{
												justarrived[this->getParentModule()->getIndex()][port] = true;
												ack[replyfrombooksim_C3[this->getParentModule()->getIndex()][port] - 1] = false;
												somemsg[port] = new Packet();
												somemsg[port]->setPid((*iter2)->getPid());
												somemsg[port]->setHid((*iter2)->getHid());
												somemsg[port]->setPacket_type((*iter2)->getPacket_type());
												somemsg[port]->setSize((*iter2)->getSize());
												somemsg[port]->setDelay((*iter2)->getDelay());
												delete (*iter2);
												notifyBookSim(somemsg[port]->getPid(),port);
											 	sendDelayed(somemsg[port],k[this->getIndex()]/* (double)(intuniform(0,k)/100.0)*/,"out",(replyfrombooksim_C3[this->getParentModule()->getIndex()][port]-1));
											         
												buffer_tail[this->getParentModule()->getIndex()][port].erase(iter2);
												hasvalue_C3[this->getParentModule()->getIndex()][port]=false;
												current_time[port] = simTime();
												Packet *ack_msg= new Packet();
												ack_msg->setPid(somemsg[port]->getPid());
												ack_msg->setPacket_type(1);
												ack_msg->setKind(1);
												sendDelayed(ack_msg,0.0/* (double)(intuniform(0,k)/100.0)*/,"Ack_out",port/*0*/);
												somemsg[port] = nullptr;
												tail[this->getParentModule()->getIndex()][port] = true;
												break;
											}
											else
												break;
                                        }
                                        iter2++;
                                    }
                                }
                             }
                       }
                  }
              }
              else if(this->getIndex()==0)
              {
              	/*For Client[0].*/
                    if(/*(ack[port]==true) && */(buffer_head[this->getParentModule()->getIndex()][port].size()>0) )
                    {
                        if(hasvalue_C0[this->getParentModule()->getIndex()][port]==false /*&& buff_reply[this->getParentModule()->getIndex()][port].empty()==true*/)		//Reads from RCP-data socket
                        {
                        	replyfromBookSim(port);
                        }
                        if(hasvalue_C0[this->getParentModule()->getIndex()][port]==false && buff_reply[this->getParentModule()->getIndex()][port].empty()==false)		//If message has its counter-message received from BookSim2
                        {
                            hasvalue_C0[this->getParentModule()->getIndex()][port] = true;
                            replyfrombooksim_C0[this->getParentModule()->getIndex()][port] = buff_reply[this->getParentModule()->getIndex()][port].front();		//Takes up the first msg received
                            buff_reply[this->getParentModule()->getIndex()][port].pop();
                        }
                        if(hasvalue_C0[this->getParentModule()->getIndex()][port]==true)
                        {
                            std::deque<pair<Packet *, SimTime> >::iterator iter = buffer_head[this->getParentModule()->getIndex()][port].begin();
                            while(iter != buffer_head[this->getParentModule()->getIndex()][port].end())
                            {
                                if(iter->first->getPid()==replyfrombooksim_C0[this->getParentModule()->getIndex()][port])		//Finding respective token
                                {
                                    if(((simTime() - iter->second) >= time_slot))		//If message has expired its time_slot
                                    {
                                        if(ack[port]==true)		
                                        {
                                        	/*Send token ahead, reset its status. */
                                            somemsg[port] = iter->first;
                                            hasvalue_C0[this->getParentModule()->getIndex()][port]=false;
//                                            Packet *ack_msg= new Packet();
//                                            ack_msg->setPid(somemsg[port]->getPid());
//                                            ack_msg->setPacket_type(1);
//                                            ack_msg->setKind(1);
//                                            sendDelayed(ack_msg,0.0/* (double)(intuniform(0,k)/100.0)*/,"Ack_out",port/*0*/);
                                            ack[port] = false;
                                            sendDelayed(somemsg[port],k[this->getIndex()]/* (double)(intuniform(0,k)/100.0)*/,"out",port);
//                                          somemsg[port] = nullptr;
                                            buffer_head[this->getParentModule()->getIndex()][port].erase(iter);
                                        }
                                    }
                                    break;
                                }
                                iter++;
                            }
                        }
                    }
              }
              else
              {
              	/*For Client[1 or 2]*/
                  if((ack[port]==true) && ((simTime() - current_time[port]) >= time_slot) && (somemsg[port]!=nullptr) && ((replyfrombooksim = replyfromBookSim(port)) >= 0) )
                  {
                  	/*If Message token has expired its time_slot, ack is true and its counter-message is received from BookSim2, send token ahead, reset status and send back acknowledgement*/
                        Packet *ack_msg= new Packet();
                        ack_msg->setPid(somemsg[port]->getPid());
                        ack_msg->setPacket_type(1);
                        ack_msg->setKind(1);
                        current_time[port] = simTime();
                        ack[port] = false;
                        sendDelayed(somemsg[port],k[this->getIndex()]/* (double)(intuniform(0,k)/100.0)*/,"out",port);
                        sendDelayed(ack_msg,0.0/* (double)(intuniform(0,k)/100.0)*/,"Ack_out",port/*0*/);
                  }
              }
              if(!msg->isSelfMessage())
              {
              	/*If Client still holds a message, trigger another event at the next cycle */
                  if(this->getIndex()==0)
                  {
                      if((buffer_head[this->getParentModule()->getIndex()][0].size()>0) || (buffer_head[this->getParentModule()->getIndex()][1].size()>0) ||(buffer_head[this->getParentModule()->getIndex()][2].size()>0) ||(buffer_head[this->getParentModule()->getIndex()][3].size()>0) ||(buffer_head[this->getParentModule()->getIndex()][4].size()>0))
                      {
                          if((int)(getcontrollertime().dbl()) != (int)(simTime().dbl()))
                          {
                                for(int R=0;R<numRouters;R++)
                                {
                                    for(int C=0;C<numClients;C++)
                                    {
                                            setmsg(true,R,C);
                                    }
                                }
                              setcontrollertime(simTime());
                              cMessage *tt_msg = new cMessage();
                              tt_msg->setKind(4);
                              sendDelayed(tt_msg,0.0,"poll");
                          }
                              timer_msg = new cMessage();
                              scheduleAt(simTime() + 1.0 /*+ time_slot + double(intuniform(0, 100))/100.0*/ , timer_msg);
                              setmsg(false,this->getParentModule()->getIndex(),this->getIndex());
                      }
                  }
                  else
                  {
                      if(somemsg[0] || somemsg[1] ||somemsg[2] ||somemsg[3] ||somemsg[4])
                        {
                            if((int)(getcontrollertime().dbl()) != (int)(simTime().dbl()))
                            {
                                  for(int R=0;R<numRouters;R++)
                                  {
                                      for(int C=0;C<numClients;C++)
                                      {
                                              setmsg(true,R,C);
                                      }
                                  }
                                setcontrollertime(simTime());
                                cMessage *tt_msg = new cMessage();
                                tt_msg->setKind(4);
                                sendDelayed(tt_msg,0.0,"poll");
                            }
                            if(getmsg(this->getParentModule()->getIndex(),this->getIndex())==true)
                              {
                                  timer_msg = new cMessage();
                                  scheduleAt(simTime() + 1.0 /*+ time_slot + double(intuniform(0, 100))/100.0*/ , timer_msg);
                                  setmsg(false,this->getParentModule()->getIndex(),this->getIndex());
                              }
                        }
                  }
              }
        }
        if(msg->isSelfMessage())
        {
        	/*If Client still holds a message, trigger another event at the next cycle */
            if(this->getIndex()==0)
              {
                  if((buffer_head[this->getParentModule()->getIndex()][0].size()>0) || (buffer_head[this->getParentModule()->getIndex()][1].size()>0) ||(buffer_head[this->getParentModule()->getIndex()][2].size()>0) ||(buffer_head[this->getParentModule()->getIndex()][3].size()>0) ||(buffer_head[this->getParentModule()->getIndex()][4].size()>0))
                  {
                      if((int)(getcontrollertime().dbl()) != (int)(simTime().dbl()))
                      {
                          for(int R=0;R<numRouters;R++)
                          {
                              for(int C=0;C<numClients;C++)
                              {
                                      setmsg(true,R,C);
                              }
                          }
                          setcontrollertime(simTime());
                          cMessage *tt_msg = new cMessage();
                          tt_msg->setKind(4);
                          sendDelayed(tt_msg,0.0,"poll");
                      }
                            timer_msg = new cMessage();
                            scheduleAt(simTime() + 1.0 /*+ time_slot + double(intuniform(0, 100))/100.0*/ , timer_msg);
                            setmsg(false,this->getParentModule()->getIndex(),this->getIndex());
                  }
              }
              else
              {
                  if(somemsg[0] || somemsg[1] ||somemsg[2] ||somemsg[3] ||somemsg[4])
                    {
                        if((int)(getcontrollertime().dbl()) != (int)(simTime().dbl()))
                        {
                              for(int R=0;R<numRouters;R++)
                              {
                                  for(int C=0;C<numClients;C++)
                                  {
                                          setmsg(true,R,C);
                                  }
                              }
                            setcontrollertime(simTime());
                            cMessage *tt_msg = new cMessage();
                            tt_msg->setKind(4);
                            sendDelayed(tt_msg,0.0,"poll");
                        }
                        if(getmsg(this->getParentModule()->getIndex(),this->getIndex())==true)
                          {
                              timer_msg = new cMessage();
                              scheduleAt(simTime() + 1.0 /*+ time_slot + double(intuniform(0, 100))/100.0*/ , timer_msg);
                              setmsg(false,this->getParentModule()->getIndex(),this->getIndex());
                          }
                    }
              }
        }
        if(msg->isSelfMessage())
        {
            delete msg;
        }
}

int mod::replyfromBookSim(int port)
{
	/*Invoked to read data from the RCP-data socket.*/
    int rv,output=0;
	char c;
    struct pollfd fds_temp = getfds(this->getParentModule()->getIndex(),this->getIndex(),port);	
    rv = poll(&fds_temp,1,0);		//Waits for file descriptor to become ready for I/O. On success(if data available on socket), returns a positive value. (http://man7.org/linux/man-pages/man2/poll.2.html)
    if(rv > 0)		//On success, reads a number from socket file
    {
        while ((c = fgetc(getfp(this->getParentModule()->getIndex(),this->getIndex(),port))) != EOF)
        {
            if (c == '\n')
                break;
            else
                output = output*10 + (c - 48);
        }
    }
    if((this->getIndex() == 3) && (rv > 0))		//Client[3] receives the output port of the flit 
    {
          return output;
    }
    else if((this->getIndex() == 0) && (rv > 0))		//Client[0] receives flitID as an acknowledgement
    {
        buff_reply[this->getParentModule()->getIndex()][port].push(output);
        return -1;
    }
    else
    {
            return (rv-1);		//Client[1] & Client[2] receives garbage value as an acknowledgement
    }
}

void mod::notifyBookSim( int id, int port )
{
	/*Invoked to write data to the RCP socket*/
    std::string myvariable_router = patch::to_string(id);
    myvariable_router.append("\n");
    str_tbs = &myvariable_router[0];
    ::send(getfd(this->getParentModule()->getIndex(),this->getIndex(),port), str_tbs, strlen(str_tbs),0);		//Write FlitID to the RCP socket
    if(this->getIndex()==0 || this->getIndex()==3)
        sethasvalue(this->getParentModule()->getIndex(),this->getIndex(),port);		//RCP-data counter increament
}

void mod::finish()
{
	/*Fin*/
}
