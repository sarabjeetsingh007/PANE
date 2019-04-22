make
make sock
ulimit -n 4096
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump05; )"
./PANE -u Cmdenv -f omnetpp.ini > dump05

sed -i -e 's/injection_rate = 0.05/injection_rate = 0.07/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump07; )"
./PANE -u Cmdenv -f omnetpp.ini > dump07

sed -i -e 's/injection_rate = 0.07/injection_rate = 0.09/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump09; )"
./PANE -u Cmdenv -f omnetpp.ini > dump09

sed -i -e 's/injection_rate = 0.09/injection_rate = 0.11/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump11; )"
./PANE -u Cmdenv -f omnetpp.ini > dump11

sed -i -e 's/injection_rate = 0.11/injection_rate = 0.13/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump13; )"
./PANE -u Cmdenv -f omnetpp.ini > dump13

sed -i -e 's/injection_rate = 0.13/injection_rate = 0.15/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump15; )"
./PANE -u Cmdenv -f omnetpp.ini > dump15

sed -i -e 's/injection_rate = 0.15/injection_rate = 0.17/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump17; )"
./PANE -u Cmdenv -f omnetpp.ini > dump17

sed -i -e 's/injection_rate = 0.17/injection_rate = 0.19/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump19; )"
./PANE -u Cmdenv -f omnetpp.ini > dump19

sed -i -e 's/injection_rate = 0.19/injection_rate = 0.21/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump21; )"
./PANE -u Cmdenv -f omnetpp.ini > dump21

sed -i -e 's/injection_rate = 0.21/injection_rate = 0.23/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump23; )"
./PANE -u Cmdenv -f omnetpp.ini > dump23

sed -i -e 's/injection_rate = 0.23/injection_rate = 0.25/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump25; )"
./PANE -u Cmdenv -f omnetpp.ini > dump25

sed -i -e 's/injection_rate = 0.25/injection_rate = 0.27/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump27; )"
./PANE -u Cmdenv -f omnetpp.ini > dump27

sed -i -e 's/injection_rate = 0.27/injection_rate = 0.29/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump29; )"
./PANE -u Cmdenv -f omnetpp.ini > dump29

sed -i -e 's/injection_rate = 0.29/injection_rate = 0.31/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump31; )"
./PANE -u Cmdenv -f omnetpp.ini > dump31

sed -i -e 's/injection_rate = 0.31/injection_rate = 0.33/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump33; )"
./PANE -u Cmdenv -f omnetpp.ini > dump33

sed -i -e 's/injection_rate = 0.33/injection_rate = 0.35/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump35; )"
./PANE -u Cmdenv -f omnetpp.ini > dump35

sed -i -e 's/injection_rate = 0.35/injection_rate = 0.37/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump37; )"
./PANE -u Cmdenv -f omnetpp.ini > dump37

sed -i -e 's/injection_rate = 0.37/injection_rate = 0.39/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump39; )"
./PANE -u Cmdenv -f omnetpp.ini > dump39

sed -i -e 's/injection_rate = 0.39/injection_rate = 0.41/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump41; )"
./PANE -u Cmdenv -f omnetpp.ini > dump41

sed -i -e 's/injection_rate = 0.41/injection_rate = 0.43/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump43; )"
./PANE -u Cmdenv -f omnetpp.ini > dump43

sed -i -e 's/injection_rate = 0.43/injection_rate = 0.45/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump45; )"
./PANE -u Cmdenv -f omnetpp.ini > dump45

sed -i -e 's/injection_rate = 0.45/injection_rate = 0.47/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump47; )"
./PANE -u Cmdenv -f omnetpp.ini > dump47

sed -i -e 's/injection_rate = 0.47/injection_rate = 0.49/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump49; )"
./PANE -u Cmdenv -f omnetpp.ini > dump49

sed -i -e 's/injection_rate = 0.49/injection_rate = 0.5/g'   ../booksim2-master/src/examples/bitrev
make
make sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh > dump50; )"
./PANE -u Cmdenv -f omnetpp.ini > dump50

sed -i -e 's/injection_rate = 0.5/injection_rate = 0.05/g'   ../booksim2-master/src/examples/bitrev
