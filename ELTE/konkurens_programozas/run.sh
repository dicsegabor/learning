#!/bin/bash

# Check if an argument is provided
if [ $# -eq 0 ]; then
  echo "Error: Please provide a program name as an argument."
  exit 1
fi

# Store the program name from the argument
program_name="$1"

# Compile the program
javac "$program_name.java"

# Check if compilation was successful
if [ $? -ne 0 ]; then
  echo "Error: Compilation failed."
  exit 1
fi

# Run the program
java "$program_name"
