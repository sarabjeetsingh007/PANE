for file in *
do
	mkdir $file"_1"
	mv $file $file"_1"
	cd $file"_1"
	space="\ "
	IFS=$'\n' 
	split -l 1000 $file
	rm $file      
	for f in *
	do
		for line in $(cat < $f)
		do
			first=$(echo $line | awk '{print $1}')
			eval "v"$first=\$"v"$first$space$(echo $line | awk '{print $2}')
		done
		rm $f
		for word in $(compgen -A variable | grep v)
		do
			eval echo \$$word | tr '\n' ' '>>$word
			unset $word
		done
	done
	rm -r vcommand
	rm -r vExiting
	rm -r vgem5
	rm -r vGlobal
	cd ../ 
done

rm -r split_thread.sh_1
