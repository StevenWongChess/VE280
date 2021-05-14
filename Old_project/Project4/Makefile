all: p4

p4: *.o
	g++ -std=c++11 -Wall -o *.o

game.o: game.cpp
	g++ -c game.cpp

exception.o: exception.cpp
	g++ -c exception.cpp

quarto.o: quarto.cpp
	g++ -c quarto.cpp

piece.o: piece.cpp
	g++ -c piece.cpp

player.o: player.cpp
	g++ -c player.cpp

pool.o: pool.cpp
	g++ -c pool.cpp

square.o: square.cpp
	g++ -c square.cpp

board.o: board.cpp
	g++ -c board.cpp

clean:
	rm -f p3 *.o