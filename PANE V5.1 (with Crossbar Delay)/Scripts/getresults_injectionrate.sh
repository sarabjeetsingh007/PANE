echo $1 >temp.csv
#echo ","$(grep "dump" $1 |  awk '{print $1}' | awk '{print substr($1,5); }'|  sed -n -e 'H;${x;s/\n/,/g;s/^,//;p;}') >>temp.csv
echo "Power,"$(grep "Average Packet Latency" $1 |  awk '{print $6}' |  sed -n -e 'H;${x;s/\n/,/g;s/^,//;p;}') >>temp.csv
