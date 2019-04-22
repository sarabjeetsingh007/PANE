/*
 * sink.cc

 *
 *  Created on: Aug 3, 2016
 *      Author: sarab
 */

#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include<omnetpp.h>
#include "packets_m.h"
using namespace omnetpp;

class mod_sink : public cSimpleModule
{
    private:
       Packet *somemsg;
//       cStdDev DelayStats;

    public:
       mod_sink();
       virtual ~mod_sink();
       int count = 0;		//Records the number of flits retired at the particular Router
     protected:
       virtual void sendAck(Packet *msg);
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void finish() override;
};
Define_Module(mod_sink);

mod_sink::mod_sink()
{
    somemsg=nullptr;
}

mod_sink::~mod_sink()
{
    delete somemsg;
}
void mod_sink::initialize()
{
}
void mod_sink::handleMessage(cMessage *msg)
{
    somemsg = check_and_cast<Packet *>(msg);
//    EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ SINK: Received, Message, ID: "<<somemsg->getPid()<<", Delay: "<<somemsg->getDelay()<<"s \n";
    count++;
	Packet *counter = new Packet();
	counter->setDelay(simTime().dbl() - somemsg->getDelay());
    sendDelayed(counter,0.0,"countret");		//Send to "PANE/controller" to record the statistics whenever a packet retires
    sendAck(somemsg);		//Send acknowlodgment token
}
void mod_sink::sendAck(Packet *msg)
{
    msg->setPacket_type(1);
    sendDelayed(msg,0.0/*(double)(intuniform(0,10)/100.0)*/,"Ack_out");
}
void mod_sink::finish()
{
    std::cout<<count<<endl;		//Number of packets retired at this Router
//       EV<<"Number of packets received = "<<count<<endl;
//       EV << "Delay, min:    " << DelayStats.getMin() <<"s \n";
//       EV << "Delay, max:    " << DelayStats.getMax() <<"s \n";
//       EV << "Delay, mean:   " << DelayStats.getMean() <<"s \n";
}
