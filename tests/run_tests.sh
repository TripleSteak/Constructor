#!/bin/bash
cd "${0%/*}"

if [ -f "tests.out" ]; then
    rm tests.out
fi

echo "Compiling tests..."
# g++ -g -std=c++17 -Wall ../src/*/*.cc -pthread */*.cc -lgtest -lgtest_main -o tests.out
make

echo "Running tests..."
./tests.out
