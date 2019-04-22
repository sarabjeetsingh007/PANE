cd ../

export PATH=$PATH:/home/sarab/Documents/Simulators/omnetpp-5.1/bin

sed -i "/traffic = / c traffic = bitrev;" ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump/dump_traffic:bitrev; )"
./PANE -u Cmdenv -f omnetpp.ini

