#!/bin/sh
#count는 vm$count을 순회해 가면서 텍스트를 저장, time은 실험하는 시간
count=0
time=$1
#작업할 pid를 공개
#echo '--- 각 vm의 pid ---'
#cat share/midFile/pid.txt
#echo '#위가 공백일경우 get_pid.txt의 -f3를 -f2로 바꿔야합니다'
#setup.sh으로 이동..
echo '--- 각 vm의 vhost pid ---'

cat share/midFile/pid.txt | \
while read line
do
count=$(($count+1))
	vhost=`pgrep vhost-$line`
	echo $vhost

	/usr/src/linux-5.1.5/tools/perf/perf stat -p $line -d -o share/midFile/stat_vm$count.txt sleep $time &
	/usr/src/linux-5.1.5/tools/perf/perf stat -p $vhost -d -o share/midFile/stat_vhost$count.txt sleep $time &
done
#echo '위가 에러일경우 perf에러, '$(uname -r) ' = 4.15.0-generic 같은지 확인'
sleep $time
exit 0
