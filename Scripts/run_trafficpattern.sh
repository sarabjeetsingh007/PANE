#Traffic Pattern
sed -i -e 's/traffic =.*/traffic = neighbor;/g' ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpneighbor; )"
./PANE -u Cmdenv -f omnetpp.ini  >dumpneighbor

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

sed -i -e 's/traffic = bitcomp/traffic = neighbor/g' ../booksim2-master/src/examples/bitrev
make sock

./GenerateReport.sh

