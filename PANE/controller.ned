//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package PANE;

simple controller_src
{
    parameters: 
        int numRouters = 16;
    gates:
        output out[numRouters] @loose ;		//Gate for sending new packets of data into the network
        input Ack_in[numRouters] @loose ;		//Gate for receiving acknowledgements of packets
        input countret[numRouters];		//Gate for monitoring retired packets	
}
