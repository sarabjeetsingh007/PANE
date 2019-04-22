/*PANE Support*/
#ifndef socket_lib
#define socket_lib

void assignsocklist();		//Defining address

int create_socket_src();		//Setup Packet generation socket
void setfd_src(const int& val);		
int getfd_src();

int create_socket_timer();		//Setup Epoch increment socket
void setfd_timer(const int& val);
int getfd_timer();

int create_socket(int R,int C,int P);		//Setup RCP-data sockets
void setfd(const int& val,int R,int C, int P);
int getfd(int R,int C,int P);

int getTransferCounter(int R,int C, int P);	//Counter to get number of flits tranferred by PANE that cycle.
void setTransferCounter(int R,int C, int P, int value);	//Set data tranferred by PANE counter = value.
void resetTransferCounter();	//Reset data tranferred by PANE counter. 
#endif
