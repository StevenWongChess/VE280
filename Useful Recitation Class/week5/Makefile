all: lab2

lab2: cord.o test.o
	g++ -std=c++11 -o lab2 cord.o test.o

cord.o: cord.cpp
	g++ -std=c++11 -c cord.cpp

test.o: test.cpp
	g++ -std=c++11 -c test.cpp

clean:
	rm -f lab2 *.o
