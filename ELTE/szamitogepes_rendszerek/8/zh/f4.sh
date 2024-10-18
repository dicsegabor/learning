#!/bin/bash

file=$1
if [ -x $file ]; then
    echo $(cat $file | grep -c "#")
else
    ls -l $file | cut -d ' ' -f 1
fi