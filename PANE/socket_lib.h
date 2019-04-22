#ifndef sock_lib
#define sock_lib

#include <omnetpp.h>
using namespace omnetpp;
//Defining address
void assignsocklist();

//Src
//int create_socket_src();
//void setfd_src(const int& val);
//int getfd_src();

//Timer
//int create_socket_timer();
//void setfd_timer(const int& val);
//int getfd_timer();

//Clients
void create_socket(int R,int C,int P);
//void setfd(const int& val,int R,int C, int P);
int getfd(int R,int C,int P);

//Setup File pointer (fpopen) for pollfd
void setup_pollfd();
pollfd getfds(int R,int C,int P);
FILE *getfp(int R,int C,int P);

//Delimiter Addition
void sethasvalue(int R,int C,int P);
int gethasvalue(int R,int C,int P);
void resethasvalue(int R,int C,int P);

//HasSomemsg
void setmsg(bool value,int R,int C);
bool getmsg(int R,int C);

//Controller_Time
bool setcontrollertime(SimTime current_time);
SimTime getcontrollertime();

//////Toy Program
////Clients
//void create_socket2(int R,int C,int P);
//int getfd2(int R,int C,int P);
//void assignsocklist2();
#endif
