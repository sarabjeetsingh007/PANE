make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump05; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.05/injection_rate = 0.07/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump07; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.07/injection_rate = 0.09/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump09; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.09/injection_rate = 0.11/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump11; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.11/injection_rate = 0.13/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump13; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.13/injection_rate = 0.15/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump15; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.15/injection_rate = 0.17/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump17; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.17/injection_rate = 0.19/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump19; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.19/injection_rate = 0.21/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump21; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.21/injection_rate = 0.23/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump23; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.23/injection_rate = 0.25/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump25; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.25/injection_rate = 0.27/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump27; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.27/injection_rate = 0.29/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump29; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.29/injection_rate = 0.31/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump31; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.31/injection_rate = 0.33/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump33; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.33/injection_rate = 0.35/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump35; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.35/injection_rate = 0.37/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump37; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.37/injection_rate = 0.39/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump39; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.39/injection_rate = 0.41/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump41; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.41/injection_rate = 0.43/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump43; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.43/injection_rate = 0.45/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump45; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.45/injection_rate = 0.47/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump47; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.47/injection_rate = 0.49/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump49; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/injection_rate = 0.49/injection_rate = 0.5/g'   ../booksim2-master/src/examples/bitrev
make -j80
make -j80 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump50; )"
./PANE -u Cmdenv -f omnetpp.ini


