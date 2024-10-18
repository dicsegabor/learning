#!/bin/bash

cat $1 | sed 's/[^0-9]/ /g' | tr "\n" ' ' | tr -s ' ' | sed 's/ //'
echo ;