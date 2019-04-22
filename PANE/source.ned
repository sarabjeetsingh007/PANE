

package PANE;

simple mod_src
{
    parameters:
        @display("i=block/routing");
    gates:
        output out @loose ;		//Message output gate 
        input Ack_in @loose ;		//Acknowledgement input gate 
        output out_controller @loose ;		//Acknowledgement output gate 
        input in_controller @loose ;		//Message input gate
}
