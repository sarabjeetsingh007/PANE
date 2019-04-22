for file in *
do
	mkdir $file"_1"
	mv $file $file"_1"
	cd $file"_1"
	IFS=$'\n'       
	count=0
	for line in $(cat < $file)
	do
		let count++
		if [ $count -gt 9 ]
		then
			first=$(echo $line | awk '{print $1}')
			echo $line | awk '{print $2}' >>$first
		fi
	done
	rm $file
	cd ../ 
done
rm -r split.sh_1

