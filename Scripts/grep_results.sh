all_keywords="sim_seconds sim_ticks system.mem_ctrls0.readReqs system.mem_ctrls0.writeReqs system.mem_ctrls0.bytesReadDRAM system.mem_ctrls0.bytesWritten system.mem_ctrls0.avgMemAccLat system.mem_ctrls0.avgRdQLen system.mem_ctrls0.avgWrQLen system.mem_ctrls0.totGap system.mem_ctrls0.bytesPerActivate::mean system.mem_ctrls0.rdPerTurnAround::mean system.mem_ctrls0.wrPerTurnAround::mean system.mem_ctrls0.readRowHits system.mem_ctrls0.writeRowHits system.mem_ctrls0_0.memoryStateTime::IDLE system.mem_ctrls0_0.memoryStateTime::REF system.mem_ctrls0_0.memoryStateTime::SREF system.mem_ctrls0_0.memoryStateTime::PRE_PDN system.mem_ctrls0_0.memoryStateTime::ACT system.mem_ctrls0_0.memoryStateTime::ACT_PDN system.mem_ctrls0_1.memoryStateTime::IDLE system.mem_ctrls0_1.memoryStateTime::REF system.mem_ctrls0_1.memoryStateTime::SREF system.mem_ctrls0_1.memoryStateTime::PRE_PDN system.mem_ctrls0_1.memoryStateTime::ACT system.mem_ctrls0_1.memoryStateTime::ACT_PDN system.mem_ctrls1.readReqs system.mem_ctrls1.writeReqs system.mem_ctrls1.bytesReadDRAM system.mem_ctrls1.bytesWritten system.mem_ctrls1.avgMemAccLat system.mem_ctrls1.avgRdQLen system.mem_ctrls1.avgWrQLen system.mem_ctrls1.totGap system.mem_ctrls1.bytesPerActivate::mean system.mem_ctrls1.rdPerTurnAround::mean system.mem_ctrls1.wrPerTurnAround::mean system.mem_ctrls1.readRowHits system.mem_ctrls1.writeRowHits system.mem_ctrls1_0.memoryStateTime::IDLE system.mem_ctrls1_0.memoryStateTime::REF system.mem_ctrls1_0.memoryStateTime::SREF system.mem_ctrls1_0.memoryStateTime::PRE_PDN system.mem_ctrls1_0.memoryStateTime::ACT system.mem_ctrls1_0.memoryStateTime::ACT_PDN system.mem_ctrls1_1.memoryStateTime::IDLE system.mem_ctrls1_1.memoryStateTime::REF system.mem_ctrls1_1.memoryStateTime::SREF system.mem_ctrls1_1.memoryStateTime::PRE_PDN system.mem_ctrls1_1.memoryStateTime::ACT system.mem_ctrls1_1.memoryStateTime::ACT_PDN"
num_keywords=$(wc -w <<< "$all_keywords")
echo "Results" > Result.csv
echo "Failed LOG:" >failed
for keyword in $all_keywords
do 
	printf '\n\n\n'$keyword >> Result.csv
	printf '\nRAM,Mapping,' >> Result.csv
	cd Output/DDR/gem5_RoCoRaBaCh/
	for file in m5out_*
	do
		printf $file','  >>../../../Result.csv
	done
	cd ../../../

	cd Output
	for ram in *
	do
		cd $ram
		for mapping in *
		do
			cd $mapping
			exists=`ls -1 m5out_* 2>/dev/null | wc -l`
			if [ $exists != 0 ]
			then
				printf '\n'$ram','$mapping',' >>../../../Result.csv
				for app in m5out_*
				do 
					cd $app
					count=$(grep -c -w "End Simulation Statistics" stats.txt)
					if [ $count == 3 ]
					then
						if [ $(grep -c -w $keyword stats.txt) == 3 ]
						then
							nums=$(awk '/'$keyword'/ {print $2}' stats.txt)
							snums=$(echo $nums | awk '{print $2}')
						else
							nums=$(awk '/'$keyword'/ {print $2}' stats.txt)
							snums=$(echo $nums | awk '{print $1}')
						fi
						printf $snums','  >>../../../../Result.csv
					else
						printf '0,'  >>../../../../Result.csv
						cd ../../../../
						echo $keyword':'$ram"->"$mapping"->"$app" failed"  >>failed
						cd Output/$ram/$mapping/$app	
					fi
					cd ../
				done
			else
				cd ../../../
				echo $keyword':'$ram"->"$mapping"-> no applications(m5out_*)"  >>failed
				cd Output/$ram/$mapping/
			fi
			cd ../
		done
		cd ../
	done
	cd ../
done
#all_keywords=""
numfail=$(wc -l < failed)
if [ $numfail == 1 ]
then
	rm failed
fi
