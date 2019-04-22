make -j4
make -j4 sock
ulimit -n 4096
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpneighbor; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/traffic = neighbor/traffic = uniform/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpuniform; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/traffic = uniform/traffic = transpose/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumptranspose; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/traffic = transpose/traffic = tornado/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumptornado; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/traffic = tornado/traffic = shuffle/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpshuffle; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/traffic = shuffle/traffic = bitrev/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpbitrev; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/traffic = bitrev/traffic = bitcomp/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpbitcomp; )"
./PANE -u Cmdenv -f omnetpp.ini

