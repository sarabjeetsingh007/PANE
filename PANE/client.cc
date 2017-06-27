/*
 * client.cc
 *
 *  Created on: Aug 3, 2016
 *      Author: sarab
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
//#include "test.hpp"
using namespace omnetpp;
using namespace std;
#define numRouters 16
#define numClients 4

std::deque<Packet *> buff_body[numRouters][5];
std::deque<Packet *> buff_tail[numRouters][5];
bool tail[numRouters][5];
int lastbody[numRouters][5];
int lasthead[numRouters][5];
SimTime lastsent[numRouters][5];
bool justarrived[numRouters][5];

int replyfrombooksim;
std::deque<pair<Packet *, SimTime> > buffer[numRouters][5];

std::queue<int> buff_reply[numRouters][5];      //TODO: Remove Reply Buffer

char c;
char const *str_tbs = "From Omi!\n";

bool starts_with(const string& s1, const string& s2) {
    return s2.size() <= s1.size() && s1.compare(0, s2.size(), s2) == 0;
}

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

double k[numClients]={0.0,0.0,0.0,0.0};     //Time Delays

class mod : public cSimpleModule
{
    private:
       Packet *somemsg[5];
       Packet *ackmsg[5];
       cMessage *timer_msg;
       bool hasvalue0[5];
       int replyfrombooksim0[5];
       bool hasvalue[5];
       int replyfrombooksim1[5];
       bool ack[5];
       double time_slot;
       SimTime current_time[5];
    public:
       mod();
       virtual ~mod();
//       int port_value[5];
    protected:
        virtual void initialize() override;
        void notifyBookSim(int id, int port);
        int replyfromBookSim(int port);
        virtual void handleMessage(cMessage *msg) override;
        virtual void finish() override;
};
Define_Module(mod);

mod::mod()
{
    for(int i = 0; i < 5 ; i++)
    {
        ack[i]=true;
        somemsg[i]=nullptr;
        ackmsg[i]=nullptr;
        hasvalue[i]=false;
        hasvalue0[i]=false;
    }
}

mod::~mod()
{
    for(int i = 0; i < 5; i++)
    {
        delete somemsg[i];
        delete ackmsg[i];
//        delete timer_msg[i];
    }
    delete timer_msg;
}

void mod::initialize()
{
	if(this->getParentModule()->getIndex()<0)
	{
		if(this->getIndex()==0)
	      {
		  time_slot = 1;
		  EV<<"Client 0 time_slot = "<<time_slot<<" s\n";
	      }
		  else if(this->getIndex()==1)
	      {
		  time_slot = 2;
		  EV<<"Client 1 time_slot = "<<time_slot<<" s\n";
	      }
	      else if(this->getIndex()==2)
	      {
		  time_slot = 3;
		  EV<<"Client 2 time_slot = "<<time_slot<<" s\n";
	      }
	      else if(this->getIndex()==3)
	      {
		  time_slot = 5;
		  EV<<"Client 3 time_slot = "<<time_slot<<" s\n";
	      }
	}
	else
	{
		if(this->getIndex()==0)
	      {
		  time_slot = 3;
		  EV<<"Client 0 time_slot = "<<time_slot<<" s\n";
	      }
		  else if(this->getIndex()==1)
	      {
		  time_slot = 3;
		  EV<<"Client 1 time_slot = "<<time_slot<<" s\n";
	      }
	      else if(this->getIndex()==2)
	      {
		  time_slot = 3;
		  EV<<"Client 2 time_slot = "<<time_slot<<" s\n";
	      }
	      else if(this->getIndex()==3)
	      {
		  time_slot = 3;
		  EV<<"Client 3 time_slot = "<<time_slot<<" s\n";
	      }
	}
		
         
      for(int P = 0; P < 5; P++)
      {
//		    resethasvalue(this->getParentModule()->getIndex(),this->getIndex(),P);
            ack[P] = true;
      }
}
void mod::handleMessage(cMessage *msg)
{
//        if(this->getIndex()==3)     //TODO: Validate
//        {
//            for(int i=0;i<5;i++)
//                ack[i]= true;
//        }
        if(msg->arrivedOn("Ack_in"))
        {
//            ackmsg[msg->getArrivalGate()->getIndex()] = check_and_cast<Packet *>(msg);
//            EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ "<<this->getParentModule()->getFullName()<<"."<<this->getFullName()<<": Received, Acknowledgement, ID: "<<ackmsg[msg->getArrivalGate()->getIndex()]->getPid()<<", Port:"<<msg->getArrivalGate()->getIndex()<<" \n";
            ack[msg->getArrivalGate()->getIndex()] = true;
            if((int)(getcontrollertime().dbl()) != (int)(simTime().dbl()))
            {
                setcontrollertime(simTime());
                cMessage *tt_msg = new cMessage();
                sendDelayed(tt_msg,0.0,"poll");
            }
//            delete ackmsg[msg->getArrivalGate()->getIndex()];
		delete (msg);
            return;
        }
        if(msg->arrivedOn("in"))
        {
            if(this->getIndex() == 0)
            {
            	Packet *ack_msg= new Packet();
		ack_msg->setPid(check_and_cast<Packet *>(msg)->getPid());
		ack_msg->setPacket_type(1);
		ack_msg->setKind(1);
    		sendDelayed(ack_msg,0.0/* (double)(intuniform(0,k)/100.0)*/,"Ack_out",msg->getArrivalGate()->getIndex());    
                if(check_and_cast<Packet *>(msg)->getPid() != check_and_cast<Packet *>(msg)->getHid())
                {
//			if(this->getParentModule()->getIndex()==6 && check_and_cast<Packet *>(msg)->getPid()==39)
//				cout<<simTime()<<"Received[39]\n";
                    notifyBookSim(check_and_cast<Packet *>(msg)->getPid(),msg->getArrivalGate()->getIndex());
                    if(check_and_cast<Packet *>(msg)->getPid()==(check_and_cast<Packet *>(msg)->getHid() + check_and_cast<Packet *>(msg)->getSize() - 1))
                    {
                        buff_tail[this->getParentModule()->getIndex()][msg->getArrivalGate()->getIndex()].push_back(check_and_cast<Packet *>(msg));
                        return;
                    }
                    else
                    {
                        buff_body[this->getParentModule()->getIndex()][msg->getArrivalGate()->getIndex()].push_back(check_and_cast<Packet *>(msg));
                        return;
                    }
                }
                else
                    buffer[this->getParentModule()->getIndex()][msg->getArrivalGate()->getIndex()].push_back(make_pair(check_and_cast<Packet *>(msg),simTime()));
            }
            somemsg[msg->getArrivalGate()->getIndex()] = check_and_cast<Packet *>(msg);
            notifyBookSim(somemsg[msg->getArrivalGate()->getIndex()]->getPid(),msg->getArrivalGate()->getIndex());
//            EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ "<<this->getParentModule()->getFullName()<<"."<<this->getFullName()<<":  Received, Message, ID: "<<somemsg[msg->getArrivalGate()->getIndex()]->getPid()<<", Port:"<<msg->getArrivalGate()->getIndex()<<" \n";
            current_time[msg->getArrivalGate()->getIndex()] = simTime();
            if(this->getIndex() == 3)
            {
                tail[this->getParentModule()->getIndex()][msg->getArrivalGate()->getIndex()] = true;
            }
        }
        for(int port = 0;port < 5; port++)
        {
              if(this->getIndex()==3)
              {
                  if(((simTime() - current_time[port]) >= time_slot) && (somemsg[port]!=nullptr))
                  {
                      if(hasvalue[port]==false)
                      {
                          if((replyfrombooksim1[port] = replyfromBookSim(port)) >= 0)
                          {
                              hasvalue[port] = true;
                              lastsent[this->getParentModule()->getIndex()][port] = simTime();
              		  }
                      }
                       if((hasvalue[port]==true) && (ack[replyfrombooksim1[port] - 1]==true))
                       {
                             if(tail[this->getParentModule()->getIndex()][port] == true)
                             {
                                 tail[this->getParentModule()->getIndex()][port] = false;
                                 ack[replyfrombooksim1[port] - 1]=false;
                         	sendDelayed(somemsg[port],k[this->getIndex()]/* (double)(intuniform(0,k)/100.0)*/,"out",(replyfrombooksim1[port]-1));
                                 lastbody[this->getParentModule()->getIndex()][port] = somemsg[port]->getPid();
                                 lasthead[this->getParentModule()->getIndex()][port] = somemsg[port]->getPid();
                                 justarrived[this->getParentModule()->getIndex()][port]=true;
                                 if(somemsg[port]->getSize()==1)
                                 {
                                       hasvalue[port]=false;
                                       ack[replyfrombooksim1[port] - 1] = false;
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
                             if(tail[this->getParentModule()->getIndex()][port] == false)
                             {
                                std::deque<Packet *>::iterator iter = buff_body[this->getParentModule()->getIndex()][port].begin();
                                while(iter!=buff_body[this->getParentModule()->getIndex()][port].end())
                                {
                		    int flag2=0;
                                    if((*iter)->getHid()==lasthead[this->getParentModule()->getIndex()][port] && (*iter)->getPid()==(lastbody[this->getParentModule()->getIndex()][port] + 1))
                                    {
                                    	if(justarrived[this->getParentModule()->getIndex()][port]==true)
                                    	{
                                    		lastsent[this->getParentModule()->getIndex()][port] = simTime();
                                    		justarrived[this->getParentModule()->getIndex()][port] = false;
                    			}
                    			if((simTime() - lastsent[this->getParentModule()->getIndex()][port] >= time_slot) && (ack[replyfrombooksim1[port] - 1]==true))
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
		                                ack[replyfrombooksim1[port] - 1]=false;
			                 	sendDelayed(somemsg[port],k[this->getIndex()]/* (double)(intuniform(0,k)/100.0)*/,"out",(replyfrombooksim1[port]-1));
						std::deque<Packet *>::iterator j = iter;		//TODO: Better fix for iter segF
		                                buff_body[this->getParentModule()->getIndex()][port].erase(iter);
		                                if(j==iter && iter!=buff_body[this->getParentModule()->getIndex()][port].end())
		                                	flag2=0;
	                                	else
		                                	flag2=1;
		                                if(buff_body[this->getParentModule()->getIndex()][port].empty())
		                                    break;
                    			}
                    			else
                    				break;
                                        
                                    }
            				if(flag2==0)
                                    		iter++;
                                }
                                if(tail[this->getParentModule()->getIndex()][port] == false)
                                {
                                    std::deque<Packet *>::iterator iter2 = buff_tail[this->getParentModule()->getIndex()][port].begin();
                                    while(iter2!=buff_tail[this->getParentModule()->getIndex()][port].end())
                                    {
                                        if((*iter2)->getHid()==lasthead[this->getParentModule()->getIndex()][port] && (*iter2)->getPid()==(lastbody[this->getParentModule()->getIndex()][port] + 1))
                                        {
                                		if(justarrived[this->getParentModule()->getIndex()][port]==true)
		                            	{
		                            		lastsent[this->getParentModule()->getIndex()][port] = simTime();
		                            		justarrived[this->getParentModule()->getIndex()][port] = false;
		            			}
		            			if((simTime() - lastsent[this->getParentModule()->getIndex()][port] >= time_slot) && (ack[replyfrombooksim1[port] - 1]==true))
		            			{
							justarrived[this->getParentModule()->getIndex()][port] = true;
							ack[replyfrombooksim1[port] - 1] = false;
							somemsg[port] = new Packet();
							somemsg[port]->setPid((*iter2)->getPid());
							somemsg[port]->setHid((*iter2)->getHid());
							somemsg[port]->setPacket_type((*iter2)->getPacket_type());
							somemsg[port]->setSize((*iter2)->getSize());
							somemsg[port]->setDelay((*iter2)->getDelay());
							delete (*iter2);
							notifyBookSim(somemsg[port]->getPid(),port);
					         	sendDelayed(somemsg[port],k[this->getIndex()]/* (double)(intuniform(0,k)/100.0)*/,"out",(replyfrombooksim1[port]-1));
                                 
							buff_tail[this->getParentModule()->getIndex()][port].erase(iter2);
							hasvalue[port]=false;
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
                    if(/*(ack[port]==true) && */(buffer[this->getParentModule()->getIndex()][port].size()>0) )
                    {
                        if(hasvalue0[port]==false /*&& buff_reply[this->getParentModule()->getIndex()][port].empty()==true*/)
                        {
                            if((replyfrombooksim0[port] = replyfromBookSim(port)) >= 0)
                            {
                                cout<<"\n\t\tSOMETHING WRONG\n";
                                hasvalue0[port] = true;
                            }
                        }
                        if(hasvalue0[port]==false && buff_reply[this->getParentModule()->getIndex()][port].empty()==false)
                        {
                            hasvalue0[port] = true;
                            replyfrombooksim0[port] = buff_reply[this->getParentModule()->getIndex()][port].front();
                            buff_reply[this->getParentModule()->getIndex()][port].pop();
                        }
                        if(hasvalue0[port]==true)
                        {
                            std::deque<pair<Packet *, SimTime> >::iterator iter = buffer[this->getParentModule()->getIndex()][port].begin();
                            while(iter != buffer[this->getParentModule()->getIndex()][port].end())
                            {
                                if(iter->first->getPid()==replyfrombooksim0[port])
                                {
                                    if(((simTime() - iter->second) >= time_slot))
                                    {
                                        if(ack[port]==true)
                                        {
                                            somemsg[port] = iter->first;
                                            hasvalue0[port]=false;
//                                            Packet *ack_msg= new Packet();
//                                            ack_msg->setPid(somemsg[port]->getPid());
//                                            ack_msg->setPacket_type(1);
//                                            ack_msg->setKind(1);
//                                            sendDelayed(ack_msg,0.0/* (double)(intuniform(0,k)/100.0)*/,"Ack_out",port/*0*/);
                                            ack[port] = false;
                                            sendDelayed(somemsg[port],k[this->getIndex()]/* (double)(intuniform(0,k)/100.0)*/,"out",port);
//                                          somemsg[port] = nullptr;
                                            buffer[this->getParentModule()->getIndex()][port].erase(iter);
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
                  if((ack[port]==true) && ((simTime() - current_time[port]) >= time_slot) && (somemsg[port]!=nullptr) && ((replyfrombooksim = replyfromBookSim(port)) >= 0) )
                  {
                        Packet *ack_msg= new Packet();
                        ack_msg->setPid(somemsg[port]->getPid());
                        ack_msg->setPacket_type(1);
                        ack_msg->setKind(1);
                        current_time[port] = simTime();
                        ack[port] = false;
                        sendDelayed(somemsg[port],k[this->getIndex()]/* (double)(intuniform(0,k)/100.0)*/,"out",port);
                        sendDelayed(ack_msg,0.0/* (double)(intuniform(0,k)/100.0)*/,"Ack_out",port/*0*/);
//                      somemsg[port] = nullptr;
                  }
              }
              if(!msg->isSelfMessage())
              {
                  if(this->getIndex()==0)
                  {
                      if((buffer[this->getParentModule()->getIndex()][0].size()>0) || (buffer[this->getParentModule()->getIndex()][1].size()>0) ||(buffer[this->getParentModule()->getIndex()][2].size()>0) ||(buffer[this->getParentModule()->getIndex()][3].size()>0) ||(buffer[this->getParentModule()->getIndex()][4].size()>0))
                      {
                          if((int)(getcontrollertime().dbl()) != (int)(simTime().dbl()))
                          {
//                              EV<<"RESET----\n";
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
//                          if(getmsg(this->getParentModule()->getIndex(),this->getIndex())==true)
//                          {
//                              EV<<"1-["<<this->getParentModule()->getIndex()<<"]["<<this->getIndex()<<"]\n";
                              timer_msg = new cMessage();
                              scheduleAt(simTime() + 1.0 /*+ time_slot + double(intuniform(0, 100))/100.0*/ , timer_msg);
                              setmsg(false,this->getParentModule()->getIndex(),this->getIndex());
//                          }
                      }
                  }
                  else
                  {
                      if(somemsg[0] || somemsg[1] ||somemsg[2] ||somemsg[3] ||somemsg[4])
                        {
                            if((int)(getcontrollertime().dbl()) != (int)(simTime().dbl()))
                            {
//                                EV<<"RESET----\n";
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
//                                  EV<<"2-["<<this->getParentModule()->getIndex()<<"]["<<this->getIndex()<<"]\n";
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
            if(this->getIndex()==0)
              {
                  if((buffer[this->getParentModule()->getIndex()][0].size()>0) || (buffer[this->getParentModule()->getIndex()][1].size()>0) ||(buffer[this->getParentModule()->getIndex()][2].size()>0) ||(buffer[this->getParentModule()->getIndex()][3].size()>0) ||(buffer[this->getParentModule()->getIndex()][4].size()>0))
                  {
                      if((int)(getcontrollertime().dbl()) != (int)(simTime().dbl()))
                      {
//                          EV<<"RESET----\n";
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
//                      if(getmsg(this->getParentModule()->getIndex(),this->getIndex())==true)
//                        {
//                            EV<<"3-["<<this->getParentModule()->getIndex()<<"]["<<this->getIndex()<<"]\n";
                            timer_msg = new cMessage();
                            scheduleAt(simTime() + 1.0 /*+ time_slot + double(intuniform(0, 100))/100.0*/ , timer_msg);
                            setmsg(false,this->getParentModule()->getIndex(),this->getIndex());
//                        }
                  }
              }
              else
              {
                  if(somemsg[0] || somemsg[1] ||somemsg[2] ||somemsg[3] ||somemsg[4])
                    {
                        if((int)(getcontrollertime().dbl()) != (int)(simTime().dbl()))
                        {
//                            EV<<"RESET----\n";
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
//                              EV<<"4-["<<this->getParentModule()->getIndex()<<"]["<<this->getIndex()<<"]\n";
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
    int rv,output=0;
//	if(this->getParentModule()->getIndex()==6 && this->getIndex()==2 && port==1)
//		cout<<simTime()<<"s:Called"<<this->getParentModule()->getIndex()<<"]["<<this->getIndex()<<"]["<<port<<"]\n";
    struct pollfd fds_temp = getfds(this->getParentModule()->getIndex(),this->getIndex(),port);
    rv = poll(&fds_temp,1,0);
    if(rv > 0)
    {
        while ((c = fgetc(getfp(this->getParentModule()->getIndex(),this->getIndex(),port))) != EOF)
        {
            if (c == '\n')
                break;
            else
                output = output*10 + (c - 48);
        }
    }
    if((this->getIndex() == 3) && (rv > 0))
    {
//        cout<<simTime()<<"s:Recv(.5.):["<<this->getParentModule()->getIndex()<<"]["<<this->getIndex()<<"]["<<port<<"]->"<<output<<"<-\n";
          return output;
    }
    else if((this->getIndex() == 0) && (rv > 0))
    {
//        cout<<simTime()<<"s:Recv:["<<this->getParentModule()->getIndex()<<"]["<<this->getIndex()<<"]["<<port<<"]->ID:"<<output<<"\n";
        buff_reply[this->getParentModule()->getIndex()][port].push(output);
        return -1;
    }
    else
    {
            return (rv-1);
    }
}

void mod::notifyBookSim( int id, int port )
{
//    if(this->getParentModule()->getIndex()==11 && this->getIndex()==3 && port==4)
//        cout<<simTime()<<"s: R,C,P:["<<this->getParentModule()->getIndex()<<"]["<<this->getIndex()<<"]["<<port<<"]->ID:"<<id<<"\n";
    std::string myvariable_router = patch::to_string(id);
    myvariable_router.append("\n");
    str_tbs = &myvariable_router[0];
    ::send(getfd(this->getParentModule()->getIndex(),this->getIndex(),port), str_tbs, strlen(str_tbs),0);
    if(this->getIndex()==0 || this->getIndex()==3)
        sethasvalue(this->getParentModule()->getIndex(),this->getIndex(),port);
}

void mod::finish()
{
}
