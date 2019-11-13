#!/bin/sh
vmNum=1
time=$1
size=$2
port=10001
argc=$#
#초기화
cat /dev/null > share/midFile/vmnetperf$vmNum.txt

netperf -H 10.0.0.2 port $port -l $time -- -m $size >> share/midFile/vmnetperf$vmNum.txt
