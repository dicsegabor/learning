#!/bin/bash

# If directory doesn't exist
if [ ! -d $1 ]; then
    mkdir $1
fi
cp ~/.profile ./$1

# Get the words with grep, count the lines in the output with wc -l
num=$(grep Fradi ./$1/.profile | wc -l)
echo $num-szor fordul elő a Fradi szó
