message Packet
{
//    char data[9];
    int pid;			//Sequential numbers. PID for a packet and its ACK is the same
    int hid;			//Identifies the PID of its head
    double delay;		//Total Time taken to travel from source to the sink. Reset delay when ACK is generated
    int packet_type;		//0 = Data, 1 = ACK, 4 = Poll
    int size;			//Size of the packet
};
