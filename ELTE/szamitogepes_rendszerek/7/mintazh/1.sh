#!/bin/sh

INPUT_DIR=$1
if [ ! -d "$INPUT_DIR" ]; then
    mkdir $INPUT_DIR

fi

cp ~/.bash_profile ./$INPUT_DIR
NUM=`grep -x -c ".* Fradi .*" ./$INPUT_DIR/.bash_profile`

echo $NUM"-szor fordul elő a Fradi szó"