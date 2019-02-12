#!/bin/bash
echo "Compiling..."
gcc $1 -o main
echo "Starting..."
./main
