declare -i var1
declare -i var2

mkdir ./Results
mkdir ./Results/Sweep_injection_rate

mkdir ./Results/Sweep_injection_rate/pk1
mkdir ./Results/Sweep_injection_rate/pk2
mkdir ./Results/Sweep_injection_rate/pk3
mkdir ./Results/Sweep_injection_rate/pk4
mkdir ./Results/Sweep_injection_rate/pk5
mkdir ./Results/Sweep_injection_rate/pk6
mkdir ./Results/Sweep_injection_rate/pk7
mkdir ./Results/Sweep_injection_rate/pk8
mkdir ./Results/Sweep_injection_rate/pk9
mkdir ./Results/Sweep_injection_rate/pk10

echo pk1
echo Booksiming 10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk1/10
echo 1 down!
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk1/10
echo 2 down!
var2=10;
for((var1=20; var1<=200; var1=var1+10))
do
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	echo another seddown!
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	var2=var2+10
	echo Booksiming $var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk1/$var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk1/$var1
done
echo Reseting the injection rate to 0.010
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
echo Setting packet size to 2
sed -i -e 's/packet_size=1;/packet_size=2;/g' ./examples/mesh88_lat
sed -i -e 's/packet_size=1;/packet_size=2;/g' ./examples/mesh88_lat

echo pk2
echo Booksiming 10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk2/10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk2/10
var2=10;
for((var1=20; var1<=200; var1=var1+10))
do
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	var2=var2+10
	echo Booksiming $var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk2/$var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk2/$var1
done
echo Reseting the injection rate to 0.010
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
echo Setting packet size to 3
sed -i -e 's/packet_size=2;/packet_size=3;/g' ./examples/mesh88_lat
sed -i -e 's/packet_size=2;/packet_size=3;/g' ./examples/mesh88_lat

echo pk3
echo Booksiming 10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk3/10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk3/10
var2=10;
for((var1=20; var1<=200; var1=var1+10))
do
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	var2=var2+10
	echo Booksiming $var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk3/$var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk3/$var1
done
echo Reseting the injection rate to 0.010
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
echo Setting packet size to 4
sed -i -e 's/packet_size=3;/packet_size=4;/g' ./examples/mesh88_lat
sed -i -e 's/packet_size=3;/packet_size=4;/g' ./examples/mesh88_lat

echo pk4
echo Booksiming 10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk4/10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk4/10
var2=10;
for((var1=20; var1<=200; var1=var1+10))
do
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	var2=var2+10
	echo Booksiming $var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk4/$var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk4/$var1
done
echo Reseting the injection rate to 0.010
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
echo Setting packet size to 5
sed -i -e 's/packet_size=4;/packet_size=5;/g' ./examples/mesh88_lat
sed -i -e 's/packet_size=4;/packet_size=5;/g' ./examples/mesh88_lat

echo pk5
echo Booksiming 10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk5/10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk5/10
var2=10;
for((var1=20; var1<=200; var1=var1+10))
do
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	var2=var2+10
	echo Booksiming $var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk5/$var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk5/$var1
done
echo Reseting the injection rate to 0.010
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
echo Setting packet size to 6
sed -i -e 's/packet_size=5;/packet_size=6;/g' ./examples/mesh88_lat
sed -i -e 's/packet_size=5;/packet_size=6;/g' ./examples/mesh88_lat

echo pk6
echo Booksiming 10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk6/10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk6/10
var2=10;
for((var1=20; var1<=200; var1=var1+10))
do
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	var2=var2+10
	echo Booksiming $var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk6/$var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk6/$var1
done
echo Reseting the injection rate to 0.010
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
echo Setting packet size to 7
sed -i -e 's/packet_size=6;/packet_size=7;/g' ./examples/mesh88_lat
sed -i -e 's/packet_size=6;/packet_size=7;/g' ./examples/mesh88_lat

echo pk7
echo Booksiming 10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk7/10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk7/10
var2=10;
for((var1=20; var1<=200; var1=var1+10))
do
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	var2=var2+10
	echo Booksiming $var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk7/$var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk7/$var1
done
echo Reseting the injection rate to 0.010
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
echo Setting packet size to 8
sed -i -e 's/packet_size=7;/packet_size=8;/g' ./examples/mesh88_lat
sed -i -e 's/packet_size=7;/packet_size=8;/g' ./examples/mesh88_lat


echo pk8
echo Booksiming 10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk8/10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk8/10
var2=10;
for((var1=20; var1<=200; var1=var1+10))
do
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	var2=var2+10
	echo Booksiming $var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk8/$var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk8/$var1
done
echo Reseting the injection rate to 0.010
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
echo Setting packet size to 9
sed -i -e 's/packet_size=8;/packet_size=9;/g' ./examples/mesh88_lat
sed -i -e 's/packet_size=8;/packet_size=9;/g' ./examples/mesh88_lat

echo pk9
echo Booksiming 10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk9/10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk9/10
var2=10;
for((var1=20; var1<=200; var1=var1+10))
do
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	var2=var2+10
	echo Booksiming $var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk9/$var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk9/$var1
done
echo Reseting the injection rate to 0.010
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
echo Setting packet size to 10
sed -i -e 's/packet_size=9;/packet_size=10;/g' ./examples/mesh88_lat
sed -i -e 's/packet_size=9;/packet_size=10;/g' ./examples/mesh88_lat

echo pk10
echo Booksiming 10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk10/10
./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk10/10
var2=10;
for((var1=20; var1<=200; var1=var1+10))
do
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	sed -i -e s/$var2/$var1/g ./examples/mesh88_lat
	var2=var2+10
	echo Booksiming $var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk10/$var1
	./booksim  ./examples/mesh88_lat > ./Results/Sweep_injection_rate/pk10/$var1
done
echo Reseting the injection rate to 0.010
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
sed -i -e 's/0.200/0.010/g' ./examples/mesh88_lat
echo Done with packet size sims..resetting the packet size to 1
sed -i -e 's/packet_size=10;/packet_size=1;/g' ./examples/mesh88_lat
sed -i -e 's/packet_size=10;/packet_size=1;/g' ./examples/mesh88_lat
echo TATA!
