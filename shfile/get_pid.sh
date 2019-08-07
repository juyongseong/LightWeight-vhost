#!/bin/sh
#초기화
cat /dev/null > share/midFile/pid.txt
# 이렇게 할경우 이름이 vm(숫자)인 실행중인 vm의 프로세스 아이디를 전부 가져옴
ps -ef | grep -i vm$i' ' | grep qemu | cut -d" " -f2 >> share/midFile/pid.txt
#pid 값이 안나올경우 -f4, -f3을 수정

exit 0
