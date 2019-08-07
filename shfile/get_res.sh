#!/bin/sh
#share/resultFile/$(date +%Y%m%d%H%M%S).txt에 저장
date=$(date +%Y%m%d%H%M%S)
echo "@@$(date +%Y)년   $(date +%m)월 $(date +%d)일 $(date +%H) 시  $(date +%M) 분  $(date +%S) 초에 출력된 결과입니다." >> share/resultFile/$date.txt

echo "@time : $1, size : $2" >> share/resultFile/$date.txt


echo '@@@@@@vm@@@@@@' >> share/resultFile/$date.txt
echo '@@@@@@vm@@@@@@' >> share/resultFile/$date.txt

for i in 1 2 3 4 5 6
do
      echo "@vm$i pidstat" >> share/resultFile/$date.txt
      cat share/midFile/pidstat_vm$i.txt >> share/resultFile/$date.txt
done

echo '@@@@@@vhost@@@@@@' >> share/resultFile/$date.txt
echo '@@@@@@vhost@@@@@@' >> share/resultFile/$date.txt

for i in 1 2 3 4 5 6
do
        echo "@vm$i vhost pidstat" >> share/resultFile/$date.txt
        cat share/midFile/pidstat_vhost$i.txt >> share/resultFile/$date.txt
done

echo '@@@@@@netperf@@@@@@' >> share/resultFile/$date.txt
echo '@@@@@@netperf@@@@@@' >> share/resultFile/$date.txt

for i in 1 2 3 4 5 6
do
        echo "@vm$i netperf" >> share/resultFile/$date.txt
        cat share/midFile/vmnetperf$i.txt >> share/resultFile/$date.txt
done

echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Summary@@@@@@@@@@@@@@@@@@@@@@@@@@@@' >> share/resultFile/$date.txt
echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Summary@@@@@@@@@@@@@@@@@@@@@@@@@@@@' >> share/resultFile/$date.txt
echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Summary@@@@@@@@@@@@@@@@@@@@@@@@@@@@' >> share/resultFile/$date.txt
echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Summary@@@@@@@@@@@@@@@@@@@@@@@@@@@@' >> share/resultFile/$date.txt

echo "@@$(date +%Y)년   $(date +%m)월 $(date +%d)일 $(date +%H) 시  $(date +%M) 분  $(date +%S) 초에 출력된 결과입니다." >> share/resultFile/$date.txt
echo "@time : $1, size : $2" >> share/resultFile/$date.txt


echo '@@@@@@vm@@@@@@' >> share/resultFile/$date.txt
echo '@@@@@@vm@@@@@@' >> share/resultFile/$date.txt

for i in 1 2 3 4 5 6
do
	echo "@vm$i pidstat" >> share/resultFile/$date.txt
	cat share/midFile/pidstat_vm$i.txt | grep Average | cut -d'-' -f1>> share/resultFile/$date.txt
done

echo '@@@@@@vhost@@@@@@' >> share/resultFile/$date.txt
echo '@@@@@@vhost@@@@@@' >> share/resultFile/$date.txt

for i in 1 2 3 4 5 6
do
        echo "@vm$i vhost pidstat" >> share/resultFile/$date.txt
        cat share/midFile/pidstat_vhost$i.txt | grep Average >> share/resultFile/$date.txt
done

echo '@@@@@@netperf@@@@@@' >> share/resultFile/$date.txt
echo '@@@@@@netperf@@@@@@' >> share/resultFile/$date.txt

for i in 1 2 3 4 5 6
do
        echo "@vm$i netperf" >> share/resultFile/$date.txt
        cat share/midFile/vmnetperf$i.txt | grep $2 >> share/resultFile/$date.txt
done

exit 0
