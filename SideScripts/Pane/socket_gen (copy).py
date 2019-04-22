numRouters = 9
before = ["ADDR ["]
before1 = ["]["]
before2 = ["] = "]
first = ["\"../socket_r"]
second = ["_c"]
third = ["_i"]
mytab = ["\t"]
line = []
out = open("socket_lib.cc", "w")
for i in range(numRouters):
    for j in range(4):
        for k in range(5):
            line = line + mytab + before + [str(i)] + before1 + [str(j)] + before1 + [str(k)] + before2 + first + [str(i)] + second + [str(j)] + third + [str(k)] + ["\";\n"]

new_line = "".join(line)





file_header = [


"#include<stdio.h>\n" +
"#include <stdlib.h>\n" +
"#include <sys/types.h>\n" +
"#include <sys/socket.h>\n" +
"#include <sys/un.h>\n" +
"#include <unistd.h>\n" +
"#include <omnetpp.h>\n" +
"#include <poll.h>\n" +
"#define numRouters " + str(numRouters) + "\n" +
"#define numClients 4\n" +

"using namespace omnetpp;\n" +

"const char * ADDR[numRouters][numClients][5];\n" +

"int fromlen;\n" +
"/*register*/ int s[numRouters][numClients][5], ns[numRouters][numClients][5], len;\n" +
"struct sockaddr_un saun[numRouters][numClients][5], fsaun[numRouters][numClients][5];\n" +

"//Pollfds\n" +
"struct pollfd fds[numRouters][4][5];\n" +
"FILE *fp[numRouters][numClients][5];\n" +

"SimTime currenttime;\n" +

"bool hasmsg[numRouters][numClients];\n" +

"bool hasvalue[numRouters][numClients][5];\n" +

"pollfd getfds(int R,int C,int P)\n" +
"{ \n" +
	"return fds[R][C][P];\n" +
"} \n" +

"FILE *getfp(int R,int C,int P) \n" +
"{ \n" +
	"return fp[R][C][P];\n" +
"} \n" +

"void setup_pollfd() \n" +
"{ \n" +
	"\tint R,C,P;\n" +
	"\tfor(R=0;R<numRouters;R++)\n" +
	"\t{\n" +
		"\t\tfor(C=0;C<numClients;C++)\n" +
		"\t\t{\n" +
		    "\t\t\tfor(P=0;P<5;P++) \n" +
		    "\t\t\t{ \n" +
				"\t\t\t\tfp[R][C][P] = fdopen(ns[R][C][P], \"r\");\n " +
				"\t\t\t\tfds[R][C][P].fd = ns[R][C][P];                  //FDS-Client\n " +
				"\t\t\t\tfds[R][C][P].events = POLLIN;\n " +
		    "\t\t\t} \n" +
		"\t\t}\n" +
	"\t}\n" +
"} \n" +

"bool setcontrollertime(SimTime current_time) \n" +
"{ \n" +
	"\tcurrenttime = current_time;\n"
"} \n" +

"SimTime getcontrollertime() \n" +
"{ \n" +
	"\treturn currenttime; \n" +
"} \n" +

"bool getmsg(int R,int C) \n" +
"{ \n" +
	"\treturn hasmsg[R][C]; \n" +
"} \n" +

"void setmsg(bool value,int R,int C) \n" +
"{ \n" +
	"\thasmsg[R][C] = value; \n" +
"} \n" +

"bool gethasvalue(int R,int C,int P) \n" +
"{ \n" +
	"\treturn hasvalue[R][C][P]; \n" +
"} \n" +

"void sethasvalue(bool value,int R,int C,int P) \n" +
"{ \n" +
	"\thasvalue[R][C][P] = value; \n" +
"} \n" +

"void create_socket(int R,int C,int P) \n" +
"{ \n" +
	"\tif ((s[R][C][P] = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) \n" +
        "\t\t{\n" +
			"\t\t\tperror(\"server: socket\");\n" +
			"\t\t\texit(1);\n" +
        "\t\t}\n" +
"\t\t//	int on=1; \n" +
"\t\t//	if((setsockopt(s[R][C][P], SOL_SOCKET,  SO_REUSEADDR,(char *)&on, sizeof(on))) < 0)		//Can remove \n" +
"\t\t//	{ \n" +
"\t\t//		perror(\"setsockopt() failed\"); \n" +
"\t\t//		exit(1); \n" +
"\t\t//	} \n" +
        "\t\tsaun[R][C][P].sun_family = AF_UNIX; \n " +
        "\t\tstrcpy(saun[R][C][P].sun_path, ADDR[R][C][P]); \n " +

        "\t\tunlink(ADDR[R][C][P]); \n " +
        "\t\tlen = sizeof(saun[R][C][P].sun_family) + strlen(saun[R][C][P].sun_path); \n " +

        "\t\tif (bind(s[R][C][P],(struct sockaddr *) &saun[R][C][P], len) < 0) \n " +
        "\t\t{ \n " +
		"\t\tperror(\"server: bind\"); \n " +
		"\t\texit(1); \n " +
        "\t\t} \n " +
        "\t\tif (listen(s[R][C][P], 5) < 0) \n " +
        "\t\t{ \n " +
		"\t\tperror(\"server: listen\"); \n " +
		"\t\texit(1); \n " +
        "\t\t} \n " +
        "\t\tif ((ns[R][C][P] = accept(s[R][C][P], (struct sockaddr *) &fsaun[R][C][P],(socklen_t*) &fromlen)) < 0) \n " +
        "\t\t{ \n " +
		"\t\tperror(\"server: accept\"); \n " +
		"\t\texit(1); \n " +
        "\t\t} \n " +
"}\n" +

"int getfd(int R,int C,int P) \n" +
"{  \n" +
 	"\treturn ns[R][C][P]; \n" +
"} \n" +

"void assignsocklist() \n" +
"{ \n" 

]


file_footer = ["}"]

out.writelines(file_header + line +file_footer)
out.close()
            
