#!/bin/bash

# g++ -std=c++11 -g -Wall -o test test.cpp
# valgrind --leak-check=full ./test

# g++ -std=c++11 -g -Wall -o calc calc.cpp
# ./calc < calc.txt 								# on MacOS
# valgrind --leak-check=full ./calc < calc.txt		# Valgrind on Linux

g++ -std=c++11 -g -Wall -o call call.cpp
valgrind --leak-check=full ./call < sample > test.out 
diff test.out sample.out

