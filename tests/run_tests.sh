#!/bin/bash

echo "Compiling tests..."
g++ -pthread */*.cc -lgtest -lgtest_main -o tests.out

echo "Running tests..."
./tests.out
rm tests.out