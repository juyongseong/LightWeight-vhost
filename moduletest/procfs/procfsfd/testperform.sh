#!/bin/bash
i=0

while [ $i -lt 7 ]
do
	timeout 5s ./testRead &
	timeout 5s ./testRead &
	timeout 5s ./testEnqueue 2&
	timeout 5s ./testDequeue &
	((i++))
done

