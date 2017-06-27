#Traffic Pattern
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpneighbor; )"
./PANE -u Cmdenv -f omnetpp.ini >dumpneighbor

sed -i -e 's/traffic = neighbor/traffic = uniform/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpuniform; )"
./PANE -u Cmdenv -f omnetpp.ini >dumpuniform

sed -i -e 's/traffic = uniform/traffic = transpose/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumptranspose; )"
./PANE -u Cmdenv -f omnetpp.ini >dumptranspose

sed -i -e 's/traffic = transpose/traffic = tornado/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumptornado; )"
./PANE -u Cmdenv -f omnetpp.ini >dumptornado

sed -i -e 's/traffic = tornado/traffic = shuffle/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpshuffle; )"
./PANE -u Cmdenv -f omnetpp.ini >dumpshuffle

sed -i -e 's/traffic = shuffle/traffic = bitrev/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpbitrev; )"
./PANE -u Cmdenv -f omnetpp.ini >dumpbitrev

sed -i -e 's/traffic = bitrev/traffic = bitcomp/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpbitcomp; )"
./PANE -u Cmdenv -f omnetpp.ini >dumpbitcomp

sed -i -e 's/traffic = bitcomp/traffic = uniform/g' ../booksim2-master/src/examples/bitrev

#Routing Function

make
make sock

gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpdor; )"
./PANE -u Cmdenv -f omnetpp.ini >dumpdor

sed -i -e 's/routing_function = dor/routing_function = xy_yx/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpxy_yx; )"
./PANE -u Cmdenv -f omnetpp.ini >dumpxy_yx

sed -i -e 's/routing_function = xy_yx/routing_function = adaptive_xy_yx/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpadaptive_xy_yx; )"
./PANE -u Cmdenv -f omnetpp.ini >dumpadaptive_xy_yx

sed -i -e 's/routing_function = adaptive_xy_yx/routing_function = romm/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpromm; )"
./PANE -u Cmdenv -f omnetpp.ini >dumpromm

sed -i -e 's/routing_function = romm/routing_function = planar_adapt/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpplanar_adapt; )"
./PANE -u Cmdenv -f omnetpp.ini >dumpplanar_adapt

sed -i -e 's/routing_function = planar_adapt/routing_function = min_adapt/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpmin_adapt; )"
./PANE -u Cmdenv -f omnetpp.ini >dumpmin_adapt

sed -i -e 's/routing_function = min_adapt/routing_function = dor/g' ../booksim2-master/src/examples/bitrev

#Packet Size

make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump1; )"
./PANE -u Cmdenv -f omnetpp.ini >dump1

sed -i -e 's/packet_size = 1/packet_size = 2/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump2; )"
./PANE -u Cmdenv -f omnetpp.ini >dump2

sed -i -e 's/packet_size = 2/packet_size = 3/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump3; )"
./PANE -u Cmdenv -f omnetpp.ini >dump3

sed -i -e 's/packet_size = 3/packet_size = 4/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump4; )"
./PANE -u Cmdenv -f omnetpp.ini >dump4

sed -i -e 's/packet_size = 4/packet_size = 5/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump5; )"
./PANE -u Cmdenv -f omnetpp.ini >dump5

sed -i -e 's/packet_size = 5/packet_size = 1/g' ../booksim2-master/src/examples/bitrev

#Buffer Organization

sed -i -e 's/num_vcs = 4/num_vcs = 1/g' ../booksim2-master/src/examples/bitrev
sed -i -e 's/vc_buf_size = 4/vc_buf_size = 32/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump1X32; )"
./PANE -u Cmdenv -f omnetpp.ini >dump1X32

sed -i -e 's/num_vcs = 1/num_vcs = 2/g' ../booksim2-master/src/examples/bitrev
sed -i -e 's/vc_buf_size = 32/vc_buf_size = 16/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump2X16; )"
./PANE -u Cmdenv -f omnetpp.ini >dump2X16

sed -i -e 's/num_vcs = 2/num_vcs = 4/g' ../booksim2-master/src/examples/bitrev
sed -i -e 's/vc_buf_size = 16/vc_buf_size = 8/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump4X8; )"
./PANE -u Cmdenv -f omnetpp.ini >dump4X8

sed -i -e 's/num_vcs = 4/num_vcs = 8/g' ../booksim2-master/src/examples/bitrev
sed -i -e 's/vc_buf_size = 8/vc_buf_size = 4/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump8X4; )"
./PANE -u Cmdenv -f omnetpp.ini >dump8X4

sed -i -e 's/num_vcs = 8/num_vcs = 16/g' ../booksim2-master/src/examples/bitrev
sed -i -e 's/vc_buf_size = 4/vc_buf_size = 2/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump16X2; )"
./PANE -u Cmdenv -f omnetpp.ini >dump16X2

sed -i -e 's/num_vcs = 16/num_vcs = 32/g' ../booksim2-master/src/examples/bitrev
sed -i -e 's/vc_buf_size = 2/vc_buf_size = 1/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump32X1; )"
./PANE -u Cmdenv -f omnetpp.ini >dump32X1

sed -i -e 's/num_vcs = 32/num_vcs = 4/g' ../booksim2-master/src/examples/bitrev
sed -i -e 's/vc_buf_size = 1/vc_buf_size = 4/g' ../booksim2-master/src/examples/bitrev


