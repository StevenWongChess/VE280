#!/bin/bash

# g++ -std=c++11 -Wall -o main main.cpp
# ./main
# valgrind --leak-check=full ./main
g++ -std=c++11 -Wall -o test test.cpp
# valgrind --leak-check=full ./test
./test
