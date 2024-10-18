#!/bin/bash

num=$1
echo -n $num

while [ $num -ne 1 ]
do
    if [ $(expr $num % 2) -eq 0 ]; then
        num=$(expr $num / 2)
    else
        num=$(expr $num * 3)
        num=$(expr $num + 1)
    fi
    echo -n " $num"
done
echo