#!/bin/bash

echo "Compiling tests..."
g++ -g -std=c++17 -Wall ../src/*/*.cc -pthread */*.cc -lgtest -lgtest_main -o tests.out

echo "Running tests..."
./tests.out
rm tests.out