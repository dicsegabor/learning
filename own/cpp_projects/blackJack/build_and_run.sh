#!/bin/bash -e

echo -- Building project
cmake --build ./bin
echo -- Running project
./bin/Blackjack