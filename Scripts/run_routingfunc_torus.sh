make -j4
make -j4 sock


sed -i -e 's/routing_function = dor/routing_function = dim_order/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpdim_order; )"
./PANE -u Cmdenv -f omnetpp.ini > dumpdim_order


sed -i -e 's/routing_function = dim_order/routing_function = min_adapt/g' ../booksim2-master/src/examples/bitrev
make -j4
make -j4 sock
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ./run.sh > dumpmin_adapt; )"
./PANE -u Cmdenv -f omnetpp.ini > dumpmin_adapt

sed -i -e 's/routing_function = min_adapt/routing_function = dor/g' ../booksim2-master/src/examples/bitrev

./GenerateReport.sh
