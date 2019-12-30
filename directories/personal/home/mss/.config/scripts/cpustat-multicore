#!/mss/bin/sh
for core in $(grep cpu[[:digit:]] /proc/stat | awk '{gsub("cpu",""); print $1}')
do 
 s1_pre=$(grep cpu${core} /proc/stat)
 s1_total=$(($(echo $s1_pre | awk '{gsub(" ","+"); gsub("'cpu${core}'","0"); print}')))
 s1_col4=$(echo $s1_pre | awk '{print $5}')

 sleep 0.5

 s2_pre=$(grep cpu${core} /proc/stat)
 s2_total=$(($(echo $s2_pre | awk '{gsub(" ","+"); gsub("'cpu${core}'","0"); print}')))
 s2_col4=$(echo $s2_pre | awk '{print $5}')

 delta=$((${s2_total} - ${s1_total}))
 idle=$((${s2_col4} - ${s1_col4}))
 used=$((${delta} - ${idle}))
 perc=$(( 100 * ${used} / ${delta}))

 temps=$(sensors coretemp-isa-0000 \
          | grep Core\ ${core} \
          | awk '{gsub("+",""); gsub("°C",""); print $3"c"}')

 if [ -z "${temps}" ]
  then echo "${perc}%" > /tmp/cpu${core}.tmp
  else echo "${perc}%(${temps}) " > /tmp/cpu${core}.tmp
 fi
done

results=$(for file in /tmp/cpu[[:digit:]].tmp; do cat $file; done)
echo $(printf "%s \n" $results)
