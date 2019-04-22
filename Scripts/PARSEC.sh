make
make sock
ulimit -n 4096
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpblackscholes_64c_simsmall; )"
./PANE -u Cmdenv -f omnetpp.ini > dumpblackscholes_64c_simsmall

sed -i -e 's/blackscholes_64c_simsmall/bodytrack_64c_simlarge/g'   ../booksim2-master/src/examples/mesh88_lat_blackscholes
make
make sock
ulimit -n 4096
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpbodytrack_64c_simlarge; )"
./PANE -u Cmdenv -f omnetpp.ini > dumpbodytrack_64c_simlarge

sed -i -e 's/bodytrack_64c_simlarge/canneal_64c_simmedium/g'   ../booksim2-master/src/examples/mesh88_lat_blackscholes
make
make sock
ulimit -n 4096
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpcanneal_64c_simmedium; )"
./PANE -u Cmdenv -f omnetpp.ini > dumpcanneal_64c_simmedium

sed -i -e 's/canneal_64c_simmedium/dedup_64c_simmedium/g'   ../booksim2-master/src/examples/mesh88_lat_blackscholes
make
make sock
ulimit -n 4096
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpdedup_64c_simmedium; )"
./PANE -u Cmdenv -f omnetpp.ini > dumpdedup_64c_simmedium

sed -i -e 's/dedup_64c_simmedium/ferret_64c_simmedium/g'   ../booksim2-master/src/examples/mesh88_lat_blackscholes
make
make sock
ulimit -n 4096
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpferret_64c_simmedium; )"
./PANE -u Cmdenv -f omnetpp.ini > dumpferret_64c_simmedium

sed -i -e 's/ferret_64c_simmedium/fluidanimate_64c_simsmall/g'   ../booksim2-master/src/examples/mesh88_lat_blackscholes
make
make sock
ulimit -n 4096
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpfluidanimate_64c_simsmall; )"
./PANE -u Cmdenv -f omnetpp.ini > dumpfluidanimate_64c_simsmall

sed -i -e 's/fluidanimate_64c_simsmall/swaptions_64c_simlarge/g'   ../booksim2-master/src/examples/mesh88_lat_blackscholes
make
make sock
ulimit -n 4096
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpswaptions_64c_simlarge; )"
./PANE -u Cmdenv -f omnetpp.ini > dumpswaptions_64c_simlarge

sed -i -e 's/swaptions_64c_simlarge/vips_64c_simmedium/g'   ../booksim2-master/src/examples/mesh88_lat_blackscholes
make
make sock
ulimit -n 4096
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpvips_64c_simmedium; )"
./PANE -u Cmdenv -f omnetpp.ini > dumpvips_64c_simmedium

sed -i -e 's/vips_64c_simmedium/x264_64c_simsmall/g'   ../booksim2-master/src/examples/mesh88_lat_blackscholes
make
make sock
ulimit -n 4096
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096; ./run.sh > dumpx264_64c_simsmall; )"
./PANE -u Cmdenv -f omnetpp.ini > dumpx264_64c_simsmall

sed -i -e 's/x264_64c_simsmall/blackscholes_64c_simsmall/g'   ../booksim2-master/src/examples/mesh88_lat_blackscholes

#./GenerateReport.sh

