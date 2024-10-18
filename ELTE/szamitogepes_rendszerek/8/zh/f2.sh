#!/bin/bash

hour=$(date +%H)
minute=$(date +%M)

if [ $hour -lt 8 ]; then
    echo még nem kezdődött el a tanítás
elif [ $hour -gt 15 ]; then
    echo vége van mára a tanításnak
elif [ $minute -lt 45 ]; then
    echo tanóra van
else
    echo szünet van
fi
