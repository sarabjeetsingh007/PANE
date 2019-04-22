make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpneighbor; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/traffic = neighbor/traffic = uniform/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpuniform; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/traffic = uniform/traffic = transpose/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumptranspose; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/traffic = transpose/traffic = tornado/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumptornado; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/traffic = tornado/traffic = shuffle/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpshuffle; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/traffic = shuffle/traffic = bitrev/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpbitrev; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/traffic = bitrev/traffic = bitcomp/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpbitcomp; )"
./PANE -u Cmdenv -f omnetpp.ini

