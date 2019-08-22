#!/bin/sh
vmNum=1
time=$1
size=$2
port=10001
netperf -H 10.0.0.2 port $port -l $time -- -m $size & netperf -H 10.0.0.2 port $port -l $time -- -m $size & netperf -H 10.0.0.2 port $port -l $time -- -m $size & netperf -H 10.0.0.2 port $port -l $time -- -m $size
