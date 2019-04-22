/*
 * source.cc
 *
 *  Created on: Aug 3, 2016
 *      Author: sarab
 */
#include<string.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include<omnetpp.h>
#include "packets_m.h"
using namespace omnetpp;


class mod_src : public cSimpleModule
{
    private:
       bool ack;
       Packet *somemsg;
       SimTime current_time;
    public:
       mod_src();
       virtual ~mod_src();
//       cOutVector SourceVector;
//       cLongHistogram SourceStats;
       int count;
    protected:
//       virtual void generateMessage();
        virtual void initialize() override;
//        void timer();
        void init_socket();
        virtual void handleMessage(cMessage *msg) override;
        virtual void finish() override;
};

Define_Module(mod_src);

mod_src::mod_src()
{
    ack=true;
}

mod_src::~mod_src()
{//..
}

void mod_src::initialize()
{
    count=0;
}
void mod_src::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("Ack_in"))
    {
//        timer();
//        EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ SOURCE["<<this->getIndex()<<"]: Received, Acknowledgement\n";//, ID: "<<ttmsg->getPid()<<" \n";
        sendDelayed(msg,0.0,"out_controller");
    }
    else if(msg->arrivedOn("in_controller"))
    {
        somemsg = check_and_cast<Packet *>(msg);
        count++;
//        EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ SOURCE["<<this->getIndex()<<"]: Received, Message, ID: "<<somemsg->getPid()<<" \n";
        sendDelayed(somemsg,0.0/*(double)(intuniform(0,10)/100.0)*/,"out");
//        delete ttmsg;
    }
}
void mod_src::finish()
{
//       EV<<"FINISH:\nNumber of packets generated = "<<count<<"\n";
    std::cout<<count<<"\t\t\t";
}




