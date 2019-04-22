make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump1; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/packet_size = 1/packet_size = 3/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump3; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/packet_size = 3/packet_size = 4/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump4; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/packet_size = 4/packet_size = 5/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump5; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/packet_size = 5/packet_size = 2/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dump2; )"
./PANE -u Cmdenv -f omnetpp.ini


