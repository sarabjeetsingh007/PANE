
#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
//using namespace std;
#define numRouters 64
#define numClients 4


#define ADDR_SRC     "../../socket_src"

#define ADDR_TIMER     "../../socket_timer"
	
int fd[numRouters][numClients][5];
int sd[numRouters][numClients][5];
struct sockaddr_un saun[numRouters][numClients][5];

int fd_src;
int sd_src;
struct sockaddr_un saun_src;

int fd_timer;
int sd_timer;
struct sockaddr_un saun_timer;

const char * ADDR[numRouters][numClients][5];

int transfer_counter[numRouters][numClients][5];		//*Sarab

int getTransferCounter(int R,int C, int P) { return transfer_counter[R][C][P];}		//*Sarab

void setTransferCounter(int R,int C, int P, int value) { transfer_counter[R][C][P]=value;}	//*Sarab

//Transfer Counter
void resetTransferCounter() 
{
	for(int R = 0; R<numRouters; R++)
	{
		for(int C = 0; C<numClients; C++)
		{
			for(int P = 0; P<5; P++)
			{
				transfer_counter[R][C][P]=0;
			}
		}
	}
}

//Src
int create_socket_src()
{
	int len;
	

	if ((sd_src = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
	perror("SRC: socket");
	exit(1);
	}

	saun_src.sun_family = AF_UNIX;
	strcpy(saun_src.sun_path, ADDR_SRC);

	len = sizeof(saun_src.sun_family) + strlen(saun_src.sun_path);

	if (connect(sd_src, (struct sockaddr *) &saun_src, len) < 0)
	{
	perror("SRC: connect");
	exit(1);
	}
	printf("Master: Running SRC....\n");
	return sd_src;
}

void setfd_src(const int& val)
{
	fd_src = val;
}
int getfd_src()
{
        return fd_src;
}

//Timer
int create_socket_timer()
{
	int len;
	

	if ((sd_timer = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
	perror("timer: socket");
	exit(1);
	}

	saun_timer.sun_family = AF_UNIX;
	strcpy(saun_timer.sun_path, ADDR_TIMER);

	len = sizeof(saun_timer.sun_family) + strlen(saun_timer.sun_path);

	if (connect(sd_timer, (struct sockaddr *) &saun_timer, len) < 0)
	{
	perror("timer: connect");
	exit(1);
	}
	printf("Master: Running timer....\n");
	return sd_timer;
}

void setfd_timer(const int& val)
{
	fd_timer = val;
}
int getfd_timer()
{
        return fd_timer;
}


//Clients
int create_socket(int R,int C,int P)
{
	
	int len; 
	 if ((sd[R][C][P] = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	 { 
		perror("socket");
//		printf("Client[%d][%d][%d]: socket error",R,C,P);exit(1); 
	 }
//	int on=1;
//	if((setsockopt(sd[R][C][P], SOL_SOCKET,  SO_REUSEADDR,(char *)&on, sizeof(on))) < 0)		//Can remove
//	{
//		perror("setsockopt() failed");
//		exit(1);
//	}
	 saun[R][C][P].sun_family = AF_UNIX;
	 strcpy(saun[R][C][P].sun_path, ADDR[R][C][P]);
	 len = sizeof(saun[R][C][P].sun_family) + strlen(saun[R][C][P].sun_path); 

	 while(1){
		if (connect(sd[R][C][P], (struct sockaddr *) &saun[R][C][P], len) < 0) { continue;}
		break;
	 }

//	 if (connect(sd[R][C][P], (struct sockaddr *) &saun[R][C][P], len) < 0) 
//	 { 
//		perror("connect");
//		printf("Client[%d][%d][%d]: connect error",R,C,P);
//		 exit(1); 
//	 }
	 return sd[R][C][P];
	
}

void setfd(const int& val,int R,int C, int P)
 { 
 	fd[R][C][P] = val;
 }

int getfd(int R,int C,int P)
 { 
 	return fd[R][C][P];
 }


void assignsocklist()
{

	ADDR [0][0][0] = "../../socket_r0_c0_i0";
	ADDR [0][0][1] = "../../socket_r0_c0_i1";
	ADDR [0][0][2] = "../../socket_r0_c0_i2";
	ADDR [0][0][3] = "../../socket_r0_c0_i3";
	ADDR [0][0][4] = "../../socket_r0_c0_i4";
	ADDR [0][1][0] = "../../socket_r0_c1_i0";
	ADDR [0][1][1] = "../../socket_r0_c1_i1";
	ADDR [0][1][2] = "../../socket_r0_c1_i2";
	ADDR [0][1][3] = "../../socket_r0_c1_i3";
	ADDR [0][1][4] = "../../socket_r0_c1_i4";
	ADDR [0][2][0] = "../../socket_r0_c2_i0";
	ADDR [0][2][1] = "../../socket_r0_c2_i1";
	ADDR [0][2][2] = "../../socket_r0_c2_i2";
	ADDR [0][2][3] = "../../socket_r0_c2_i3";
	ADDR [0][2][4] = "../../socket_r0_c2_i4";
	ADDR [0][3][0] = "../../socket_r0_c3_i0";
	ADDR [0][3][1] = "../../socket_r0_c3_i1";
	ADDR [0][3][2] = "../../socket_r0_c3_i2";
	ADDR [0][3][3] = "../../socket_r0_c3_i3";
	ADDR [0][3][4] = "../../socket_r0_c3_i4";
	ADDR [1][0][0] = "../../socket_r1_c0_i0";
	ADDR [1][0][1] = "../../socket_r1_c0_i1";
	ADDR [1][0][2] = "../../socket_r1_c0_i2";
	ADDR [1][0][3] = "../../socket_r1_c0_i3";
	ADDR [1][0][4] = "../../socket_r1_c0_i4";
	ADDR [1][1][0] = "../../socket_r1_c1_i0";
	ADDR [1][1][1] = "../../socket_r1_c1_i1";
	ADDR [1][1][2] = "../../socket_r1_c1_i2";
	ADDR [1][1][3] = "../../socket_r1_c1_i3";
	ADDR [1][1][4] = "../../socket_r1_c1_i4";
	ADDR [1][2][0] = "../../socket_r1_c2_i0";
	ADDR [1][2][1] = "../../socket_r1_c2_i1";
	ADDR [1][2][2] = "../../socket_r1_c2_i2";
	ADDR [1][2][3] = "../../socket_r1_c2_i3";
	ADDR [1][2][4] = "../../socket_r1_c2_i4";
	ADDR [1][3][0] = "../../socket_r1_c3_i0";
	ADDR [1][3][1] = "../../socket_r1_c3_i1";
	ADDR [1][3][2] = "../../socket_r1_c3_i2";
	ADDR [1][3][3] = "../../socket_r1_c3_i3";
	ADDR [1][3][4] = "../../socket_r1_c3_i4";
	ADDR [2][0][0] = "../../socket_r2_c0_i0";
	ADDR [2][0][1] = "../../socket_r2_c0_i1";
	ADDR [2][0][2] = "../../socket_r2_c0_i2";
	ADDR [2][0][3] = "../../socket_r2_c0_i3";
	ADDR [2][0][4] = "../../socket_r2_c0_i4";
	ADDR [2][1][0] = "../../socket_r2_c1_i0";
	ADDR [2][1][1] = "../../socket_r2_c1_i1";
	ADDR [2][1][2] = "../../socket_r2_c1_i2";
	ADDR [2][1][3] = "../../socket_r2_c1_i3";
	ADDR [2][1][4] = "../../socket_r2_c1_i4";
	ADDR [2][2][0] = "../../socket_r2_c2_i0";
	ADDR [2][2][1] = "../../socket_r2_c2_i1";
	ADDR [2][2][2] = "../../socket_r2_c2_i2";
	ADDR [2][2][3] = "../../socket_r2_c2_i3";
	ADDR [2][2][4] = "../../socket_r2_c2_i4";
	ADDR [2][3][0] = "../../socket_r2_c3_i0";
	ADDR [2][3][1] = "../../socket_r2_c3_i1";
	ADDR [2][3][2] = "../../socket_r2_c3_i2";
	ADDR [2][3][3] = "../../socket_r2_c3_i3";
	ADDR [2][3][4] = "../../socket_r2_c3_i4";
	ADDR [3][0][0] = "../../socket_r3_c0_i0";
	ADDR [3][0][1] = "../../socket_r3_c0_i1";
	ADDR [3][0][2] = "../../socket_r3_c0_i2";
	ADDR [3][0][3] = "../../socket_r3_c0_i3";
	ADDR [3][0][4] = "../../socket_r3_c0_i4";
	ADDR [3][1][0] = "../../socket_r3_c1_i0";
	ADDR [3][1][1] = "../../socket_r3_c1_i1";
	ADDR [3][1][2] = "../../socket_r3_c1_i2";
	ADDR [3][1][3] = "../../socket_r3_c1_i3";
	ADDR [3][1][4] = "../../socket_r3_c1_i4";
	ADDR [3][2][0] = "../../socket_r3_c2_i0";
	ADDR [3][2][1] = "../../socket_r3_c2_i1";
	ADDR [3][2][2] = "../../socket_r3_c2_i2";
	ADDR [3][2][3] = "../../socket_r3_c2_i3";
	ADDR [3][2][4] = "../../socket_r3_c2_i4";
	ADDR [3][3][0] = "../../socket_r3_c3_i0";
	ADDR [3][3][1] = "../../socket_r3_c3_i1";
	ADDR [3][3][2] = "../../socket_r3_c3_i2";
	ADDR [3][3][3] = "../../socket_r3_c3_i3";
	ADDR [3][3][4] = "../../socket_r3_c3_i4";
	ADDR [4][0][0] = "../../socket_r4_c0_i0";
	ADDR [4][0][1] = "../../socket_r4_c0_i1";
	ADDR [4][0][2] = "../../socket_r4_c0_i2";
	ADDR [4][0][3] = "../../socket_r4_c0_i3";
	ADDR [4][0][4] = "../../socket_r4_c0_i4";
	ADDR [4][1][0] = "../../socket_r4_c1_i0";
	ADDR [4][1][1] = "../../socket_r4_c1_i1";
	ADDR [4][1][2] = "../../socket_r4_c1_i2";
	ADDR [4][1][3] = "../../socket_r4_c1_i3";
	ADDR [4][1][4] = "../../socket_r4_c1_i4";
	ADDR [4][2][0] = "../../socket_r4_c2_i0";
	ADDR [4][2][1] = "../../socket_r4_c2_i1";
	ADDR [4][2][2] = "../../socket_r4_c2_i2";
	ADDR [4][2][3] = "../../socket_r4_c2_i3";
	ADDR [4][2][4] = "../../socket_r4_c2_i4";
	ADDR [4][3][0] = "../../socket_r4_c3_i0";
	ADDR [4][3][1] = "../../socket_r4_c3_i1";
	ADDR [4][3][2] = "../../socket_r4_c3_i2";
	ADDR [4][3][3] = "../../socket_r4_c3_i3";
	ADDR [4][3][4] = "../../socket_r4_c3_i4";
	ADDR [5][0][0] = "../../socket_r5_c0_i0";
	ADDR [5][0][1] = "../../socket_r5_c0_i1";
	ADDR [5][0][2] = "../../socket_r5_c0_i2";
	ADDR [5][0][3] = "../../socket_r5_c0_i3";
	ADDR [5][0][4] = "../../socket_r5_c0_i4";
	ADDR [5][1][0] = "../../socket_r5_c1_i0";
	ADDR [5][1][1] = "../../socket_r5_c1_i1";
	ADDR [5][1][2] = "../../socket_r5_c1_i2";
	ADDR [5][1][3] = "../../socket_r5_c1_i3";
	ADDR [5][1][4] = "../../socket_r5_c1_i4";
	ADDR [5][2][0] = "../../socket_r5_c2_i0";
	ADDR [5][2][1] = "../../socket_r5_c2_i1";
	ADDR [5][2][2] = "../../socket_r5_c2_i2";
	ADDR [5][2][3] = "../../socket_r5_c2_i3";
	ADDR [5][2][4] = "../../socket_r5_c2_i4";
	ADDR [5][3][0] = "../../socket_r5_c3_i0";
	ADDR [5][3][1] = "../../socket_r5_c3_i1";
	ADDR [5][3][2] = "../../socket_r5_c3_i2";
	ADDR [5][3][3] = "../../socket_r5_c3_i3";
	ADDR [5][3][4] = "../../socket_r5_c3_i4";
	ADDR [6][0][0] = "../../socket_r6_c0_i0";
	ADDR [6][0][1] = "../../socket_r6_c0_i1";
	ADDR [6][0][2] = "../../socket_r6_c0_i2";
	ADDR [6][0][3] = "../../socket_r6_c0_i3";
	ADDR [6][0][4] = "../../socket_r6_c0_i4";
	ADDR [6][1][0] = "../../socket_r6_c1_i0";
	ADDR [6][1][1] = "../../socket_r6_c1_i1";
	ADDR [6][1][2] = "../../socket_r6_c1_i2";
	ADDR [6][1][3] = "../../socket_r6_c1_i3";
	ADDR [6][1][4] = "../../socket_r6_c1_i4";
	ADDR [6][2][0] = "../../socket_r6_c2_i0";
	ADDR [6][2][1] = "../../socket_r6_c2_i1";
	ADDR [6][2][2] = "../../socket_r6_c2_i2";
	ADDR [6][2][3] = "../../socket_r6_c2_i3";
	ADDR [6][2][4] = "../../socket_r6_c2_i4";
	ADDR [6][3][0] = "../../socket_r6_c3_i0";
	ADDR [6][3][1] = "../../socket_r6_c3_i1";
	ADDR [6][3][2] = "../../socket_r6_c3_i2";
	ADDR [6][3][3] = "../../socket_r6_c3_i3";
	ADDR [6][3][4] = "../../socket_r6_c3_i4";
	ADDR [7][0][0] = "../../socket_r7_c0_i0";
	ADDR [7][0][1] = "../../socket_r7_c0_i1";
	ADDR [7][0][2] = "../../socket_r7_c0_i2";
	ADDR [7][0][3] = "../../socket_r7_c0_i3";
	ADDR [7][0][4] = "../../socket_r7_c0_i4";
	ADDR [7][1][0] = "../../socket_r7_c1_i0";
	ADDR [7][1][1] = "../../socket_r7_c1_i1";
	ADDR [7][1][2] = "../../socket_r7_c1_i2";
	ADDR [7][1][3] = "../../socket_r7_c1_i3";
	ADDR [7][1][4] = "../../socket_r7_c1_i4";
	ADDR [7][2][0] = "../../socket_r7_c2_i0";
	ADDR [7][2][1] = "../../socket_r7_c2_i1";
	ADDR [7][2][2] = "../../socket_r7_c2_i2";
	ADDR [7][2][3] = "../../socket_r7_c2_i3";
	ADDR [7][2][4] = "../../socket_r7_c2_i4";
	ADDR [7][3][0] = "../../socket_r7_c3_i0";
	ADDR [7][3][1] = "../../socket_r7_c3_i1";
	ADDR [7][3][2] = "../../socket_r7_c3_i2";
	ADDR [7][3][3] = "../../socket_r7_c3_i3";
	ADDR [7][3][4] = "../../socket_r7_c3_i4";
	ADDR [8][0][0] = "../../socket_r8_c0_i0";
	ADDR [8][0][1] = "../../socket_r8_c0_i1";
	ADDR [8][0][2] = "../../socket_r8_c0_i2";
	ADDR [8][0][3] = "../../socket_r8_c0_i3";
	ADDR [8][0][4] = "../../socket_r8_c0_i4";
	ADDR [8][1][0] = "../../socket_r8_c1_i0";
	ADDR [8][1][1] = "../../socket_r8_c1_i1";
	ADDR [8][1][2] = "../../socket_r8_c1_i2";
	ADDR [8][1][3] = "../../socket_r8_c1_i3";
	ADDR [8][1][4] = "../../socket_r8_c1_i4";
	ADDR [8][2][0] = "../../socket_r8_c2_i0";
	ADDR [8][2][1] = "../../socket_r8_c2_i1";
	ADDR [8][2][2] = "../../socket_r8_c2_i2";
	ADDR [8][2][3] = "../../socket_r8_c2_i3";
	ADDR [8][2][4] = "../../socket_r8_c2_i4";
	ADDR [8][3][0] = "../../socket_r8_c3_i0";
	ADDR [8][3][1] = "../../socket_r8_c3_i1";
	ADDR [8][3][2] = "../../socket_r8_c3_i2";
	ADDR [8][3][3] = "../../socket_r8_c3_i3";
	ADDR [8][3][4] = "../../socket_r8_c3_i4";
	ADDR [9][0][0] = "../../socket_r9_c0_i0";
	ADDR [9][0][1] = "../../socket_r9_c0_i1";
	ADDR [9][0][2] = "../../socket_r9_c0_i2";
	ADDR [9][0][3] = "../../socket_r9_c0_i3";
	ADDR [9][0][4] = "../../socket_r9_c0_i4";
	ADDR [9][1][0] = "../../socket_r9_c1_i0";
	ADDR [9][1][1] = "../../socket_r9_c1_i1";
	ADDR [9][1][2] = "../../socket_r9_c1_i2";
	ADDR [9][1][3] = "../../socket_r9_c1_i3";
	ADDR [9][1][4] = "../../socket_r9_c1_i4";
	ADDR [9][2][0] = "../../socket_r9_c2_i0";
	ADDR [9][2][1] = "../../socket_r9_c2_i1";
	ADDR [9][2][2] = "../../socket_r9_c2_i2";
	ADDR [9][2][3] = "../../socket_r9_c2_i3";
	ADDR [9][2][4] = "../../socket_r9_c2_i4";
	ADDR [9][3][0] = "../../socket_r9_c3_i0";
	ADDR [9][3][1] = "../../socket_r9_c3_i1";
	ADDR [9][3][2] = "../../socket_r9_c3_i2";
	ADDR [9][3][3] = "../../socket_r9_c3_i3";
	ADDR [9][3][4] = "../../socket_r9_c3_i4";
	ADDR [10][0][0] = "../../socket_r10_c0_i0";
	ADDR [10][0][1] = "../../socket_r10_c0_i1";
	ADDR [10][0][2] = "../../socket_r10_c0_i2";
	ADDR [10][0][3] = "../../socket_r10_c0_i3";
	ADDR [10][0][4] = "../../socket_r10_c0_i4";
	ADDR [10][1][0] = "../../socket_r10_c1_i0";
	ADDR [10][1][1] = "../../socket_r10_c1_i1";
	ADDR [10][1][2] = "../../socket_r10_c1_i2";
	ADDR [10][1][3] = "../../socket_r10_c1_i3";
	ADDR [10][1][4] = "../../socket_r10_c1_i4";
	ADDR [10][2][0] = "../../socket_r10_c2_i0";
	ADDR [10][2][1] = "../../socket_r10_c2_i1";
	ADDR [10][2][2] = "../../socket_r10_c2_i2";
	ADDR [10][2][3] = "../../socket_r10_c2_i3";
	ADDR [10][2][4] = "../../socket_r10_c2_i4";
	ADDR [10][3][0] = "../../socket_r10_c3_i0";
	ADDR [10][3][1] = "../../socket_r10_c3_i1";
	ADDR [10][3][2] = "../../socket_r10_c3_i2";
	ADDR [10][3][3] = "../../socket_r10_c3_i3";
	ADDR [10][3][4] = "../../socket_r10_c3_i4";
	ADDR [11][0][0] = "../../socket_r11_c0_i0";
	ADDR [11][0][1] = "../../socket_r11_c0_i1";
	ADDR [11][0][2] = "../../socket_r11_c0_i2";
	ADDR [11][0][3] = "../../socket_r11_c0_i3";
	ADDR [11][0][4] = "../../socket_r11_c0_i4";
	ADDR [11][1][0] = "../../socket_r11_c1_i0";
	ADDR [11][1][1] = "../../socket_r11_c1_i1";
	ADDR [11][1][2] = "../../socket_r11_c1_i2";
	ADDR [11][1][3] = "../../socket_r11_c1_i3";
	ADDR [11][1][4] = "../../socket_r11_c1_i4";
	ADDR [11][2][0] = "../../socket_r11_c2_i0";
	ADDR [11][2][1] = "../../socket_r11_c2_i1";
	ADDR [11][2][2] = "../../socket_r11_c2_i2";
	ADDR [11][2][3] = "../../socket_r11_c2_i3";
	ADDR [11][2][4] = "../../socket_r11_c2_i4";
	ADDR [11][3][0] = "../../socket_r11_c3_i0";
	ADDR [11][3][1] = "../../socket_r11_c3_i1";
	ADDR [11][3][2] = "../../socket_r11_c3_i2";
	ADDR [11][3][3] = "../../socket_r11_c3_i3";
	ADDR [11][3][4] = "../../socket_r11_c3_i4";
	ADDR [12][0][0] = "../../socket_r12_c0_i0";
	ADDR [12][0][1] = "../../socket_r12_c0_i1";
	ADDR [12][0][2] = "../../socket_r12_c0_i2";
	ADDR [12][0][3] = "../../socket_r12_c0_i3";
	ADDR [12][0][4] = "../../socket_r12_c0_i4";
	ADDR [12][1][0] = "../../socket_r12_c1_i0";
	ADDR [12][1][1] = "../../socket_r12_c1_i1";
	ADDR [12][1][2] = "../../socket_r12_c1_i2";
	ADDR [12][1][3] = "../../socket_r12_c1_i3";
	ADDR [12][1][4] = "../../socket_r12_c1_i4";
	ADDR [12][2][0] = "../../socket_r12_c2_i0";
	ADDR [12][2][1] = "../../socket_r12_c2_i1";
	ADDR [12][2][2] = "../../socket_r12_c2_i2";
	ADDR [12][2][3] = "../../socket_r12_c2_i3";
	ADDR [12][2][4] = "../../socket_r12_c2_i4";
	ADDR [12][3][0] = "../../socket_r12_c3_i0";
	ADDR [12][3][1] = "../../socket_r12_c3_i1";
	ADDR [12][3][2] = "../../socket_r12_c3_i2";
	ADDR [12][3][3] = "../../socket_r12_c3_i3";
	ADDR [12][3][4] = "../../socket_r12_c3_i4";
	ADDR [13][0][0] = "../../socket_r13_c0_i0";
	ADDR [13][0][1] = "../../socket_r13_c0_i1";
	ADDR [13][0][2] = "../../socket_r13_c0_i2";
	ADDR [13][0][3] = "../../socket_r13_c0_i3";
	ADDR [13][0][4] = "../../socket_r13_c0_i4";
	ADDR [13][1][0] = "../../socket_r13_c1_i0";
	ADDR [13][1][1] = "../../socket_r13_c1_i1";
	ADDR [13][1][2] = "../../socket_r13_c1_i2";
	ADDR [13][1][3] = "../../socket_r13_c1_i3";
	ADDR [13][1][4] = "../../socket_r13_c1_i4";
	ADDR [13][2][0] = "../../socket_r13_c2_i0";
	ADDR [13][2][1] = "../../socket_r13_c2_i1";
	ADDR [13][2][2] = "../../socket_r13_c2_i2";
	ADDR [13][2][3] = "../../socket_r13_c2_i3";
	ADDR [13][2][4] = "../../socket_r13_c2_i4";
	ADDR [13][3][0] = "../../socket_r13_c3_i0";
	ADDR [13][3][1] = "../../socket_r13_c3_i1";
	ADDR [13][3][2] = "../../socket_r13_c3_i2";
	ADDR [13][3][3] = "../../socket_r13_c3_i3";
	ADDR [13][3][4] = "../../socket_r13_c3_i4";
	ADDR [14][0][0] = "../../socket_r14_c0_i0";
	ADDR [14][0][1] = "../../socket_r14_c0_i1";
	ADDR [14][0][2] = "../../socket_r14_c0_i2";
	ADDR [14][0][3] = "../../socket_r14_c0_i3";
	ADDR [14][0][4] = "../../socket_r14_c0_i4";
	ADDR [14][1][0] = "../../socket_r14_c1_i0";
	ADDR [14][1][1] = "../../socket_r14_c1_i1";
	ADDR [14][1][2] = "../../socket_r14_c1_i2";
	ADDR [14][1][3] = "../../socket_r14_c1_i3";
	ADDR [14][1][4] = "../../socket_r14_c1_i4";
	ADDR [14][2][0] = "../../socket_r14_c2_i0";
	ADDR [14][2][1] = "../../socket_r14_c2_i1";
	ADDR [14][2][2] = "../../socket_r14_c2_i2";
	ADDR [14][2][3] = "../../socket_r14_c2_i3";
	ADDR [14][2][4] = "../../socket_r14_c2_i4";
	ADDR [14][3][0] = "../../socket_r14_c3_i0";
	ADDR [14][3][1] = "../../socket_r14_c3_i1";
	ADDR [14][3][2] = "../../socket_r14_c3_i2";
	ADDR [14][3][3] = "../../socket_r14_c3_i3";
	ADDR [14][3][4] = "../../socket_r14_c3_i4";
	ADDR [15][0][0] = "../../socket_r15_c0_i0";
	ADDR [15][0][1] = "../../socket_r15_c0_i1";
	ADDR [15][0][2] = "../../socket_r15_c0_i2";
	ADDR [15][0][3] = "../../socket_r15_c0_i3";
	ADDR [15][0][4] = "../../socket_r15_c0_i4";
	ADDR [15][1][0] = "../../socket_r15_c1_i0";
	ADDR [15][1][1] = "../../socket_r15_c1_i1";
	ADDR [15][1][2] = "../../socket_r15_c1_i2";
	ADDR [15][1][3] = "../../socket_r15_c1_i3";
	ADDR [15][1][4] = "../../socket_r15_c1_i4";
	ADDR [15][2][0] = "../../socket_r15_c2_i0";
	ADDR [15][2][1] = "../../socket_r15_c2_i1";
	ADDR [15][2][2] = "../../socket_r15_c2_i2";
	ADDR [15][2][3] = "../../socket_r15_c2_i3";
	ADDR [15][2][4] = "../../socket_r15_c2_i4";
	ADDR [15][3][0] = "../../socket_r15_c3_i0";
	ADDR [15][3][1] = "../../socket_r15_c3_i1";
	ADDR [15][3][2] = "../../socket_r15_c3_i2";
	ADDR [15][3][3] = "../../socket_r15_c3_i3";
	ADDR [15][3][4] = "../../socket_r15_c3_i4";
	ADDR [16][0][0] = "../../socket_r16_c0_i0";
	ADDR [16][0][1] = "../../socket_r16_c0_i1";
	ADDR [16][0][2] = "../../socket_r16_c0_i2";
	ADDR [16][0][3] = "../../socket_r16_c0_i3";
	ADDR [16][0][4] = "../../socket_r16_c0_i4";
	ADDR [16][1][0] = "../../socket_r16_c1_i0";
	ADDR [16][1][1] = "../../socket_r16_c1_i1";
	ADDR [16][1][2] = "../../socket_r16_c1_i2";
	ADDR [16][1][3] = "../../socket_r16_c1_i3";
	ADDR [16][1][4] = "../../socket_r16_c1_i4";
	ADDR [16][2][0] = "../../socket_r16_c2_i0";
	ADDR [16][2][1] = "../../socket_r16_c2_i1";
	ADDR [16][2][2] = "../../socket_r16_c2_i2";
	ADDR [16][2][3] = "../../socket_r16_c2_i3";
	ADDR [16][2][4] = "../../socket_r16_c2_i4";
	ADDR [16][3][0] = "../../socket_r16_c3_i0";
	ADDR [16][3][1] = "../../socket_r16_c3_i1";
	ADDR [16][3][2] = "../../socket_r16_c3_i2";
	ADDR [16][3][3] = "../../socket_r16_c3_i3";
	ADDR [16][3][4] = "../../socket_r16_c3_i4";
	ADDR [17][0][0] = "../../socket_r17_c0_i0";
	ADDR [17][0][1] = "../../socket_r17_c0_i1";
	ADDR [17][0][2] = "../../socket_r17_c0_i2";
	ADDR [17][0][3] = "../../socket_r17_c0_i3";
	ADDR [17][0][4] = "../../socket_r17_c0_i4";
	ADDR [17][1][0] = "../../socket_r17_c1_i0";
	ADDR [17][1][1] = "../../socket_r17_c1_i1";
	ADDR [17][1][2] = "../../socket_r17_c1_i2";
	ADDR [17][1][3] = "../../socket_r17_c1_i3";
	ADDR [17][1][4] = "../../socket_r17_c1_i4";
	ADDR [17][2][0] = "../../socket_r17_c2_i0";
	ADDR [17][2][1] = "../../socket_r17_c2_i1";
	ADDR [17][2][2] = "../../socket_r17_c2_i2";
	ADDR [17][2][3] = "../../socket_r17_c2_i3";
	ADDR [17][2][4] = "../../socket_r17_c2_i4";
	ADDR [17][3][0] = "../../socket_r17_c3_i0";
	ADDR [17][3][1] = "../../socket_r17_c3_i1";
	ADDR [17][3][2] = "../../socket_r17_c3_i2";
	ADDR [17][3][3] = "../../socket_r17_c3_i3";
	ADDR [17][3][4] = "../../socket_r17_c3_i4";
	ADDR [18][0][0] = "../../socket_r18_c0_i0";
	ADDR [18][0][1] = "../../socket_r18_c0_i1";
	ADDR [18][0][2] = "../../socket_r18_c0_i2";
	ADDR [18][0][3] = "../../socket_r18_c0_i3";
	ADDR [18][0][4] = "../../socket_r18_c0_i4";
	ADDR [18][1][0] = "../../socket_r18_c1_i0";
	ADDR [18][1][1] = "../../socket_r18_c1_i1";
	ADDR [18][1][2] = "../../socket_r18_c1_i2";
	ADDR [18][1][3] = "../../socket_r18_c1_i3";
	ADDR [18][1][4] = "../../socket_r18_c1_i4";
	ADDR [18][2][0] = "../../socket_r18_c2_i0";
	ADDR [18][2][1] = "../../socket_r18_c2_i1";
	ADDR [18][2][2] = "../../socket_r18_c2_i2";
	ADDR [18][2][3] = "../../socket_r18_c2_i3";
	ADDR [18][2][4] = "../../socket_r18_c2_i4";
	ADDR [18][3][0] = "../../socket_r18_c3_i0";
	ADDR [18][3][1] = "../../socket_r18_c3_i1";
	ADDR [18][3][2] = "../../socket_r18_c3_i2";
	ADDR [18][3][3] = "../../socket_r18_c3_i3";
	ADDR [18][3][4] = "../../socket_r18_c3_i4";
	ADDR [19][0][0] = "../../socket_r19_c0_i0";
	ADDR [19][0][1] = "../../socket_r19_c0_i1";
	ADDR [19][0][2] = "../../socket_r19_c0_i2";
	ADDR [19][0][3] = "../../socket_r19_c0_i3";
	ADDR [19][0][4] = "../../socket_r19_c0_i4";
	ADDR [19][1][0] = "../../socket_r19_c1_i0";
	ADDR [19][1][1] = "../../socket_r19_c1_i1";
	ADDR [19][1][2] = "../../socket_r19_c1_i2";
	ADDR [19][1][3] = "../../socket_r19_c1_i3";
	ADDR [19][1][4] = "../../socket_r19_c1_i4";
	ADDR [19][2][0] = "../../socket_r19_c2_i0";
	ADDR [19][2][1] = "../../socket_r19_c2_i1";
	ADDR [19][2][2] = "../../socket_r19_c2_i2";
	ADDR [19][2][3] = "../../socket_r19_c2_i3";
	ADDR [19][2][4] = "../../socket_r19_c2_i4";
	ADDR [19][3][0] = "../../socket_r19_c3_i0";
	ADDR [19][3][1] = "../../socket_r19_c3_i1";
	ADDR [19][3][2] = "../../socket_r19_c3_i2";
	ADDR [19][3][3] = "../../socket_r19_c3_i3";
	ADDR [19][3][4] = "../../socket_r19_c3_i4";
	ADDR [20][0][0] = "../../socket_r20_c0_i0";
	ADDR [20][0][1] = "../../socket_r20_c0_i1";
	ADDR [20][0][2] = "../../socket_r20_c0_i2";
	ADDR [20][0][3] = "../../socket_r20_c0_i3";
	ADDR [20][0][4] = "../../socket_r20_c0_i4";
	ADDR [20][1][0] = "../../socket_r20_c1_i0";
	ADDR [20][1][1] = "../../socket_r20_c1_i1";
	ADDR [20][1][2] = "../../socket_r20_c1_i2";
	ADDR [20][1][3] = "../../socket_r20_c1_i3";
	ADDR [20][1][4] = "../../socket_r20_c1_i4";
	ADDR [20][2][0] = "../../socket_r20_c2_i0";
	ADDR [20][2][1] = "../../socket_r20_c2_i1";
	ADDR [20][2][2] = "../../socket_r20_c2_i2";
	ADDR [20][2][3] = "../../socket_r20_c2_i3";
	ADDR [20][2][4] = "../../socket_r20_c2_i4";
	ADDR [20][3][0] = "../../socket_r20_c3_i0";
	ADDR [20][3][1] = "../../socket_r20_c3_i1";
	ADDR [20][3][2] = "../../socket_r20_c3_i2";
	ADDR [20][3][3] = "../../socket_r20_c3_i3";
	ADDR [20][3][4] = "../../socket_r20_c3_i4";
	ADDR [21][0][0] = "../../socket_r21_c0_i0";
	ADDR [21][0][1] = "../../socket_r21_c0_i1";
	ADDR [21][0][2] = "../../socket_r21_c0_i2";
	ADDR [21][0][3] = "../../socket_r21_c0_i3";
	ADDR [21][0][4] = "../../socket_r21_c0_i4";
	ADDR [21][1][0] = "../../socket_r21_c1_i0";
	ADDR [21][1][1] = "../../socket_r21_c1_i1";
	ADDR [21][1][2] = "../../socket_r21_c1_i2";
	ADDR [21][1][3] = "../../socket_r21_c1_i3";
	ADDR [21][1][4] = "../../socket_r21_c1_i4";
	ADDR [21][2][0] = "../../socket_r21_c2_i0";
	ADDR [21][2][1] = "../../socket_r21_c2_i1";
	ADDR [21][2][2] = "../../socket_r21_c2_i2";
	ADDR [21][2][3] = "../../socket_r21_c2_i3";
	ADDR [21][2][4] = "../../socket_r21_c2_i4";
	ADDR [21][3][0] = "../../socket_r21_c3_i0";
	ADDR [21][3][1] = "../../socket_r21_c3_i1";
	ADDR [21][3][2] = "../../socket_r21_c3_i2";
	ADDR [21][3][3] = "../../socket_r21_c3_i3";
	ADDR [21][3][4] = "../../socket_r21_c3_i4";
	ADDR [22][0][0] = "../../socket_r22_c0_i0";
	ADDR [22][0][1] = "../../socket_r22_c0_i1";
	ADDR [22][0][2] = "../../socket_r22_c0_i2";
	ADDR [22][0][3] = "../../socket_r22_c0_i3";
	ADDR [22][0][4] = "../../socket_r22_c0_i4";
	ADDR [22][1][0] = "../../socket_r22_c1_i0";
	ADDR [22][1][1] = "../../socket_r22_c1_i1";
	ADDR [22][1][2] = "../../socket_r22_c1_i2";
	ADDR [22][1][3] = "../../socket_r22_c1_i3";
	ADDR [22][1][4] = "../../socket_r22_c1_i4";
	ADDR [22][2][0] = "../../socket_r22_c2_i0";
	ADDR [22][2][1] = "../../socket_r22_c2_i1";
	ADDR [22][2][2] = "../../socket_r22_c2_i2";
	ADDR [22][2][3] = "../../socket_r22_c2_i3";
	ADDR [22][2][4] = "../../socket_r22_c2_i4";
	ADDR [22][3][0] = "../../socket_r22_c3_i0";
	ADDR [22][3][1] = "../../socket_r22_c3_i1";
	ADDR [22][3][2] = "../../socket_r22_c3_i2";
	ADDR [22][3][3] = "../../socket_r22_c3_i3";
	ADDR [22][3][4] = "../../socket_r22_c3_i4";
	ADDR [23][0][0] = "../../socket_r23_c0_i0";
	ADDR [23][0][1] = "../../socket_r23_c0_i1";
	ADDR [23][0][2] = "../../socket_r23_c0_i2";
	ADDR [23][0][3] = "../../socket_r23_c0_i3";
	ADDR [23][0][4] = "../../socket_r23_c0_i4";
	ADDR [23][1][0] = "../../socket_r23_c1_i0";
	ADDR [23][1][1] = "../../socket_r23_c1_i1";
	ADDR [23][1][2] = "../../socket_r23_c1_i2";
	ADDR [23][1][3] = "../../socket_r23_c1_i3";
	ADDR [23][1][4] = "../../socket_r23_c1_i4";
	ADDR [23][2][0] = "../../socket_r23_c2_i0";
	ADDR [23][2][1] = "../../socket_r23_c2_i1";
	ADDR [23][2][2] = "../../socket_r23_c2_i2";
	ADDR [23][2][3] = "../../socket_r23_c2_i3";
	ADDR [23][2][4] = "../../socket_r23_c2_i4";
	ADDR [23][3][0] = "../../socket_r23_c3_i0";
	ADDR [23][3][1] = "../../socket_r23_c3_i1";
	ADDR [23][3][2] = "../../socket_r23_c3_i2";
	ADDR [23][3][3] = "../../socket_r23_c3_i3";
	ADDR [23][3][4] = "../../socket_r23_c3_i4";
	ADDR [24][0][0] = "../../socket_r24_c0_i0";
	ADDR [24][0][1] = "../../socket_r24_c0_i1";
	ADDR [24][0][2] = "../../socket_r24_c0_i2";
	ADDR [24][0][3] = "../../socket_r24_c0_i3";
	ADDR [24][0][4] = "../../socket_r24_c0_i4";
	ADDR [24][1][0] = "../../socket_r24_c1_i0";
	ADDR [24][1][1] = "../../socket_r24_c1_i1";
	ADDR [24][1][2] = "../../socket_r24_c1_i2";
	ADDR [24][1][3] = "../../socket_r24_c1_i3";
	ADDR [24][1][4] = "../../socket_r24_c1_i4";
	ADDR [24][2][0] = "../../socket_r24_c2_i0";
	ADDR [24][2][1] = "../../socket_r24_c2_i1";
	ADDR [24][2][2] = "../../socket_r24_c2_i2";
	ADDR [24][2][3] = "../../socket_r24_c2_i3";
	ADDR [24][2][4] = "../../socket_r24_c2_i4";
	ADDR [24][3][0] = "../../socket_r24_c3_i0";
	ADDR [24][3][1] = "../../socket_r24_c3_i1";
	ADDR [24][3][2] = "../../socket_r24_c3_i2";
	ADDR [24][3][3] = "../../socket_r24_c3_i3";
	ADDR [24][3][4] = "../../socket_r24_c3_i4";
	ADDR [25][0][0] = "../../socket_r25_c0_i0";
	ADDR [25][0][1] = "../../socket_r25_c0_i1";
	ADDR [25][0][2] = "../../socket_r25_c0_i2";
	ADDR [25][0][3] = "../../socket_r25_c0_i3";
	ADDR [25][0][4] = "../../socket_r25_c0_i4";
	ADDR [25][1][0] = "../../socket_r25_c1_i0";
	ADDR [25][1][1] = "../../socket_r25_c1_i1";
	ADDR [25][1][2] = "../../socket_r25_c1_i2";
	ADDR [25][1][3] = "../../socket_r25_c1_i3";
	ADDR [25][1][4] = "../../socket_r25_c1_i4";
	ADDR [25][2][0] = "../../socket_r25_c2_i0";
	ADDR [25][2][1] = "../../socket_r25_c2_i1";
	ADDR [25][2][2] = "../../socket_r25_c2_i2";
	ADDR [25][2][3] = "../../socket_r25_c2_i3";
	ADDR [25][2][4] = "../../socket_r25_c2_i4";
	ADDR [25][3][0] = "../../socket_r25_c3_i0";
	ADDR [25][3][1] = "../../socket_r25_c3_i1";
	ADDR [25][3][2] = "../../socket_r25_c3_i2";
	ADDR [25][3][3] = "../../socket_r25_c3_i3";
	ADDR [25][3][4] = "../../socket_r25_c3_i4";
	ADDR [26][0][0] = "../../socket_r26_c0_i0";
	ADDR [26][0][1] = "../../socket_r26_c0_i1";
	ADDR [26][0][2] = "../../socket_r26_c0_i2";
	ADDR [26][0][3] = "../../socket_r26_c0_i3";
	ADDR [26][0][4] = "../../socket_r26_c0_i4";
	ADDR [26][1][0] = "../../socket_r26_c1_i0";
	ADDR [26][1][1] = "../../socket_r26_c1_i1";
	ADDR [26][1][2] = "../../socket_r26_c1_i2";
	ADDR [26][1][3] = "../../socket_r26_c1_i3";
	ADDR [26][1][4] = "../../socket_r26_c1_i4";
	ADDR [26][2][0] = "../../socket_r26_c2_i0";
	ADDR [26][2][1] = "../../socket_r26_c2_i1";
	ADDR [26][2][2] = "../../socket_r26_c2_i2";
	ADDR [26][2][3] = "../../socket_r26_c2_i3";
	ADDR [26][2][4] = "../../socket_r26_c2_i4";
	ADDR [26][3][0] = "../../socket_r26_c3_i0";
	ADDR [26][3][1] = "../../socket_r26_c3_i1";
	ADDR [26][3][2] = "../../socket_r26_c3_i2";
	ADDR [26][3][3] = "../../socket_r26_c3_i3";
	ADDR [26][3][4] = "../../socket_r26_c3_i4";
	ADDR [27][0][0] = "../../socket_r27_c0_i0";
	ADDR [27][0][1] = "../../socket_r27_c0_i1";
	ADDR [27][0][2] = "../../socket_r27_c0_i2";
	ADDR [27][0][3] = "../../socket_r27_c0_i3";
	ADDR [27][0][4] = "../../socket_r27_c0_i4";
	ADDR [27][1][0] = "../../socket_r27_c1_i0";
	ADDR [27][1][1] = "../../socket_r27_c1_i1";
	ADDR [27][1][2] = "../../socket_r27_c1_i2";
	ADDR [27][1][3] = "../../socket_r27_c1_i3";
	ADDR [27][1][4] = "../../socket_r27_c1_i4";
	ADDR [27][2][0] = "../../socket_r27_c2_i0";
	ADDR [27][2][1] = "../../socket_r27_c2_i1";
	ADDR [27][2][2] = "../../socket_r27_c2_i2";
	ADDR [27][2][3] = "../../socket_r27_c2_i3";
	ADDR [27][2][4] = "../../socket_r27_c2_i4";
	ADDR [27][3][0] = "../../socket_r27_c3_i0";
	ADDR [27][3][1] = "../../socket_r27_c3_i1";
	ADDR [27][3][2] = "../../socket_r27_c3_i2";
	ADDR [27][3][3] = "../../socket_r27_c3_i3";
	ADDR [27][3][4] = "../../socket_r27_c3_i4";
	ADDR [28][0][0] = "../../socket_r28_c0_i0";
	ADDR [28][0][1] = "../../socket_r28_c0_i1";
	ADDR [28][0][2] = "../../socket_r28_c0_i2";
	ADDR [28][0][3] = "../../socket_r28_c0_i3";
	ADDR [28][0][4] = "../../socket_r28_c0_i4";
	ADDR [28][1][0] = "../../socket_r28_c1_i0";
	ADDR [28][1][1] = "../../socket_r28_c1_i1";
	ADDR [28][1][2] = "../../socket_r28_c1_i2";
	ADDR [28][1][3] = "../../socket_r28_c1_i3";
	ADDR [28][1][4] = "../../socket_r28_c1_i4";
	ADDR [28][2][0] = "../../socket_r28_c2_i0";
	ADDR [28][2][1] = "../../socket_r28_c2_i1";
	ADDR [28][2][2] = "../../socket_r28_c2_i2";
	ADDR [28][2][3] = "../../socket_r28_c2_i3";
	ADDR [28][2][4] = "../../socket_r28_c2_i4";
	ADDR [28][3][0] = "../../socket_r28_c3_i0";
	ADDR [28][3][1] = "../../socket_r28_c3_i1";
	ADDR [28][3][2] = "../../socket_r28_c3_i2";
	ADDR [28][3][3] = "../../socket_r28_c3_i3";
	ADDR [28][3][4] = "../../socket_r28_c3_i4";
	ADDR [29][0][0] = "../../socket_r29_c0_i0";
	ADDR [29][0][1] = "../../socket_r29_c0_i1";
	ADDR [29][0][2] = "../../socket_r29_c0_i2";
	ADDR [29][0][3] = "../../socket_r29_c0_i3";
	ADDR [29][0][4] = "../../socket_r29_c0_i4";
	ADDR [29][1][0] = "../../socket_r29_c1_i0";
	ADDR [29][1][1] = "../../socket_r29_c1_i1";
	ADDR [29][1][2] = "../../socket_r29_c1_i2";
	ADDR [29][1][3] = "../../socket_r29_c1_i3";
	ADDR [29][1][4] = "../../socket_r29_c1_i4";
	ADDR [29][2][0] = "../../socket_r29_c2_i0";
	ADDR [29][2][1] = "../../socket_r29_c2_i1";
	ADDR [29][2][2] = "../../socket_r29_c2_i2";
	ADDR [29][2][3] = "../../socket_r29_c2_i3";
	ADDR [29][2][4] = "../../socket_r29_c2_i4";
	ADDR [29][3][0] = "../../socket_r29_c3_i0";
	ADDR [29][3][1] = "../../socket_r29_c3_i1";
	ADDR [29][3][2] = "../../socket_r29_c3_i2";
	ADDR [29][3][3] = "../../socket_r29_c3_i3";
	ADDR [29][3][4] = "../../socket_r29_c3_i4";
	ADDR [30][0][0] = "../../socket_r30_c0_i0";
	ADDR [30][0][1] = "../../socket_r30_c0_i1";
	ADDR [30][0][2] = "../../socket_r30_c0_i2";
	ADDR [30][0][3] = "../../socket_r30_c0_i3";
	ADDR [30][0][4] = "../../socket_r30_c0_i4";
	ADDR [30][1][0] = "../../socket_r30_c1_i0";
	ADDR [30][1][1] = "../../socket_r30_c1_i1";
	ADDR [30][1][2] = "../../socket_r30_c1_i2";
	ADDR [30][1][3] = "../../socket_r30_c1_i3";
	ADDR [30][1][4] = "../../socket_r30_c1_i4";
	ADDR [30][2][0] = "../../socket_r30_c2_i0";
	ADDR [30][2][1] = "../../socket_r30_c2_i1";
	ADDR [30][2][2] = "../../socket_r30_c2_i2";
	ADDR [30][2][3] = "../../socket_r30_c2_i3";
	ADDR [30][2][4] = "../../socket_r30_c2_i4";
	ADDR [30][3][0] = "../../socket_r30_c3_i0";
	ADDR [30][3][1] = "../../socket_r30_c3_i1";
	ADDR [30][3][2] = "../../socket_r30_c3_i2";
	ADDR [30][3][3] = "../../socket_r30_c3_i3";
	ADDR [30][3][4] = "../../socket_r30_c3_i4";
	ADDR [31][0][0] = "../../socket_r31_c0_i0";
	ADDR [31][0][1] = "../../socket_r31_c0_i1";
	ADDR [31][0][2] = "../../socket_r31_c0_i2";
	ADDR [31][0][3] = "../../socket_r31_c0_i3";
	ADDR [31][0][4] = "../../socket_r31_c0_i4";
	ADDR [31][1][0] = "../../socket_r31_c1_i0";
	ADDR [31][1][1] = "../../socket_r31_c1_i1";
	ADDR [31][1][2] = "../../socket_r31_c1_i2";
	ADDR [31][1][3] = "../../socket_r31_c1_i3";
	ADDR [31][1][4] = "../../socket_r31_c1_i4";
	ADDR [31][2][0] = "../../socket_r31_c2_i0";
	ADDR [31][2][1] = "../../socket_r31_c2_i1";
	ADDR [31][2][2] = "../../socket_r31_c2_i2";
	ADDR [31][2][3] = "../../socket_r31_c2_i3";
	ADDR [31][2][4] = "../../socket_r31_c2_i4";
	ADDR [31][3][0] = "../../socket_r31_c3_i0";
	ADDR [31][3][1] = "../../socket_r31_c3_i1";
	ADDR [31][3][2] = "../../socket_r31_c3_i2";
	ADDR [31][3][3] = "../../socket_r31_c3_i3";
	ADDR [31][3][4] = "../../socket_r31_c3_i4";
	ADDR [32][0][0] = "../../socket_r32_c0_i0";
	ADDR [32][0][1] = "../../socket_r32_c0_i1";
	ADDR [32][0][2] = "../../socket_r32_c0_i2";
	ADDR [32][0][3] = "../../socket_r32_c0_i3";
	ADDR [32][0][4] = "../../socket_r32_c0_i4";
	ADDR [32][1][0] = "../../socket_r32_c1_i0";
	ADDR [32][1][1] = "../../socket_r32_c1_i1";
	ADDR [32][1][2] = "../../socket_r32_c1_i2";
	ADDR [32][1][3] = "../../socket_r32_c1_i3";
	ADDR [32][1][4] = "../../socket_r32_c1_i4";
	ADDR [32][2][0] = "../../socket_r32_c2_i0";
	ADDR [32][2][1] = "../../socket_r32_c2_i1";
	ADDR [32][2][2] = "../../socket_r32_c2_i2";
	ADDR [32][2][3] = "../../socket_r32_c2_i3";
	ADDR [32][2][4] = "../../socket_r32_c2_i4";
	ADDR [32][3][0] = "../../socket_r32_c3_i0";
	ADDR [32][3][1] = "../../socket_r32_c3_i1";
	ADDR [32][3][2] = "../../socket_r32_c3_i2";
	ADDR [32][3][3] = "../../socket_r32_c3_i3";
	ADDR [32][3][4] = "../../socket_r32_c3_i4";
	ADDR [33][0][0] = "../../socket_r33_c0_i0";
	ADDR [33][0][1] = "../../socket_r33_c0_i1";
	ADDR [33][0][2] = "../../socket_r33_c0_i2";
	ADDR [33][0][3] = "../../socket_r33_c0_i3";
	ADDR [33][0][4] = "../../socket_r33_c0_i4";
	ADDR [33][1][0] = "../../socket_r33_c1_i0";
	ADDR [33][1][1] = "../../socket_r33_c1_i1";
	ADDR [33][1][2] = "../../socket_r33_c1_i2";
	ADDR [33][1][3] = "../../socket_r33_c1_i3";
	ADDR [33][1][4] = "../../socket_r33_c1_i4";
	ADDR [33][2][0] = "../../socket_r33_c2_i0";
	ADDR [33][2][1] = "../../socket_r33_c2_i1";
	ADDR [33][2][2] = "../../socket_r33_c2_i2";
	ADDR [33][2][3] = "../../socket_r33_c2_i3";
	ADDR [33][2][4] = "../../socket_r33_c2_i4";
	ADDR [33][3][0] = "../../socket_r33_c3_i0";
	ADDR [33][3][1] = "../../socket_r33_c3_i1";
	ADDR [33][3][2] = "../../socket_r33_c3_i2";
	ADDR [33][3][3] = "../../socket_r33_c3_i3";
	ADDR [33][3][4] = "../../socket_r33_c3_i4";
	ADDR [34][0][0] = "../../socket_r34_c0_i0";
	ADDR [34][0][1] = "../../socket_r34_c0_i1";
	ADDR [34][0][2] = "../../socket_r34_c0_i2";
	ADDR [34][0][3] = "../../socket_r34_c0_i3";
	ADDR [34][0][4] = "../../socket_r34_c0_i4";
	ADDR [34][1][0] = "../../socket_r34_c1_i0";
	ADDR [34][1][1] = "../../socket_r34_c1_i1";
	ADDR [34][1][2] = "../../socket_r34_c1_i2";
	ADDR [34][1][3] = "../../socket_r34_c1_i3";
	ADDR [34][1][4] = "../../socket_r34_c1_i4";
	ADDR [34][2][0] = "../../socket_r34_c2_i0";
	ADDR [34][2][1] = "../../socket_r34_c2_i1";
	ADDR [34][2][2] = "../../socket_r34_c2_i2";
	ADDR [34][2][3] = "../../socket_r34_c2_i3";
	ADDR [34][2][4] = "../../socket_r34_c2_i4";
	ADDR [34][3][0] = "../../socket_r34_c3_i0";
	ADDR [34][3][1] = "../../socket_r34_c3_i1";
	ADDR [34][3][2] = "../../socket_r34_c3_i2";
	ADDR [34][3][3] = "../../socket_r34_c3_i3";
	ADDR [34][3][4] = "../../socket_r34_c3_i4";
	ADDR [35][0][0] = "../../socket_r35_c0_i0";
	ADDR [35][0][1] = "../../socket_r35_c0_i1";
	ADDR [35][0][2] = "../../socket_r35_c0_i2";
	ADDR [35][0][3] = "../../socket_r35_c0_i3";
	ADDR [35][0][4] = "../../socket_r35_c0_i4";
	ADDR [35][1][0] = "../../socket_r35_c1_i0";
	ADDR [35][1][1] = "../../socket_r35_c1_i1";
	ADDR [35][1][2] = "../../socket_r35_c1_i2";
	ADDR [35][1][3] = "../../socket_r35_c1_i3";
	ADDR [35][1][4] = "../../socket_r35_c1_i4";
	ADDR [35][2][0] = "../../socket_r35_c2_i0";
	ADDR [35][2][1] = "../../socket_r35_c2_i1";
	ADDR [35][2][2] = "../../socket_r35_c2_i2";
	ADDR [35][2][3] = "../../socket_r35_c2_i3";
	ADDR [35][2][4] = "../../socket_r35_c2_i4";
	ADDR [35][3][0] = "../../socket_r35_c3_i0";
	ADDR [35][3][1] = "../../socket_r35_c3_i1";
	ADDR [35][3][2] = "../../socket_r35_c3_i2";
	ADDR [35][3][3] = "../../socket_r35_c3_i3";
	ADDR [35][3][4] = "../../socket_r35_c3_i4";
	ADDR [36][0][0] = "../../socket_r36_c0_i0";
	ADDR [36][0][1] = "../../socket_r36_c0_i1";
	ADDR [36][0][2] = "../../socket_r36_c0_i2";
	ADDR [36][0][3] = "../../socket_r36_c0_i3";
	ADDR [36][0][4] = "../../socket_r36_c0_i4";
	ADDR [36][1][0] = "../../socket_r36_c1_i0";
	ADDR [36][1][1] = "../../socket_r36_c1_i1";
	ADDR [36][1][2] = "../../socket_r36_c1_i2";
	ADDR [36][1][3] = "../../socket_r36_c1_i3";
	ADDR [36][1][4] = "../../socket_r36_c1_i4";
	ADDR [36][2][0] = "../../socket_r36_c2_i0";
	ADDR [36][2][1] = "../../socket_r36_c2_i1";
	ADDR [36][2][2] = "../../socket_r36_c2_i2";
	ADDR [36][2][3] = "../../socket_r36_c2_i3";
	ADDR [36][2][4] = "../../socket_r36_c2_i4";
	ADDR [36][3][0] = "../../socket_r36_c3_i0";
	ADDR [36][3][1] = "../../socket_r36_c3_i1";
	ADDR [36][3][2] = "../../socket_r36_c3_i2";
	ADDR [36][3][3] = "../../socket_r36_c3_i3";
	ADDR [36][3][4] = "../../socket_r36_c3_i4";
	ADDR [37][0][0] = "../../socket_r37_c0_i0";
	ADDR [37][0][1] = "../../socket_r37_c0_i1";
	ADDR [37][0][2] = "../../socket_r37_c0_i2";
	ADDR [37][0][3] = "../../socket_r37_c0_i3";
	ADDR [37][0][4] = "../../socket_r37_c0_i4";
	ADDR [37][1][0] = "../../socket_r37_c1_i0";
	ADDR [37][1][1] = "../../socket_r37_c1_i1";
	ADDR [37][1][2] = "../../socket_r37_c1_i2";
	ADDR [37][1][3] = "../../socket_r37_c1_i3";
	ADDR [37][1][4] = "../../socket_r37_c1_i4";
	ADDR [37][2][0] = "../../socket_r37_c2_i0";
	ADDR [37][2][1] = "../../socket_r37_c2_i1";
	ADDR [37][2][2] = "../../socket_r37_c2_i2";
	ADDR [37][2][3] = "../../socket_r37_c2_i3";
	ADDR [37][2][4] = "../../socket_r37_c2_i4";
	ADDR [37][3][0] = "../../socket_r37_c3_i0";
	ADDR [37][3][1] = "../../socket_r37_c3_i1";
	ADDR [37][3][2] = "../../socket_r37_c3_i2";
	ADDR [37][3][3] = "../../socket_r37_c3_i3";
	ADDR [37][3][4] = "../../socket_r37_c3_i4";
	ADDR [38][0][0] = "../../socket_r38_c0_i0";
	ADDR [38][0][1] = "../../socket_r38_c0_i1";
	ADDR [38][0][2] = "../../socket_r38_c0_i2";
	ADDR [38][0][3] = "../../socket_r38_c0_i3";
	ADDR [38][0][4] = "../../socket_r38_c0_i4";
	ADDR [38][1][0] = "../../socket_r38_c1_i0";
	ADDR [38][1][1] = "../../socket_r38_c1_i1";
	ADDR [38][1][2] = "../../socket_r38_c1_i2";
	ADDR [38][1][3] = "../../socket_r38_c1_i3";
	ADDR [38][1][4] = "../../socket_r38_c1_i4";
	ADDR [38][2][0] = "../../socket_r38_c2_i0";
	ADDR [38][2][1] = "../../socket_r38_c2_i1";
	ADDR [38][2][2] = "../../socket_r38_c2_i2";
	ADDR [38][2][3] = "../../socket_r38_c2_i3";
	ADDR [38][2][4] = "../../socket_r38_c2_i4";
	ADDR [38][3][0] = "../../socket_r38_c3_i0";
	ADDR [38][3][1] = "../../socket_r38_c3_i1";
	ADDR [38][3][2] = "../../socket_r38_c3_i2";
	ADDR [38][3][3] = "../../socket_r38_c3_i3";
	ADDR [38][3][4] = "../../socket_r38_c3_i4";
	ADDR [39][0][0] = "../../socket_r39_c0_i0";
	ADDR [39][0][1] = "../../socket_r39_c0_i1";
	ADDR [39][0][2] = "../../socket_r39_c0_i2";
	ADDR [39][0][3] = "../../socket_r39_c0_i3";
	ADDR [39][0][4] = "../../socket_r39_c0_i4";
	ADDR [39][1][0] = "../../socket_r39_c1_i0";
	ADDR [39][1][1] = "../../socket_r39_c1_i1";
	ADDR [39][1][2] = "../../socket_r39_c1_i2";
	ADDR [39][1][3] = "../../socket_r39_c1_i3";
	ADDR [39][1][4] = "../../socket_r39_c1_i4";
	ADDR [39][2][0] = "../../socket_r39_c2_i0";
	ADDR [39][2][1] = "../../socket_r39_c2_i1";
	ADDR [39][2][2] = "../../socket_r39_c2_i2";
	ADDR [39][2][3] = "../../socket_r39_c2_i3";
	ADDR [39][2][4] = "../../socket_r39_c2_i4";
	ADDR [39][3][0] = "../../socket_r39_c3_i0";
	ADDR [39][3][1] = "../../socket_r39_c3_i1";
	ADDR [39][3][2] = "../../socket_r39_c3_i2";
	ADDR [39][3][3] = "../../socket_r39_c3_i3";
	ADDR [39][3][4] = "../../socket_r39_c3_i4";
	ADDR [40][0][0] = "../../socket_r40_c0_i0";
	ADDR [40][0][1] = "../../socket_r40_c0_i1";
	ADDR [40][0][2] = "../../socket_r40_c0_i2";
	ADDR [40][0][3] = "../../socket_r40_c0_i3";
	ADDR [40][0][4] = "../../socket_r40_c0_i4";
	ADDR [40][1][0] = "../../socket_r40_c1_i0";
	ADDR [40][1][1] = "../../socket_r40_c1_i1";
	ADDR [40][1][2] = "../../socket_r40_c1_i2";
	ADDR [40][1][3] = "../../socket_r40_c1_i3";
	ADDR [40][1][4] = "../../socket_r40_c1_i4";
	ADDR [40][2][0] = "../../socket_r40_c2_i0";
	ADDR [40][2][1] = "../../socket_r40_c2_i1";
	ADDR [40][2][2] = "../../socket_r40_c2_i2";
	ADDR [40][2][3] = "../../socket_r40_c2_i3";
	ADDR [40][2][4] = "../../socket_r40_c2_i4";
	ADDR [40][3][0] = "../../socket_r40_c3_i0";
	ADDR [40][3][1] = "../../socket_r40_c3_i1";
	ADDR [40][3][2] = "../../socket_r40_c3_i2";
	ADDR [40][3][3] = "../../socket_r40_c3_i3";
	ADDR [40][3][4] = "../../socket_r40_c3_i4";
	ADDR [41][0][0] = "../../socket_r41_c0_i0";
	ADDR [41][0][1] = "../../socket_r41_c0_i1";
	ADDR [41][0][2] = "../../socket_r41_c0_i2";
	ADDR [41][0][3] = "../../socket_r41_c0_i3";
	ADDR [41][0][4] = "../../socket_r41_c0_i4";
	ADDR [41][1][0] = "../../socket_r41_c1_i0";
	ADDR [41][1][1] = "../../socket_r41_c1_i1";
	ADDR [41][1][2] = "../../socket_r41_c1_i2";
	ADDR [41][1][3] = "../../socket_r41_c1_i3";
	ADDR [41][1][4] = "../../socket_r41_c1_i4";
	ADDR [41][2][0] = "../../socket_r41_c2_i0";
	ADDR [41][2][1] = "../../socket_r41_c2_i1";
	ADDR [41][2][2] = "../../socket_r41_c2_i2";
	ADDR [41][2][3] = "../../socket_r41_c2_i3";
	ADDR [41][2][4] = "../../socket_r41_c2_i4";
	ADDR [41][3][0] = "../../socket_r41_c3_i0";
	ADDR [41][3][1] = "../../socket_r41_c3_i1";
	ADDR [41][3][2] = "../../socket_r41_c3_i2";
	ADDR [41][3][3] = "../../socket_r41_c3_i3";
	ADDR [41][3][4] = "../../socket_r41_c3_i4";
	ADDR [42][0][0] = "../../socket_r42_c0_i0";
	ADDR [42][0][1] = "../../socket_r42_c0_i1";
	ADDR [42][0][2] = "../../socket_r42_c0_i2";
	ADDR [42][0][3] = "../../socket_r42_c0_i3";
	ADDR [42][0][4] = "../../socket_r42_c0_i4";
	ADDR [42][1][0] = "../../socket_r42_c1_i0";
	ADDR [42][1][1] = "../../socket_r42_c1_i1";
	ADDR [42][1][2] = "../../socket_r42_c1_i2";
	ADDR [42][1][3] = "../../socket_r42_c1_i3";
	ADDR [42][1][4] = "../../socket_r42_c1_i4";
	ADDR [42][2][0] = "../../socket_r42_c2_i0";
	ADDR [42][2][1] = "../../socket_r42_c2_i1";
	ADDR [42][2][2] = "../../socket_r42_c2_i2";
	ADDR [42][2][3] = "../../socket_r42_c2_i3";
	ADDR [42][2][4] = "../../socket_r42_c2_i4";
	ADDR [42][3][0] = "../../socket_r42_c3_i0";
	ADDR [42][3][1] = "../../socket_r42_c3_i1";
	ADDR [42][3][2] = "../../socket_r42_c3_i2";
	ADDR [42][3][3] = "../../socket_r42_c3_i3";
	ADDR [42][3][4] = "../../socket_r42_c3_i4";
	ADDR [43][0][0] = "../../socket_r43_c0_i0";
	ADDR [43][0][1] = "../../socket_r43_c0_i1";
	ADDR [43][0][2] = "../../socket_r43_c0_i2";
	ADDR [43][0][3] = "../../socket_r43_c0_i3";
	ADDR [43][0][4] = "../../socket_r43_c0_i4";
	ADDR [43][1][0] = "../../socket_r43_c1_i0";
	ADDR [43][1][1] = "../../socket_r43_c1_i1";
	ADDR [43][1][2] = "../../socket_r43_c1_i2";
	ADDR [43][1][3] = "../../socket_r43_c1_i3";
	ADDR [43][1][4] = "../../socket_r43_c1_i4";
	ADDR [43][2][0] = "../../socket_r43_c2_i0";
	ADDR [43][2][1] = "../../socket_r43_c2_i1";
	ADDR [43][2][2] = "../../socket_r43_c2_i2";
	ADDR [43][2][3] = "../../socket_r43_c2_i3";
	ADDR [43][2][4] = "../../socket_r43_c2_i4";
	ADDR [43][3][0] = "../../socket_r43_c3_i0";
	ADDR [43][3][1] = "../../socket_r43_c3_i1";
	ADDR [43][3][2] = "../../socket_r43_c3_i2";
	ADDR [43][3][3] = "../../socket_r43_c3_i3";
	ADDR [43][3][4] = "../../socket_r43_c3_i4";
	ADDR [44][0][0] = "../../socket_r44_c0_i0";
	ADDR [44][0][1] = "../../socket_r44_c0_i1";
	ADDR [44][0][2] = "../../socket_r44_c0_i2";
	ADDR [44][0][3] = "../../socket_r44_c0_i3";
	ADDR [44][0][4] = "../../socket_r44_c0_i4";
	ADDR [44][1][0] = "../../socket_r44_c1_i0";
	ADDR [44][1][1] = "../../socket_r44_c1_i1";
	ADDR [44][1][2] = "../../socket_r44_c1_i2";
	ADDR [44][1][3] = "../../socket_r44_c1_i3";
	ADDR [44][1][4] = "../../socket_r44_c1_i4";
	ADDR [44][2][0] = "../../socket_r44_c2_i0";
	ADDR [44][2][1] = "../../socket_r44_c2_i1";
	ADDR [44][2][2] = "../../socket_r44_c2_i2";
	ADDR [44][2][3] = "../../socket_r44_c2_i3";
	ADDR [44][2][4] = "../../socket_r44_c2_i4";
	ADDR [44][3][0] = "../../socket_r44_c3_i0";
	ADDR [44][3][1] = "../../socket_r44_c3_i1";
	ADDR [44][3][2] = "../../socket_r44_c3_i2";
	ADDR [44][3][3] = "../../socket_r44_c3_i3";
	ADDR [44][3][4] = "../../socket_r44_c3_i4";
	ADDR [45][0][0] = "../../socket_r45_c0_i0";
	ADDR [45][0][1] = "../../socket_r45_c0_i1";
	ADDR [45][0][2] = "../../socket_r45_c0_i2";
	ADDR [45][0][3] = "../../socket_r45_c0_i3";
	ADDR [45][0][4] = "../../socket_r45_c0_i4";
	ADDR [45][1][0] = "../../socket_r45_c1_i0";
	ADDR [45][1][1] = "../../socket_r45_c1_i1";
	ADDR [45][1][2] = "../../socket_r45_c1_i2";
	ADDR [45][1][3] = "../../socket_r45_c1_i3";
	ADDR [45][1][4] = "../../socket_r45_c1_i4";
	ADDR [45][2][0] = "../../socket_r45_c2_i0";
	ADDR [45][2][1] = "../../socket_r45_c2_i1";
	ADDR [45][2][2] = "../../socket_r45_c2_i2";
	ADDR [45][2][3] = "../../socket_r45_c2_i3";
	ADDR [45][2][4] = "../../socket_r45_c2_i4";
	ADDR [45][3][0] = "../../socket_r45_c3_i0";
	ADDR [45][3][1] = "../../socket_r45_c3_i1";
	ADDR [45][3][2] = "../../socket_r45_c3_i2";
	ADDR [45][3][3] = "../../socket_r45_c3_i3";
	ADDR [45][3][4] = "../../socket_r45_c3_i4";
	ADDR [46][0][0] = "../../socket_r46_c0_i0";
	ADDR [46][0][1] = "../../socket_r46_c0_i1";
	ADDR [46][0][2] = "../../socket_r46_c0_i2";
	ADDR [46][0][3] = "../../socket_r46_c0_i3";
	ADDR [46][0][4] = "../../socket_r46_c0_i4";
	ADDR [46][1][0] = "../../socket_r46_c1_i0";
	ADDR [46][1][1] = "../../socket_r46_c1_i1";
	ADDR [46][1][2] = "../../socket_r46_c1_i2";
	ADDR [46][1][3] = "../../socket_r46_c1_i3";
	ADDR [46][1][4] = "../../socket_r46_c1_i4";
	ADDR [46][2][0] = "../../socket_r46_c2_i0";
	ADDR [46][2][1] = "../../socket_r46_c2_i1";
	ADDR [46][2][2] = "../../socket_r46_c2_i2";
	ADDR [46][2][3] = "../../socket_r46_c2_i3";
	ADDR [46][2][4] = "../../socket_r46_c2_i4";
	ADDR [46][3][0] = "../../socket_r46_c3_i0";
	ADDR [46][3][1] = "../../socket_r46_c3_i1";
	ADDR [46][3][2] = "../../socket_r46_c3_i2";
	ADDR [46][3][3] = "../../socket_r46_c3_i3";
	ADDR [46][3][4] = "../../socket_r46_c3_i4";
	ADDR [47][0][0] = "../../socket_r47_c0_i0";
	ADDR [47][0][1] = "../../socket_r47_c0_i1";
	ADDR [47][0][2] = "../../socket_r47_c0_i2";
	ADDR [47][0][3] = "../../socket_r47_c0_i3";
	ADDR [47][0][4] = "../../socket_r47_c0_i4";
	ADDR [47][1][0] = "../../socket_r47_c1_i0";
	ADDR [47][1][1] = "../../socket_r47_c1_i1";
	ADDR [47][1][2] = "../../socket_r47_c1_i2";
	ADDR [47][1][3] = "../../socket_r47_c1_i3";
	ADDR [47][1][4] = "../../socket_r47_c1_i4";
	ADDR [47][2][0] = "../../socket_r47_c2_i0";
	ADDR [47][2][1] = "../../socket_r47_c2_i1";
	ADDR [47][2][2] = "../../socket_r47_c2_i2";
	ADDR [47][2][3] = "../../socket_r47_c2_i3";
	ADDR [47][2][4] = "../../socket_r47_c2_i4";
	ADDR [47][3][0] = "../../socket_r47_c3_i0";
	ADDR [47][3][1] = "../../socket_r47_c3_i1";
	ADDR [47][3][2] = "../../socket_r47_c3_i2";
	ADDR [47][3][3] = "../../socket_r47_c3_i3";
	ADDR [47][3][4] = "../../socket_r47_c3_i4";
	ADDR [48][0][0] = "../../socket_r48_c0_i0";
	ADDR [48][0][1] = "../../socket_r48_c0_i1";
	ADDR [48][0][2] = "../../socket_r48_c0_i2";
	ADDR [48][0][3] = "../../socket_r48_c0_i3";
	ADDR [48][0][4] = "../../socket_r48_c0_i4";
	ADDR [48][1][0] = "../../socket_r48_c1_i0";
	ADDR [48][1][1] = "../../socket_r48_c1_i1";
	ADDR [48][1][2] = "../../socket_r48_c1_i2";
	ADDR [48][1][3] = "../../socket_r48_c1_i3";
	ADDR [48][1][4] = "../../socket_r48_c1_i4";
	ADDR [48][2][0] = "../../socket_r48_c2_i0";
	ADDR [48][2][1] = "../../socket_r48_c2_i1";
	ADDR [48][2][2] = "../../socket_r48_c2_i2";
	ADDR [48][2][3] = "../../socket_r48_c2_i3";
	ADDR [48][2][4] = "../../socket_r48_c2_i4";
	ADDR [48][3][0] = "../../socket_r48_c3_i0";
	ADDR [48][3][1] = "../../socket_r48_c3_i1";
	ADDR [48][3][2] = "../../socket_r48_c3_i2";
	ADDR [48][3][3] = "../../socket_r48_c3_i3";
	ADDR [48][3][4] = "../../socket_r48_c3_i4";
	ADDR [49][0][0] = "../../socket_r49_c0_i0";
	ADDR [49][0][1] = "../../socket_r49_c0_i1";
	ADDR [49][0][2] = "../../socket_r49_c0_i2";
	ADDR [49][0][3] = "../../socket_r49_c0_i3";
	ADDR [49][0][4] = "../../socket_r49_c0_i4";
	ADDR [49][1][0] = "../../socket_r49_c1_i0";
	ADDR [49][1][1] = "../../socket_r49_c1_i1";
	ADDR [49][1][2] = "../../socket_r49_c1_i2";
	ADDR [49][1][3] = "../../socket_r49_c1_i3";
	ADDR [49][1][4] = "../../socket_r49_c1_i4";
	ADDR [49][2][0] = "../../socket_r49_c2_i0";
	ADDR [49][2][1] = "../../socket_r49_c2_i1";
	ADDR [49][2][2] = "../../socket_r49_c2_i2";
	ADDR [49][2][3] = "../../socket_r49_c2_i3";
	ADDR [49][2][4] = "../../socket_r49_c2_i4";
	ADDR [49][3][0] = "../../socket_r49_c3_i0";
	ADDR [49][3][1] = "../../socket_r49_c3_i1";
	ADDR [49][3][2] = "../../socket_r49_c3_i2";
	ADDR [49][3][3] = "../../socket_r49_c3_i3";
	ADDR [49][3][4] = "../../socket_r49_c3_i4";
	ADDR [50][0][0] = "../../socket_r50_c0_i0";
	ADDR [50][0][1] = "../../socket_r50_c0_i1";
	ADDR [50][0][2] = "../../socket_r50_c0_i2";
	ADDR [50][0][3] = "../../socket_r50_c0_i3";
	ADDR [50][0][4] = "../../socket_r50_c0_i4";
	ADDR [50][1][0] = "../../socket_r50_c1_i0";
	ADDR [50][1][1] = "../../socket_r50_c1_i1";
	ADDR [50][1][2] = "../../socket_r50_c1_i2";
	ADDR [50][1][3] = "../../socket_r50_c1_i3";
	ADDR [50][1][4] = "../../socket_r50_c1_i4";
	ADDR [50][2][0] = "../../socket_r50_c2_i0";
	ADDR [50][2][1] = "../../socket_r50_c2_i1";
	ADDR [50][2][2] = "../../socket_r50_c2_i2";
	ADDR [50][2][3] = "../../socket_r50_c2_i3";
	ADDR [50][2][4] = "../../socket_r50_c2_i4";
	ADDR [50][3][0] = "../../socket_r50_c3_i0";
	ADDR [50][3][1] = "../../socket_r50_c3_i1";
	ADDR [50][3][2] = "../../socket_r50_c3_i2";
	ADDR [50][3][3] = "../../socket_r50_c3_i3";
	ADDR [50][3][4] = "../../socket_r50_c3_i4";
	ADDR [51][0][0] = "../../socket_r51_c0_i0";
	ADDR [51][0][1] = "../../socket_r51_c0_i1";
	ADDR [51][0][2] = "../../socket_r51_c0_i2";
	ADDR [51][0][3] = "../../socket_r51_c0_i3";
	ADDR [51][0][4] = "../../socket_r51_c0_i4";
	ADDR [51][1][0] = "../../socket_r51_c1_i0";
	ADDR [51][1][1] = "../../socket_r51_c1_i1";
	ADDR [51][1][2] = "../../socket_r51_c1_i2";
	ADDR [51][1][3] = "../../socket_r51_c1_i3";
	ADDR [51][1][4] = "../../socket_r51_c1_i4";
	ADDR [51][2][0] = "../../socket_r51_c2_i0";
	ADDR [51][2][1] = "../../socket_r51_c2_i1";
	ADDR [51][2][2] = "../../socket_r51_c2_i2";
	ADDR [51][2][3] = "../../socket_r51_c2_i3";
	ADDR [51][2][4] = "../../socket_r51_c2_i4";
	ADDR [51][3][0] = "../../socket_r51_c3_i0";
	ADDR [51][3][1] = "../../socket_r51_c3_i1";
	ADDR [51][3][2] = "../../socket_r51_c3_i2";
	ADDR [51][3][3] = "../../socket_r51_c3_i3";
	ADDR [51][3][4] = "../../socket_r51_c3_i4";
	ADDR [52][0][0] = "../../socket_r52_c0_i0";
	ADDR [52][0][1] = "../../socket_r52_c0_i1";
	ADDR [52][0][2] = "../../socket_r52_c0_i2";
	ADDR [52][0][3] = "../../socket_r52_c0_i3";
	ADDR [52][0][4] = "../../socket_r52_c0_i4";
	ADDR [52][1][0] = "../../socket_r52_c1_i0";
	ADDR [52][1][1] = "../../socket_r52_c1_i1";
	ADDR [52][1][2] = "../../socket_r52_c1_i2";
	ADDR [52][1][3] = "../../socket_r52_c1_i3";
	ADDR [52][1][4] = "../../socket_r52_c1_i4";
	ADDR [52][2][0] = "../../socket_r52_c2_i0";
	ADDR [52][2][1] = "../../socket_r52_c2_i1";
	ADDR [52][2][2] = "../../socket_r52_c2_i2";
	ADDR [52][2][3] = "../../socket_r52_c2_i3";
	ADDR [52][2][4] = "../../socket_r52_c2_i4";
	ADDR [52][3][0] = "../../socket_r52_c3_i0";
	ADDR [52][3][1] = "../../socket_r52_c3_i1";
	ADDR [52][3][2] = "../../socket_r52_c3_i2";
	ADDR [52][3][3] = "../../socket_r52_c3_i3";
	ADDR [52][3][4] = "../../socket_r52_c3_i4";
	ADDR [53][0][0] = "../../socket_r53_c0_i0";
	ADDR [53][0][1] = "../../socket_r53_c0_i1";
	ADDR [53][0][2] = "../../socket_r53_c0_i2";
	ADDR [53][0][3] = "../../socket_r53_c0_i3";
	ADDR [53][0][4] = "../../socket_r53_c0_i4";
	ADDR [53][1][0] = "../../socket_r53_c1_i0";
	ADDR [53][1][1] = "../../socket_r53_c1_i1";
	ADDR [53][1][2] = "../../socket_r53_c1_i2";
	ADDR [53][1][3] = "../../socket_r53_c1_i3";
	ADDR [53][1][4] = "../../socket_r53_c1_i4";
	ADDR [53][2][0] = "../../socket_r53_c2_i0";
	ADDR [53][2][1] = "../../socket_r53_c2_i1";
	ADDR [53][2][2] = "../../socket_r53_c2_i2";
	ADDR [53][2][3] = "../../socket_r53_c2_i3";
	ADDR [53][2][4] = "../../socket_r53_c2_i4";
	ADDR [53][3][0] = "../../socket_r53_c3_i0";
	ADDR [53][3][1] = "../../socket_r53_c3_i1";
	ADDR [53][3][2] = "../../socket_r53_c3_i2";
	ADDR [53][3][3] = "../../socket_r53_c3_i3";
	ADDR [53][3][4] = "../../socket_r53_c3_i4";
	ADDR [54][0][0] = "../../socket_r54_c0_i0";
	ADDR [54][0][1] = "../../socket_r54_c0_i1";
	ADDR [54][0][2] = "../../socket_r54_c0_i2";
	ADDR [54][0][3] = "../../socket_r54_c0_i3";
	ADDR [54][0][4] = "../../socket_r54_c0_i4";
	ADDR [54][1][0] = "../../socket_r54_c1_i0";
	ADDR [54][1][1] = "../../socket_r54_c1_i1";
	ADDR [54][1][2] = "../../socket_r54_c1_i2";
	ADDR [54][1][3] = "../../socket_r54_c1_i3";
	ADDR [54][1][4] = "../../socket_r54_c1_i4";
	ADDR [54][2][0] = "../../socket_r54_c2_i0";
	ADDR [54][2][1] = "../../socket_r54_c2_i1";
	ADDR [54][2][2] = "../../socket_r54_c2_i2";
	ADDR [54][2][3] = "../../socket_r54_c2_i3";
	ADDR [54][2][4] = "../../socket_r54_c2_i4";
	ADDR [54][3][0] = "../../socket_r54_c3_i0";
	ADDR [54][3][1] = "../../socket_r54_c3_i1";
	ADDR [54][3][2] = "../../socket_r54_c3_i2";
	ADDR [54][3][3] = "../../socket_r54_c3_i3";
	ADDR [54][3][4] = "../../socket_r54_c3_i4";
	ADDR [55][0][0] = "../../socket_r55_c0_i0";
	ADDR [55][0][1] = "../../socket_r55_c0_i1";
	ADDR [55][0][2] = "../../socket_r55_c0_i2";
	ADDR [55][0][3] = "../../socket_r55_c0_i3";
	ADDR [55][0][4] = "../../socket_r55_c0_i4";
	ADDR [55][1][0] = "../../socket_r55_c1_i0";
	ADDR [55][1][1] = "../../socket_r55_c1_i1";
	ADDR [55][1][2] = "../../socket_r55_c1_i2";
	ADDR [55][1][3] = "../../socket_r55_c1_i3";
	ADDR [55][1][4] = "../../socket_r55_c1_i4";
	ADDR [55][2][0] = "../../socket_r55_c2_i0";
	ADDR [55][2][1] = "../../socket_r55_c2_i1";
	ADDR [55][2][2] = "../../socket_r55_c2_i2";
	ADDR [55][2][3] = "../../socket_r55_c2_i3";
	ADDR [55][2][4] = "../../socket_r55_c2_i4";
	ADDR [55][3][0] = "../../socket_r55_c3_i0";
	ADDR [55][3][1] = "../../socket_r55_c3_i1";
	ADDR [55][3][2] = "../../socket_r55_c3_i2";
	ADDR [55][3][3] = "../../socket_r55_c3_i3";
	ADDR [55][3][4] = "../../socket_r55_c3_i4";
	ADDR [56][0][0] = "../../socket_r56_c0_i0";
	ADDR [56][0][1] = "../../socket_r56_c0_i1";
	ADDR [56][0][2] = "../../socket_r56_c0_i2";
	ADDR [56][0][3] = "../../socket_r56_c0_i3";
	ADDR [56][0][4] = "../../socket_r56_c0_i4";
	ADDR [56][1][0] = "../../socket_r56_c1_i0";
	ADDR [56][1][1] = "../../socket_r56_c1_i1";
	ADDR [56][1][2] = "../../socket_r56_c1_i2";
	ADDR [56][1][3] = "../../socket_r56_c1_i3";
	ADDR [56][1][4] = "../../socket_r56_c1_i4";
	ADDR [56][2][0] = "../../socket_r56_c2_i0";
	ADDR [56][2][1] = "../../socket_r56_c2_i1";
	ADDR [56][2][2] = "../../socket_r56_c2_i2";
	ADDR [56][2][3] = "../../socket_r56_c2_i3";
	ADDR [56][2][4] = "../../socket_r56_c2_i4";
	ADDR [56][3][0] = "../../socket_r56_c3_i0";
	ADDR [56][3][1] = "../../socket_r56_c3_i1";
	ADDR [56][3][2] = "../../socket_r56_c3_i2";
	ADDR [56][3][3] = "../../socket_r56_c3_i3";
	ADDR [56][3][4] = "../../socket_r56_c3_i4";
	ADDR [57][0][0] = "../../socket_r57_c0_i0";
	ADDR [57][0][1] = "../../socket_r57_c0_i1";
	ADDR [57][0][2] = "../../socket_r57_c0_i2";
	ADDR [57][0][3] = "../../socket_r57_c0_i3";
	ADDR [57][0][4] = "../../socket_r57_c0_i4";
	ADDR [57][1][0] = "../../socket_r57_c1_i0";
	ADDR [57][1][1] = "../../socket_r57_c1_i1";
	ADDR [57][1][2] = "../../socket_r57_c1_i2";
	ADDR [57][1][3] = "../../socket_r57_c1_i3";
	ADDR [57][1][4] = "../../socket_r57_c1_i4";
	ADDR [57][2][0] = "../../socket_r57_c2_i0";
	ADDR [57][2][1] = "../../socket_r57_c2_i1";
	ADDR [57][2][2] = "../../socket_r57_c2_i2";
	ADDR [57][2][3] = "../../socket_r57_c2_i3";
	ADDR [57][2][4] = "../../socket_r57_c2_i4";
	ADDR [57][3][0] = "../../socket_r57_c3_i0";
	ADDR [57][3][1] = "../../socket_r57_c3_i1";
	ADDR [57][3][2] = "../../socket_r57_c3_i2";
	ADDR [57][3][3] = "../../socket_r57_c3_i3";
	ADDR [57][3][4] = "../../socket_r57_c3_i4";
	ADDR [58][0][0] = "../../socket_r58_c0_i0";
	ADDR [58][0][1] = "../../socket_r58_c0_i1";
	ADDR [58][0][2] = "../../socket_r58_c0_i2";
	ADDR [58][0][3] = "../../socket_r58_c0_i3";
	ADDR [58][0][4] = "../../socket_r58_c0_i4";
	ADDR [58][1][0] = "../../socket_r58_c1_i0";
	ADDR [58][1][1] = "../../socket_r58_c1_i1";
	ADDR [58][1][2] = "../../socket_r58_c1_i2";
	ADDR [58][1][3] = "../../socket_r58_c1_i3";
	ADDR [58][1][4] = "../../socket_r58_c1_i4";
	ADDR [58][2][0] = "../../socket_r58_c2_i0";
	ADDR [58][2][1] = "../../socket_r58_c2_i1";
	ADDR [58][2][2] = "../../socket_r58_c2_i2";
	ADDR [58][2][3] = "../../socket_r58_c2_i3";
	ADDR [58][2][4] = "../../socket_r58_c2_i4";
	ADDR [58][3][0] = "../../socket_r58_c3_i0";
	ADDR [58][3][1] = "../../socket_r58_c3_i1";
	ADDR [58][3][2] = "../../socket_r58_c3_i2";
	ADDR [58][3][3] = "../../socket_r58_c3_i3";
	ADDR [58][3][4] = "../../socket_r58_c3_i4";
	ADDR [59][0][0] = "../../socket_r59_c0_i0";
	ADDR [59][0][1] = "../../socket_r59_c0_i1";
	ADDR [59][0][2] = "../../socket_r59_c0_i2";
	ADDR [59][0][3] = "../../socket_r59_c0_i3";
	ADDR [59][0][4] = "../../socket_r59_c0_i4";
	ADDR [59][1][0] = "../../socket_r59_c1_i0";
	ADDR [59][1][1] = "../../socket_r59_c1_i1";
	ADDR [59][1][2] = "../../socket_r59_c1_i2";
	ADDR [59][1][3] = "../../socket_r59_c1_i3";
	ADDR [59][1][4] = "../../socket_r59_c1_i4";
	ADDR [59][2][0] = "../../socket_r59_c2_i0";
	ADDR [59][2][1] = "../../socket_r59_c2_i1";
	ADDR [59][2][2] = "../../socket_r59_c2_i2";
	ADDR [59][2][3] = "../../socket_r59_c2_i3";
	ADDR [59][2][4] = "../../socket_r59_c2_i4";
	ADDR [59][3][0] = "../../socket_r59_c3_i0";
	ADDR [59][3][1] = "../../socket_r59_c3_i1";
	ADDR [59][3][2] = "../../socket_r59_c3_i2";
	ADDR [59][3][3] = "../../socket_r59_c3_i3";
	ADDR [59][3][4] = "../../socket_r59_c3_i4";
	ADDR [60][0][0] = "../../socket_r60_c0_i0";
	ADDR [60][0][1] = "../../socket_r60_c0_i1";
	ADDR [60][0][2] = "../../socket_r60_c0_i2";
	ADDR [60][0][3] = "../../socket_r60_c0_i3";
	ADDR [60][0][4] = "../../socket_r60_c0_i4";
	ADDR [60][1][0] = "../../socket_r60_c1_i0";
	ADDR [60][1][1] = "../../socket_r60_c1_i1";
	ADDR [60][1][2] = "../../socket_r60_c1_i2";
	ADDR [60][1][3] = "../../socket_r60_c1_i3";
	ADDR [60][1][4] = "../../socket_r60_c1_i4";
	ADDR [60][2][0] = "../../socket_r60_c2_i0";
	ADDR [60][2][1] = "../../socket_r60_c2_i1";
	ADDR [60][2][2] = "../../socket_r60_c2_i2";
	ADDR [60][2][3] = "../../socket_r60_c2_i3";
	ADDR [60][2][4] = "../../socket_r60_c2_i4";
	ADDR [60][3][0] = "../../socket_r60_c3_i0";
	ADDR [60][3][1] = "../../socket_r60_c3_i1";
	ADDR [60][3][2] = "../../socket_r60_c3_i2";
	ADDR [60][3][3] = "../../socket_r60_c3_i3";
	ADDR [60][3][4] = "../../socket_r60_c3_i4";
	ADDR [61][0][0] = "../../socket_r61_c0_i0";
	ADDR [61][0][1] = "../../socket_r61_c0_i1";
	ADDR [61][0][2] = "../../socket_r61_c0_i2";
	ADDR [61][0][3] = "../../socket_r61_c0_i3";
	ADDR [61][0][4] = "../../socket_r61_c0_i4";
	ADDR [61][1][0] = "../../socket_r61_c1_i0";
	ADDR [61][1][1] = "../../socket_r61_c1_i1";
	ADDR [61][1][2] = "../../socket_r61_c1_i2";
	ADDR [61][1][3] = "../../socket_r61_c1_i3";
	ADDR [61][1][4] = "../../socket_r61_c1_i4";
	ADDR [61][2][0] = "../../socket_r61_c2_i0";
	ADDR [61][2][1] = "../../socket_r61_c2_i1";
	ADDR [61][2][2] = "../../socket_r61_c2_i2";
	ADDR [61][2][3] = "../../socket_r61_c2_i3";
	ADDR [61][2][4] = "../../socket_r61_c2_i4";
	ADDR [61][3][0] = "../../socket_r61_c3_i0";
	ADDR [61][3][1] = "../../socket_r61_c3_i1";
	ADDR [61][3][2] = "../../socket_r61_c3_i2";
	ADDR [61][3][3] = "../../socket_r61_c3_i3";
	ADDR [61][3][4] = "../../socket_r61_c3_i4";
	ADDR [62][0][0] = "../../socket_r62_c0_i0";
	ADDR [62][0][1] = "../../socket_r62_c0_i1";
	ADDR [62][0][2] = "../../socket_r62_c0_i2";
	ADDR [62][0][3] = "../../socket_r62_c0_i3";
	ADDR [62][0][4] = "../../socket_r62_c0_i4";
	ADDR [62][1][0] = "../../socket_r62_c1_i0";
	ADDR [62][1][1] = "../../socket_r62_c1_i1";
	ADDR [62][1][2] = "../../socket_r62_c1_i2";
	ADDR [62][1][3] = "../../socket_r62_c1_i3";
	ADDR [62][1][4] = "../../socket_r62_c1_i4";
	ADDR [62][2][0] = "../../socket_r62_c2_i0";
	ADDR [62][2][1] = "../../socket_r62_c2_i1";
	ADDR [62][2][2] = "../../socket_r62_c2_i2";
	ADDR [62][2][3] = "../../socket_r62_c2_i3";
	ADDR [62][2][4] = "../../socket_r62_c2_i4";
	ADDR [62][3][0] = "../../socket_r62_c3_i0";
	ADDR [62][3][1] = "../../socket_r62_c3_i1";
	ADDR [62][3][2] = "../../socket_r62_c3_i2";
	ADDR [62][3][3] = "../../socket_r62_c3_i3";
	ADDR [62][3][4] = "../../socket_r62_c3_i4";
	ADDR [63][0][0] = "../../socket_r63_c0_i0";
	ADDR [63][0][1] = "../../socket_r63_c0_i1";
	ADDR [63][0][2] = "../../socket_r63_c0_i2";
	ADDR [63][0][3] = "../../socket_r63_c0_i3";
	ADDR [63][0][4] = "../../socket_r63_c0_i4";
	ADDR [63][1][0] = "../../socket_r63_c1_i0";
	ADDR [63][1][1] = "../../socket_r63_c1_i1";
	ADDR [63][1][2] = "../../socket_r63_c1_i2";
	ADDR [63][1][3] = "../../socket_r63_c1_i3";
	ADDR [63][1][4] = "../../socket_r63_c1_i4";
	ADDR [63][2][0] = "../../socket_r63_c2_i0";
	ADDR [63][2][1] = "../../socket_r63_c2_i1";
	ADDR [63][2][2] = "../../socket_r63_c2_i2";
	ADDR [63][2][3] = "../../socket_r63_c2_i3";
	ADDR [63][2][4] = "../../socket_r63_c2_i4";
	ADDR [63][3][0] = "../../socket_r63_c3_i0";
	ADDR [63][3][1] = "../../socket_r63_c3_i1";
	ADDR [63][3][2] = "../../socket_r63_c3_i2";
	ADDR [63][3][3] = "../../socket_r63_c3_i3";
	ADDR [63][3][4] = "../../socket_r63_c3_i4";


}





























































































