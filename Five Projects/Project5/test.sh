#!/bin/zsh

g++ -std=c++11 -g -Wall -o test test.cpp
./test

g++ -std=c++11 -g -Wall -o calc calc.cpp
g++ -std=c++11 -g -Wall -o call call.cpp
./call < sample > test.out 
diff test.out sample.out


# valgrind --leak-check=full <PROGRAM_COMMAND>