all: lab5

lab5: lab5.o
	g++ -std=c++11 -o lab5 lab5.o

test: test.o
	g++ -std=c++11 -o test test.o
	./test

lab5.o: lab5.cpp
	g++ -std=c++11 -c lab5.cpp

test.o: test.cpp
	g++ -std=c++11 -c test.cpp

clean:
	rm -f lab5 test *.o

.PHONY: test
