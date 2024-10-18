#!/bin/bash

sm=$1
for par in "$@"; do
    if [ $par -lt $sm ]; then
        sm=$par
    fi
done

echo $sm
