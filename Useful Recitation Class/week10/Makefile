all: ltk

ltk: card.o deck.o exceptions.o game.o hero.o ltk.o player.o
	g++ -std=c++11 -o ltk card.o deck.o exceptions.o game.o hero.o ltk.o player.o

card.o: card.cpp
	g++ -std=c++11 -c card.cpp

deck.o: deck.cpp
	g++ -std=c++11 -c deck.cpp

exceptions.o: exceptions.cpp
	g++ -std=c++11 -c exceptions.cpp

game.o: game.cpp
	g++ -std=c++11 -c game.cpp

hero.o: hero.cpp
	g++ -std=c++11 -c hero.cpp

ltk.o: ltk.cpp
	g++ -std=c++11 -c ltk.cpp

player.o: player.cpp
	g++ -std=c++11 -c player.cpp

clean:
	rm -f ltk *.o
