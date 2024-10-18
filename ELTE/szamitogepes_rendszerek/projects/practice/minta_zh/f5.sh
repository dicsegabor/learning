#!/bin/bash

counter=0
for i in "$@"
do
    if [ $i -eq 0 ]; then
        counter=$(expr $counter + 1)
    fi
done
echo $counter db 0 szerepel a paraméterek között
