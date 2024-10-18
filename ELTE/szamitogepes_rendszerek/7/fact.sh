#!/bin/bash

FAKT=1
for ((i=1; i<=$1; i++)); do
    FAKT=$((FAKT*$i))
done

echo $FAKT