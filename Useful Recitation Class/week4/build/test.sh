#!/bin/bash

# g++ -o main.o -c main.cpp 
# g++ -o odd.o -c odd.cpp
# g++ -o even.o -c even.cpp 
# g++ -o sum.o -c sum.cpp
# g++ -o prod.o -c prod.cpp
# gcc -o sum_large.o -c sum_large.c

# g++ -o main main.o even.o sum.o && ./main
# g++ -o main main.o even.o prod.o && ./main 
# g++ -o main main.o odd.o prod.o && ./main

# g++ -o main main.o odd.o even.o prod.o && ./main #wrong
# g++ -o main main.o odd.o sum.o prod.o && ./main #wrong
# g++ -o main main.o prod.o && ./main #wrong
# g++ -o main even.o prod.o && ./main #wrong
# g++ -o main main.o even.o sum_large.o && ./main #still work, but renaming





