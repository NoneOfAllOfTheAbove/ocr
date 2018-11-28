#!/bin/bash

COUNTER=0
while [ $COUNTER -lt 10 ]; do
	if [ $COUNTER == 0 ]; then
		echo tools 0
	else
		echo tools 1
	fi
	let COUNTER=COUNTER+1
done
