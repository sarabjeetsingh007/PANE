//PANE/network.ned
//Describes the outer level connections of the network
//Network distribution:		A single Controller responsible for managing the control of PANE simulation
//							User defined Routers and their respective Cores(Source & Sink)
package PANE;
network NoC
{
    parameters:
        int r = 0;	//right
        int l = 1;	//left
        int d = 2;	//down
        int u = 3;	//up
        int c = 4;	//core
        int numRouters @prompt("Number of routers") = default(16);
        @display("bgb=1012,797,white,grey30,0");
    submodules:
        controller_src: controller_src {
            @display("p=232,21");
        }
        src[numRouters]: mod_src {
            parameters:
                @display("i=block/departure,lightGreen;p=58,71,m,4,250,180;is=s");
        }
        router[numRouters]: mod_router {
            parameters:
                @display("i=device/server,dodgerBlue;p=139,120,m,4,250,180;is=l");
        }
        sink[numRouters]: mod_sink {
            parameters:
                @display("i=block/arrival,red;p=222,169,m,4,250,180;is=s");
        }
    connections:

	//Inter-Router Communication !!Go to network_ned_connections.py

       router[0].out[r] --> router[1].in[l];
        router[1].out[r] --> router[2].in[l];
        router[2].out[r] --> router[3].in[l];
        router[4].out[r] --> router[5].in[l];
        router[5].out[r] --> router[6].in[l];
        router[6].out[r] --> router[7].in[l];
        router[8].out[r] --> router[9].in[l];
        router[9].out[r] --> router[10].in[l];
        router[10].out[r] --> router[11].in[l];
        router[12].out[r] --> router[13].in[l];
        router[13].out[r] --> router[14].in[l];
        router[14].out[r] --> router[15].in[l];

        router[0].Ack_in[r] <-- router[1].Ack_out[l];
        router[1].Ack_in[r] <-- router[2].Ack_out[l];
        router[2].Ack_in[r] <-- router[3].Ack_out[l];
        router[4].Ack_in[r] <-- router[5].Ack_out[l];
        router[5].Ack_in[r] <-- router[6].Ack_out[l];
        router[6].Ack_in[r] <-- router[7].Ack_out[l];
        router[8].Ack_in[r] <-- router[9].Ack_out[l];
        router[9].Ack_in[r] <-- router[10].Ack_out[l];
        router[10].Ack_in[r] <-- router[11].Ack_out[l];
        router[12].Ack_in[r] <-- router[13].Ack_out[l];
        router[13].Ack_in[r] <-- router[14].Ack_out[l];
        router[14].Ack_in[r] <-- router[15].Ack_out[l];

        router[0].out[d] --> router[4].in[u];
        router[1].out[d] --> router[5].in[u];
        router[2].out[d] --> router[6].in[u];
        router[3].out[d] --> router[7].in[u];
        router[4].out[d] --> router[8].in[u];
        router[5].out[d] --> router[9].in[u];
        router[6].out[d] --> router[10].in[u];
        router[7].out[d] --> router[11].in[u];
        router[8].out[d] --> router[12].in[u];
        router[9].out[d] --> router[13].in[u];
        router[10].out[d] --> router[14].in[u];
        router[11].out[d] --> router[15].in[u];

        router[0].Ack_in[d] <-- router[4].Ack_out[u];
        router[1].Ack_in[d] <-- router[5].Ack_out[u];
        router[2].Ack_in[d] <-- router[6].Ack_out[u];
        router[3].Ack_in[d] <-- router[7].Ack_out[u];
        router[4].Ack_in[d] <-- router[8].Ack_out[u];
        router[5].Ack_in[d] <-- router[9].Ack_out[u];
        router[6].Ack_in[d] <-- router[10].Ack_out[u];
        router[7].Ack_in[d] <-- router[11].Ack_out[u];
        router[8].Ack_in[d] <-- router[12].Ack_out[u];
        router[9].Ack_in[d] <-- router[13].Ack_out[u];
        router[10].Ack_in[d] <-- router[14].Ack_out[u];
        router[11].Ack_in[d] <-- router[15].Ack_out[u];

        router[0].in[r] <-- router[1].out[l];
        router[1].in[r] <-- router[2].out[l];
        router[2].in[r] <-- router[3].out[l];
        router[4].in[r] <-- router[5].out[l];
        router[5].in[r] <-- router[6].out[l];
        router[6].in[r] <-- router[7].out[l];
        router[8].in[r] <-- router[9].out[l];
        router[9].in[r] <-- router[10].out[l];
        router[10].in[r] <-- router[11].out[l];
        router[12].in[r] <-- router[13].out[l];
        router[13].in[r] <-- router[14].out[l];
        router[14].in[r] <-- router[15].out[l];

        router[0].Ack_out[r] --> router[1].Ack_in[l];
        router[1].Ack_out[r] --> router[2].Ack_in[l];
        router[2].Ack_out[r] --> router[3].Ack_in[l];
        router[4].Ack_out[r] --> router[5].Ack_in[l];
        router[5].Ack_out[r] --> router[6].Ack_in[l];
        router[6].Ack_out[r] --> router[7].Ack_in[l];
        router[8].Ack_out[r] --> router[9].Ack_in[l];
        router[9].Ack_out[r] --> router[10].Ack_in[l];
        router[10].Ack_out[r] --> router[11].Ack_in[l];
        router[12].Ack_out[r] --> router[13].Ack_in[l];
        router[13].Ack_out[r] --> router[14].Ack_in[l];
        router[14].Ack_out[r] --> router[15].Ack_in[l];

        router[0].in[d] <-- router[4].out[u];
        router[1].in[d] <-- router[5].out[u];
        router[2].in[d] <-- router[6].out[u];
        router[3].in[d] <-- router[7].out[u];
        router[4].in[d] <-- router[8].out[u];
        router[5].in[d] <-- router[9].out[u];
        router[6].in[d] <-- router[10].out[u];
        router[7].in[d] <-- router[11].out[u];
        router[8].in[d] <-- router[12].out[u];
        router[9].in[d] <-- router[13].out[u];
        router[10].in[d] <-- router[14].out[u];
        router[11].in[d] <-- router[15].out[u];

        router[0].Ack_out[d] --> router[4].Ack_in[u];
        router[1].Ack_out[d] --> router[5].Ack_in[u];
        router[2].Ack_out[d] --> router[6].Ack_in[u];
        router[3].Ack_out[d] --> router[7].Ack_in[u];
        router[4].Ack_out[d] --> router[8].Ack_in[u];
        router[5].Ack_out[d] --> router[9].Ack_in[u];
        router[6].Ack_out[d] --> router[10].Ack_in[u];
        router[7].Ack_out[d] --> router[11].Ack_in[u];
        router[8].Ack_out[d] --> router[12].Ack_in[u];
        router[9].Ack_out[d] --> router[13].Ack_in[u];
        router[10].Ack_out[d] --> router[14].Ack_in[u];
        router[11].Ack_out[d] --> router[15].Ack_in[u];

        //Source-Router Communication
        for i=0..numRouters-1 {
            src[i].out --> { @display("ls=#F34141"); } --> router[i].in[c];
            src[i].Ack_in <-- { @display("ls=#F34141"); } <-- router[i].Ack_out[c];
        }
        //Sink-Router Communication
        for i=0..numRouters-1 {
            router[i].out[c] --> { @display("ls=#F28080"); } --> sink[i].in;
            router[i].Ack_in[c] <-- { @display("ls=#F28080"); } <-- sink[i].Ack_out;
        }

        //Src-Controller Communication
        for i=0..numRouters-1 {
            controller_src.Ack_in[i] <-- { @display("ls=#2C1CCE,0"); } <-- src[i].out_controller;
        }
        for i=0..numRouters-1 {
            controller_src.out[i] --> { @display("ls=#2C1CCE,0"); } --> src[i].in_controller;
        }

        //Sink-Controller CountReturn Communication
        for i=0..numRouters-1 {
            sink[i].countret --> { @display("ls=,0"); } --> controller_src.countret[i];
        }
}
