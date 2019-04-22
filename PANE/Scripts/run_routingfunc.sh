make -j4
make -j4 sock

gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpdor; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/routing_function = dor/routing_function = xy_yx/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpxy_yx; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/routing_function = xy_yx/routing_function = adaptive_xy_yx/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpadaptive_xy_yx; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/routing_function = adaptive_xy_yx/routing_function = romm/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpromm; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/routing_function = romm/routing_function = planar_adapt/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpplanar_adapt; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/routing_function = planar_adapt/routing_function = min_adapt/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpmin_adapt; )"
./PANE -u Cmdenv -f omnetpp.ini

sed -i -e 's/routing_function = min_adapt/routing_function = dor/g' ../booksim2-master/src/examples/bitrev
