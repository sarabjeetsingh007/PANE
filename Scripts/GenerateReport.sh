echo "Results"$'\n\n' >Result
for file in dump*
do
	echo $file ":">>Result
#	grep "\bTotal Number of packets generated\b" $file >>Result
#	grep "\bTotal Number of packets retired\b" $file >>Result
#	grep "\bLink Activity Factor\b" $file >> Result
	for f in ../booksim2-master/src/dump*
	do
		if [ ../booksim2-master/src/$file == $f ]
		then
			grep "\bOverall maximum packet latency\b" $f >> Result
			grep "\bOverall average packet latency\b" $f >> Result
			rm $f
		fi
	done
	rm $file
	printf '\n'>>Result
done
