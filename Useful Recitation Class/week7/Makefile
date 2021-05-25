all: 2048

2048: 2048.o input.o direction.o point.o tile.o grid.o game.o
	g++ -std=c++11 -o 2048 2048.o input.o direction.o point.o tile.o grid.o game.o

test: test.o input.o direction.o point.o tile.o grid.o game.o
	g++ -std=c++11 -o test test.o input.o direction.o point.o tile.o grid.o game.o
	./test

2048.o: 2048.cpp
	g++ -std=c++11 -c 2048.cpp

test.o: test.cpp
	g++ -std=c++11 -c test.cpp

input.o: input.cpp
	g++ -std=c++11 -c input.cpp

direction.o: direction.cpp
	g++ -std=c++11 -c direction.cpp

point.o: point.cpp
	g++ -std=c++11 -c point.cpp

tile.o: tile.cpp
	g++ -std=c++11 -c tile.cpp

grid.o: grid.cpp
	g++ -std=c++11 -c grid.cpp

game.o: game.cpp
	g++ -std=c++11 -c game.cpp

clean:
	rm -f 2048 test *.o

.PHONY: test
