/*
PANE/socket_lib.h
Header file
*/
#ifndef sock_lib
#define sock_lib

#include <omnetpp.h>
using namespace omnetpp;

void assignsocklist();		//Defining address

void create_socket(int R,int C,int P);		//Setup RCP-data sockets
int getfd(int R,int C,int P);		//Returns file descriptor pointing to the RCP-data socket

void setup_pollfd();		//Setup File pointer (fpopen) for pollfd
pollfd getfds(int R,int C,int P);		//Get file pointer set
FILE *getfp(int R,int C,int P);		//Get file pointer

void sethasvalue(int R,int C,int P);		//Sets the counter for data written in the RCP-data socket (Sensible for only clients, C=0 & C=3)
int gethasvalue(int R,int C,int P);		//Returns the counter value
void resethasvalue(int R,int C,int P);		//Resets the counter value

void setmsg(bool value,int R,int C);		//Sets the flip value indicating status of poll msg in the particular epoch
bool getmsg(int R,int C);		//Returns the flip value

//Controller_Time
void setcontrollertime(SimTime current_time);		//Sets controller time flag
SimTime getcontrollertime();			//Returns controller time flag

#endif
