#cd ../PANE
#export PATH=$PATH:$HOME/omnetpp-5.1/bin
export PATH=$PATH:/home/sarab/Documents/Simulators/omnetpp-5.1/bin
make -C ../PANE/
#make
#make sock
make sock -C ../PANE/
ulimit -n 4096
gnome-terminal -x sh -c "(sleep 1; cd ../booksim2-master/src/; ulimit -n 4096;   ./run.sh>dump/singleRunStats; )"
./PANE -u Cmdenv -f omnetpp.ini>dump/singleRunStats
make sock -C ../PANE/
