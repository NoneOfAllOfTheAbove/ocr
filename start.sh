#!/bin/bash

COUNTER=0
while [ $COUNTER -lt 30 ]; do
	echo $COUNTER
    ./bin/Tools 1
	let COUNTER=COUNTER+1
done
