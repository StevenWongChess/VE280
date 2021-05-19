#!/bin/zsh

g++ -std=c++11 -Wall -o p4 game.cpp quarto.cpp exceptions.cpp piece.cpp pool.cpp square.cpp board.cpp player.cpp
# g++ -std=c++11 -Wall -o p4 game.cpp quarto.cpp piece.cpp pool.cpp square.cpp board.cpp exceptions.cpp
./p4 m m 10

