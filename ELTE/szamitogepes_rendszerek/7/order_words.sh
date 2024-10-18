#!/bin/bash

#tmpfile=$(mktemp /tmp/order_words.XXXXX)

set line
while [ $line == "vége" ]; do
    read line
    echo $line >$tmpfile
done

cat $tmpfile | sort