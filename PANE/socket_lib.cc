/*
PANE/socket_lib.cc
Header file
*/
#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <omnetpp.h>
#include <poll.h>
#define numRouters 16		//Represents the number of Routers in the network
#define numClients 4		//Represents the division of a Router

using namespace omnetpp;

const char * ADDR[numRouters][numClients][5];		//UNIX Domain Socket Path Address

int fromlen;		//(UNIX DOMAIN SOCKET: addrlen) contains the size of structure pointed by the socket address
/*register*/ int s[numRouters][numClients][5], ns[numRouters][numClients][5], len;		//(UNIX DOMAIN SOCKET parameters)
struct sockaddr_un saun[numRouters][numClients][5], fsaun[numRouters][numClients][5];		//(UNIX DOMAIN SOCKET parameters)

//Pollfds
struct pollfd fds[numRouters][4][5];		//(UNIX DOMAIN SOCKET) Holds the set of file descriptors(Core->GenFlit) to be monitored by poll (http://man7.org/linux/man-pages/man2/poll.2.html)
FILE *fp[numRouters][numClients][5];		//(UNIX DOMAIN SOCKET) file pointer

SimTime currenttime;		//Represents last time at which controller was evaluated

bool hasmsg[numRouters][numClients];		//Flip value to remove redundancy of poll msg in an epoch

int hasvalue[numRouters][numClients][5];	//Counter for data written in the RCP-data socket (Sensible for only clients, C=0 & C=3)

pollfd getfds(int R,int C,int P)
{
	return fds[R][C][P];
}

FILE *getfp(int R,int C,int P)
{
	return fp[R][C][P];
}

void setup_pollfd()
{
	int R,C,P;
	for(R=0;R<numRouters;R++)
	{
		for(C=0;C<numClients;C++)
		{
		    for(P=0;P<5;P++)
		    {
				fp[R][C][P] = fdopen(ns[R][C][P], "r");
				fds[R][C][P].fd = ns[R][C][P];                  //FDS-Client
				fds[R][C][P].events = POLLIN;
		    }
		}
	}
}

void setcontrollertime(SimTime current_time)
{
	currenttime = current_time;
}

SimTime getcontrollertime()
{
	return currenttime;
}

bool getmsg(int R,int C)
{
	return hasmsg[R][C];
}

void setmsg(bool value,int R,int C)
{
	hasmsg[R][C] = value;
}

int gethasvalue(int R,int C,int P)
{
	return hasvalue[R][C][P];
}

void sethasvalue(int R,int C,int P)
{
	++hasvalue[R][C][P];
}

void resethasvalue(int R,int C,int P)
{
	hasvalue[R][C][P]=0;
}

void create_socket(int R,int C,int P)
{
	if ((s[R][C][P] = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)		//creates a socket
    {
		perror("server: socket");
		exit(1);
    }
    saun[R][C][P].sun_family = AF_UNIX;		//set type of socket to be UNIX DOMAIN
    strcpy(saun[R][C][P].sun_path, ADDR[R][C][P]);

    unlink(ADDR[R][C][P]);		//unlink from any other connection
    len = sizeof(saun[R][C][P].sun_family) + strlen(saun[R][C][P].sun_path);

    if (bind(s[R][C][P],(struct sockaddr *) &saun[R][C][P], len) < 0)		//binds socket to the address
    {
		perror("server: bind");
		exit(1);
    }
    if (listen(s[R][C][P], 5) < 0)		//listen for incoming connections from any client programs
    {
		perror("server: listen");
		exit(1);
    }
    if ((ns[R][C][P] = accept(s[R][C][P], (struct sockaddr *) &fsaun[R][C][P],(socklen_t*) &fromlen)) < 0)		//accept a connection from a client
    {
		perror("server: accept");
		exit(1);
    }
}

int getfd(int R,int C,int P)
{ 
 	return ns[R][C][P];
}

void assignsocklist()
{
	ADDR [0][0][0] = "../socket_r0_c0_i0";
ADDR [0][0][1] = "../socket_r0_c0_i1";
ADDR [0][0][2] = "../socket_r0_c0_i2";
ADDR [0][0][3] = "../socket_r0_c0_i3";
ADDR [0][0][4] = "../socket_r0_c0_i4";
ADDR [0][1][0] = "../socket_r0_c1_i0";
ADDR [0][1][1] = "../socket_r0_c1_i1";
ADDR [0][1][2] = "../socket_r0_c1_i2";
ADDR [0][1][3] = "../socket_r0_c1_i3";
ADDR [0][1][4] = "../socket_r0_c1_i4";
ADDR [0][2][0] = "../socket_r0_c2_i0";
ADDR [0][2][1] = "../socket_r0_c2_i1";
ADDR [0][2][2] = "../socket_r0_c2_i2";
ADDR [0][2][3] = "../socket_r0_c2_i3";
ADDR [0][2][4] = "../socket_r0_c2_i4";
ADDR [0][3][0] = "../socket_r0_c3_i0";
ADDR [0][3][1] = "../socket_r0_c3_i1";
ADDR [0][3][2] = "../socket_r0_c3_i2";
ADDR [0][3][3] = "../socket_r0_c3_i3";
ADDR [0][3][4] = "../socket_r0_c3_i4";
ADDR [1][0][0] = "../socket_r1_c0_i0";
ADDR [1][0][1] = "../socket_r1_c0_i1";
ADDR [1][0][2] = "../socket_r1_c0_i2";
ADDR [1][0][3] = "../socket_r1_c0_i3";
ADDR [1][0][4] = "../socket_r1_c0_i4";
ADDR [1][1][0] = "../socket_r1_c1_i0";
ADDR [1][1][1] = "../socket_r1_c1_i1";
ADDR [1][1][2] = "../socket_r1_c1_i2";
ADDR [1][1][3] = "../socket_r1_c1_i3";
ADDR [1][1][4] = "../socket_r1_c1_i4";
ADDR [1][2][0] = "../socket_r1_c2_i0";
ADDR [1][2][1] = "../socket_r1_c2_i1";
ADDR [1][2][2] = "../socket_r1_c2_i2";
ADDR [1][2][3] = "../socket_r1_c2_i3";
ADDR [1][2][4] = "../socket_r1_c2_i4";
ADDR [1][3][0] = "../socket_r1_c3_i0";
ADDR [1][3][1] = "../socket_r1_c3_i1";
ADDR [1][3][2] = "../socket_r1_c3_i2";
ADDR [1][3][3] = "../socket_r1_c3_i3";
ADDR [1][3][4] = "../socket_r1_c3_i4";
ADDR [2][0][0] = "../socket_r2_c0_i0";
ADDR [2][0][1] = "../socket_r2_c0_i1";
ADDR [2][0][2] = "../socket_r2_c0_i2";
ADDR [2][0][3] = "../socket_r2_c0_i3";
ADDR [2][0][4] = "../socket_r2_c0_i4";
ADDR [2][1][0] = "../socket_r2_c1_i0";
ADDR [2][1][1] = "../socket_r2_c1_i1";
ADDR [2][1][2] = "../socket_r2_c1_i2";
ADDR [2][1][3] = "../socket_r2_c1_i3";
ADDR [2][1][4] = "../socket_r2_c1_i4";
ADDR [2][2][0] = "../socket_r2_c2_i0";
ADDR [2][2][1] = "../socket_r2_c2_i1";
ADDR [2][2][2] = "../socket_r2_c2_i2";
ADDR [2][2][3] = "../socket_r2_c2_i3";
ADDR [2][2][4] = "../socket_r2_c2_i4";
ADDR [2][3][0] = "../socket_r2_c3_i0";
ADDR [2][3][1] = "../socket_r2_c3_i1";
ADDR [2][3][2] = "../socket_r2_c3_i2";
ADDR [2][3][3] = "../socket_r2_c3_i3";
ADDR [2][3][4] = "../socket_r2_c3_i4";
ADDR [3][0][0] = "../socket_r3_c0_i0";
ADDR [3][0][1] = "../socket_r3_c0_i1";
ADDR [3][0][2] = "../socket_r3_c0_i2";
ADDR [3][0][3] = "../socket_r3_c0_i3";
ADDR [3][0][4] = "../socket_r3_c0_i4";
ADDR [3][1][0] = "../socket_r3_c1_i0";
ADDR [3][1][1] = "../socket_r3_c1_i1";
ADDR [3][1][2] = "../socket_r3_c1_i2";
ADDR [3][1][3] = "../socket_r3_c1_i3";
ADDR [3][1][4] = "../socket_r3_c1_i4";
ADDR [3][2][0] = "../socket_r3_c2_i0";
ADDR [3][2][1] = "../socket_r3_c2_i1";
ADDR [3][2][2] = "../socket_r3_c2_i2";
ADDR [3][2][3] = "../socket_r3_c2_i3";
ADDR [3][2][4] = "../socket_r3_c2_i4";
ADDR [3][3][0] = "../socket_r3_c3_i0";
ADDR [3][3][1] = "../socket_r3_c3_i1";
ADDR [3][3][2] = "../socket_r3_c3_i2";
ADDR [3][3][3] = "../socket_r3_c3_i3";
ADDR [3][3][4] = "../socket_r3_c3_i4";
ADDR [4][0][0] = "../socket_r4_c0_i0";
ADDR [4][0][1] = "../socket_r4_c0_i1";
ADDR [4][0][2] = "../socket_r4_c0_i2";
ADDR [4][0][3] = "../socket_r4_c0_i3";
ADDR [4][0][4] = "../socket_r4_c0_i4";
ADDR [4][1][0] = "../socket_r4_c1_i0";
ADDR [4][1][1] = "../socket_r4_c1_i1";
ADDR [4][1][2] = "../socket_r4_c1_i2";
ADDR [4][1][3] = "../socket_r4_c1_i3";
ADDR [4][1][4] = "../socket_r4_c1_i4";
ADDR [4][2][0] = "../socket_r4_c2_i0";
ADDR [4][2][1] = "../socket_r4_c2_i1";
ADDR [4][2][2] = "../socket_r4_c2_i2";
ADDR [4][2][3] = "../socket_r4_c2_i3";
ADDR [4][2][4] = "../socket_r4_c2_i4";
ADDR [4][3][0] = "../socket_r4_c3_i0";
ADDR [4][3][1] = "../socket_r4_c3_i1";
ADDR [4][3][2] = "../socket_r4_c3_i2";
ADDR [4][3][3] = "../socket_r4_c3_i3";
ADDR [4][3][4] = "../socket_r4_c3_i4";
ADDR [5][0][0] = "../socket_r5_c0_i0";
ADDR [5][0][1] = "../socket_r5_c0_i1";
ADDR [5][0][2] = "../socket_r5_c0_i2";
ADDR [5][0][3] = "../socket_r5_c0_i3";
ADDR [5][0][4] = "../socket_r5_c0_i4";
ADDR [5][1][0] = "../socket_r5_c1_i0";
ADDR [5][1][1] = "../socket_r5_c1_i1";
ADDR [5][1][2] = "../socket_r5_c1_i2";
ADDR [5][1][3] = "../socket_r5_c1_i3";
ADDR [5][1][4] = "../socket_r5_c1_i4";
ADDR [5][2][0] = "../socket_r5_c2_i0";
ADDR [5][2][1] = "../socket_r5_c2_i1";
ADDR [5][2][2] = "../socket_r5_c2_i2";
ADDR [5][2][3] = "../socket_r5_c2_i3";
ADDR [5][2][4] = "../socket_r5_c2_i4";
ADDR [5][3][0] = "../socket_r5_c3_i0";
ADDR [5][3][1] = "../socket_r5_c3_i1";
ADDR [5][3][2] = "../socket_r5_c3_i2";
ADDR [5][3][3] = "../socket_r5_c3_i3";
ADDR [5][3][4] = "../socket_r5_c3_i4";
ADDR [6][0][0] = "../socket_r6_c0_i0";
ADDR [6][0][1] = "../socket_r6_c0_i1";
ADDR [6][0][2] = "../socket_r6_c0_i2";
ADDR [6][0][3] = "../socket_r6_c0_i3";
ADDR [6][0][4] = "../socket_r6_c0_i4";
ADDR [6][1][0] = "../socket_r6_c1_i0";
ADDR [6][1][1] = "../socket_r6_c1_i1";
ADDR [6][1][2] = "../socket_r6_c1_i2";
ADDR [6][1][3] = "../socket_r6_c1_i3";
ADDR [6][1][4] = "../socket_r6_c1_i4";
ADDR [6][2][0] = "../socket_r6_c2_i0";
ADDR [6][2][1] = "../socket_r6_c2_i1";
ADDR [6][2][2] = "../socket_r6_c2_i2";
ADDR [6][2][3] = "../socket_r6_c2_i3";
ADDR [6][2][4] = "../socket_r6_c2_i4";
ADDR [6][3][0] = "../socket_r6_c3_i0";
ADDR [6][3][1] = "../socket_r6_c3_i1";
ADDR [6][3][2] = "../socket_r6_c3_i2";
ADDR [6][3][3] = "../socket_r6_c3_i3";
ADDR [6][3][4] = "../socket_r6_c3_i4";
ADDR [7][0][0] = "../socket_r7_c0_i0";
ADDR [7][0][1] = "../socket_r7_c0_i1";
ADDR [7][0][2] = "../socket_r7_c0_i2";
ADDR [7][0][3] = "../socket_r7_c0_i3";
ADDR [7][0][4] = "../socket_r7_c0_i4";
ADDR [7][1][0] = "../socket_r7_c1_i0";
ADDR [7][1][1] = "../socket_r7_c1_i1";
ADDR [7][1][2] = "../socket_r7_c1_i2";
ADDR [7][1][3] = "../socket_r7_c1_i3";
ADDR [7][1][4] = "../socket_r7_c1_i4";
ADDR [7][2][0] = "../socket_r7_c2_i0";
ADDR [7][2][1] = "../socket_r7_c2_i1";
ADDR [7][2][2] = "../socket_r7_c2_i2";
ADDR [7][2][3] = "../socket_r7_c2_i3";
ADDR [7][2][4] = "../socket_r7_c2_i4";
ADDR [7][3][0] = "../socket_r7_c3_i0";
ADDR [7][3][1] = "../socket_r7_c3_i1";
ADDR [7][3][2] = "../socket_r7_c3_i2";
ADDR [7][3][3] = "../socket_r7_c3_i3";
ADDR [7][3][4] = "../socket_r7_c3_i4";
ADDR [8][0][0] = "../socket_r8_c0_i0";
ADDR [8][0][1] = "../socket_r8_c0_i1";
ADDR [8][0][2] = "../socket_r8_c0_i2";
ADDR [8][0][3] = "../socket_r8_c0_i3";
ADDR [8][0][4] = "../socket_r8_c0_i4";
ADDR [8][1][0] = "../socket_r8_c1_i0";
ADDR [8][1][1] = "../socket_r8_c1_i1";
ADDR [8][1][2] = "../socket_r8_c1_i2";
ADDR [8][1][3] = "../socket_r8_c1_i3";
ADDR [8][1][4] = "../socket_r8_c1_i4";
ADDR [8][2][0] = "../socket_r8_c2_i0";
ADDR [8][2][1] = "../socket_r8_c2_i1";
ADDR [8][2][2] = "../socket_r8_c2_i2";
ADDR [8][2][3] = "../socket_r8_c2_i3";
ADDR [8][2][4] = "../socket_r8_c2_i4";
ADDR [8][3][0] = "../socket_r8_c3_i0";
ADDR [8][3][1] = "../socket_r8_c3_i1";
ADDR [8][3][2] = "../socket_r8_c3_i2";
ADDR [8][3][3] = "../socket_r8_c3_i3";
ADDR [8][3][4] = "../socket_r8_c3_i4";
ADDR [9][0][0] = "../socket_r9_c0_i0";
ADDR [9][0][1] = "../socket_r9_c0_i1";
ADDR [9][0][2] = "../socket_r9_c0_i2";
ADDR [9][0][3] = "../socket_r9_c0_i3";
ADDR [9][0][4] = "../socket_r9_c0_i4";
ADDR [9][1][0] = "../socket_r9_c1_i0";
ADDR [9][1][1] = "../socket_r9_c1_i1";
ADDR [9][1][2] = "../socket_r9_c1_i2";
ADDR [9][1][3] = "../socket_r9_c1_i3";
ADDR [9][1][4] = "../socket_r9_c1_i4";
ADDR [9][2][0] = "../socket_r9_c2_i0";
ADDR [9][2][1] = "../socket_r9_c2_i1";
ADDR [9][2][2] = "../socket_r9_c2_i2";
ADDR [9][2][3] = "../socket_r9_c2_i3";
ADDR [9][2][4] = "../socket_r9_c2_i4";
ADDR [9][3][0] = "../socket_r9_c3_i0";
ADDR [9][3][1] = "../socket_r9_c3_i1";
ADDR [9][3][2] = "../socket_r9_c3_i2";
ADDR [9][3][3] = "../socket_r9_c3_i3";
ADDR [9][3][4] = "../socket_r9_c3_i4";
ADDR [10][0][0] = "../socket_r10_c0_i0";
ADDR [10][0][1] = "../socket_r10_c0_i1";
ADDR [10][0][2] = "../socket_r10_c0_i2";
ADDR [10][0][3] = "../socket_r10_c0_i3";
ADDR [10][0][4] = "../socket_r10_c0_i4";
ADDR [10][1][0] = "../socket_r10_c1_i0";
ADDR [10][1][1] = "../socket_r10_c1_i1";
ADDR [10][1][2] = "../socket_r10_c1_i2";
ADDR [10][1][3] = "../socket_r10_c1_i3";
ADDR [10][1][4] = "../socket_r10_c1_i4";
ADDR [10][2][0] = "../socket_r10_c2_i0";
ADDR [10][2][1] = "../socket_r10_c2_i1";
ADDR [10][2][2] = "../socket_r10_c2_i2";
ADDR [10][2][3] = "../socket_r10_c2_i3";
ADDR [10][2][4] = "../socket_r10_c2_i4";
ADDR [10][3][0] = "../socket_r10_c3_i0";
ADDR [10][3][1] = "../socket_r10_c3_i1";
ADDR [10][3][2] = "../socket_r10_c3_i2";
ADDR [10][3][3] = "../socket_r10_c3_i3";
ADDR [10][3][4] = "../socket_r10_c3_i4";
ADDR [11][0][0] = "../socket_r11_c0_i0";
ADDR [11][0][1] = "../socket_r11_c0_i1";
ADDR [11][0][2] = "../socket_r11_c0_i2";
ADDR [11][0][3] = "../socket_r11_c0_i3";
ADDR [11][0][4] = "../socket_r11_c0_i4";
ADDR [11][1][0] = "../socket_r11_c1_i0";
ADDR [11][1][1] = "../socket_r11_c1_i1";
ADDR [11][1][2] = "../socket_r11_c1_i2";
ADDR [11][1][3] = "../socket_r11_c1_i3";
ADDR [11][1][4] = "../socket_r11_c1_i4";
ADDR [11][2][0] = "../socket_r11_c2_i0";
ADDR [11][2][1] = "../socket_r11_c2_i1";
ADDR [11][2][2] = "../socket_r11_c2_i2";
ADDR [11][2][3] = "../socket_r11_c2_i3";
ADDR [11][2][4] = "../socket_r11_c2_i4";
ADDR [11][3][0] = "../socket_r11_c3_i0";
ADDR [11][3][1] = "../socket_r11_c3_i1";
ADDR [11][3][2] = "../socket_r11_c3_i2";
ADDR [11][3][3] = "../socket_r11_c3_i3";
ADDR [11][3][4] = "../socket_r11_c3_i4";
ADDR [12][0][0] = "../socket_r12_c0_i0";
ADDR [12][0][1] = "../socket_r12_c0_i1";
ADDR [12][0][2] = "../socket_r12_c0_i2";
ADDR [12][0][3] = "../socket_r12_c0_i3";
ADDR [12][0][4] = "../socket_r12_c0_i4";
ADDR [12][1][0] = "../socket_r12_c1_i0";
ADDR [12][1][1] = "../socket_r12_c1_i1";
ADDR [12][1][2] = "../socket_r12_c1_i2";
ADDR [12][1][3] = "../socket_r12_c1_i3";
ADDR [12][1][4] = "../socket_r12_c1_i4";
ADDR [12][2][0] = "../socket_r12_c2_i0";
ADDR [12][2][1] = "../socket_r12_c2_i1";
ADDR [12][2][2] = "../socket_r12_c2_i2";
ADDR [12][2][3] = "../socket_r12_c2_i3";
ADDR [12][2][4] = "../socket_r12_c2_i4";
ADDR [12][3][0] = "../socket_r12_c3_i0";
ADDR [12][3][1] = "../socket_r12_c3_i1";
ADDR [12][3][2] = "../socket_r12_c3_i2";
ADDR [12][3][3] = "../socket_r12_c3_i3";
ADDR [12][3][4] = "../socket_r12_c3_i4";
ADDR [13][0][0] = "../socket_r13_c0_i0";
ADDR [13][0][1] = "../socket_r13_c0_i1";
ADDR [13][0][2] = "../socket_r13_c0_i2";
ADDR [13][0][3] = "../socket_r13_c0_i3";
ADDR [13][0][4] = "../socket_r13_c0_i4";
ADDR [13][1][0] = "../socket_r13_c1_i0";
ADDR [13][1][1] = "../socket_r13_c1_i1";
ADDR [13][1][2] = "../socket_r13_c1_i2";
ADDR [13][1][3] = "../socket_r13_c1_i3";
ADDR [13][1][4] = "../socket_r13_c1_i4";
ADDR [13][2][0] = "../socket_r13_c2_i0";
ADDR [13][2][1] = "../socket_r13_c2_i1";
ADDR [13][2][2] = "../socket_r13_c2_i2";
ADDR [13][2][3] = "../socket_r13_c2_i3";
ADDR [13][2][4] = "../socket_r13_c2_i4";
ADDR [13][3][0] = "../socket_r13_c3_i0";
ADDR [13][3][1] = "../socket_r13_c3_i1";
ADDR [13][3][2] = "../socket_r13_c3_i2";
ADDR [13][3][3] = "../socket_r13_c3_i3";
ADDR [13][3][4] = "../socket_r13_c3_i4";
ADDR [14][0][0] = "../socket_r14_c0_i0";
ADDR [14][0][1] = "../socket_r14_c0_i1";
ADDR [14][0][2] = "../socket_r14_c0_i2";
ADDR [14][0][3] = "../socket_r14_c0_i3";
ADDR [14][0][4] = "../socket_r14_c0_i4";
ADDR [14][1][0] = "../socket_r14_c1_i0";
ADDR [14][1][1] = "../socket_r14_c1_i1";
ADDR [14][1][2] = "../socket_r14_c1_i2";
ADDR [14][1][3] = "../socket_r14_c1_i3";
ADDR [14][1][4] = "../socket_r14_c1_i4";
ADDR [14][2][0] = "../socket_r14_c2_i0";
ADDR [14][2][1] = "../socket_r14_c2_i1";
ADDR [14][2][2] = "../socket_r14_c2_i2";
ADDR [14][2][3] = "../socket_r14_c2_i3";
ADDR [14][2][4] = "../socket_r14_c2_i4";
ADDR [14][3][0] = "../socket_r14_c3_i0";
ADDR [14][3][1] = "../socket_r14_c3_i1";
ADDR [14][3][2] = "../socket_r14_c3_i2";
ADDR [14][3][3] = "../socket_r14_c3_i3";
ADDR [14][3][4] = "../socket_r14_c3_i4";
ADDR [15][0][0] = "../socket_r15_c0_i0";
ADDR [15][0][1] = "../socket_r15_c0_i1";
ADDR [15][0][2] = "../socket_r15_c0_i2";
ADDR [15][0][3] = "../socket_r15_c0_i3";
ADDR [15][0][4] = "../socket_r15_c0_i4";
ADDR [15][1][0] = "../socket_r15_c1_i0";
ADDR [15][1][1] = "../socket_r15_c1_i1";
ADDR [15][1][2] = "../socket_r15_c1_i2";
ADDR [15][1][3] = "../socket_r15_c1_i3";
ADDR [15][1][4] = "../socket_r15_c1_i4";
ADDR [15][2][0] = "../socket_r15_c2_i0";
ADDR [15][2][1] = "../socket_r15_c2_i1";
ADDR [15][2][2] = "../socket_r15_c2_i2";
ADDR [15][2][3] = "../socket_r15_c2_i3";
ADDR [15][2][4] = "../socket_r15_c2_i4";
ADDR [15][3][0] = "../socket_r15_c3_i0";
ADDR [15][3][1] = "../socket_r15_c3_i1";
ADDR [15][3][2] = "../socket_r15_c3_i2";
ADDR [15][3][3] = "../socket_r15_c3_i3";
ADDR [15][3][4] = "../socket_r15_c3_i4";
}
