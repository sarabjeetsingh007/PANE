//PANE/router.ned
//Describes the connections within a router 
//Router distribution: 		5 InputBuffer each connected to respective ports of Client[0]. A new packet of data enter the router through InputBuffer.
//							4 simultaneously connected Clients
//							5 OutputBuffer each connected to respective ports of Client[3]. A packet of data exits the router through OutputBuffer.

package PANE;
module mod_router
{
    //@display("bgb=553.14,131.67");
    parameters:
        int numClients = 4 ;		//Represents the division of a Router
        @display("bgb=864.745,437.255");
    gates:
        input in[5] @loose;		//Message input gate 
        output out[5] @loose;		//Message output gate
        input Ack_in[5] @loose;		//Acknowledgement input gate
        output Ack_out[5] @loose;		//Acknowledgement output gate 

    submodules:
        inputbuff[5]: inputbuffer {
            @display("p=69.52,83.64125,c,65,80;i=block/queue");
        }
        client[numClients]: mod {
            parameters:
                @display("i=abstract/router,white;p=235.71625,193.3525,m,10,80");
        }
        outputbuff[5]: outputbuffer {
            @display("p=782.1,83.64125,c,65,80;i=block/queue");
        }
    connections:
        //		 Buffer-Router Connection
        for i=0..4 {
            in[i] --> inputbuff[i].in;
        }
        for i=0..4 {
            outputbuff[i].out --> out[i];
        }

        for i=0..4 {
            outputbuff[i].Ack_in <-- Ack_in[i];
        }
        for i=0..4 {
            Ack_out[i] <-- inputbuff[i].Ack_out;
        }

        //        Client-Buffer Connection
        for i=0..4 {
            inputbuff[i].out --> client[0].in[i];
        }
        for i=0..4 {
            client[numClients-1].out[i] --> outputbuff[i].in;
        }
        for i=0..4 {
            client[numClients-1].Ack_in[i] <-- outputbuff[i].Ack_out;
        }
        for i=0..4 {
            inputbuff[i].Ack_in <-- client[0].Ack_out[i];
        }

        //       Inter-Client Connections:
        for i=0..numClients-2 {
            client[i].out[0] --> client[i+1].in[0];
        }
        for i=0..numClients-2 {
            client[i].out[1] --> client[i+1].in[1];
        }
        for i=0..numClients-2 {
            client[i].out[2] --> client[i+1].in[2];
        }
        for i=0..numClients-2 {
            client[i].out[3] --> client[i+1].in[3];
        }
        for i=0..numClients-2 {
            client[i].out[4] --> client[i+1].in[4];
        }

        for i=0..numClients-2 {
            client[i].Ack_in[0] <-- client[i+1].Ack_out[0];
        }
        for i=0..numClients-2 {
            client[i].Ack_in[1] <-- client[i+1].Ack_out[1];
        }
        for i=0..numClients-2 {
            client[i].Ack_in[2] <-- client[i+1].Ack_out[2];
        }
        for i=0..numClients-2 {
            client[i].Ack_in[3] <-- client[i+1].Ack_out[3];
        }
        for i=0..numClients-2 {
            client[i].Ack_in[4] <-- client[i+1].Ack_out[4];
        }

        //Client-InputBuffer[5] Poll (Call to Core)
        for i=0..numClients-1 {
            client[i].poll --> inputbuff[4].poll[i];
        }
}
