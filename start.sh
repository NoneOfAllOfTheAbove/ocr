#!/bin/bash

COUNTER=0
while [ $COUNTER -lt 30 ]; do
	if [ $COUNTER == 0 ]; then
		./bin/Tools 0
	else
		./bin/Tools 1
	fi
	let COUNTER=COUNTER+1
done
