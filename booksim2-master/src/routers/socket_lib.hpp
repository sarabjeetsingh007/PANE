#ifndef socket_lib
#define socket_lib

//Defining address
void assignsocklist();

//Src
int create_socket_src();
void setfd_src(const int& val);
int getfd_src();

//Timer
int create_socket_timer();
void setfd_timer(const int& val);
int getfd_timer();

//Clients
int create_socket(int R,int C,int P);
void setfd(const int& val,int R,int C, int P);
int getfd(int R,int C,int P);

//Transfer Counter

int getTransferCounter(int R,int C, int P);	//Get number of flits tranferred by PANE that cycle.
void setTransferCounter(int R,int C, int P, int value);	//Set data tranferred by PANE counter = value.
void resetTransferCounter();	//Reset data tranferred by PANE counter. 
#endif
