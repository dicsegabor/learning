#!/bin/bash -e

echo -- Building project
cmake --build ./build
echo -- Running project
./build/chess
