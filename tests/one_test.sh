#!/bin/bash
cd "${0%/*}"

if [ $# -eq 0 ]
  then
    echo "No file path supplied"
    exit 1
fi

echo "Compiling tests..."
g++ -g -std=c++17 -Wall ../src/*/*.cc -pthread $1 -lgtest -lgtest_main -o test1.out

echo "Running tests..."
./test1.out
rm test1.out
