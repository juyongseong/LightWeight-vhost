#/bin/sh
time=$1
size=$2
#echo "vm의 pid를 검색..."
./get_pid.sh
#setup.sh으로 이동..
echo "netperf측정중..."
#echo start >> /var/log/kern.log
./run_perf1.sh $time
#echo end >> /var/log/kern.log
echo "결과 출력중..."
sleep 5
#run_perf.sh's sleep time error
./get_res1.sh $time $size
echo "완료"
rm share/midFile/stat_*
#rm share/midFile/pidstat_*	#오류날 경우 제거 혹은 오류메세지를 알기위해서 중간 파일이 필요할경우 이라인 제거 가능
rm share/midFile/vmnetperf*
