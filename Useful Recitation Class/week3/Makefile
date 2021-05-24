all: lab1

lab1: lab1.o magnanimous.o jordan_polya.o alternating.o duffinian.o
	g++ -o lab1 lab1.o magnanimous.o jordan_polya.o alternating.o duffinian.o

lab1.o: lab1.cpp
	g++ -c lab1.cpp

magnanimous.o: magnanimous.cpp
	g++ -c magnanimous.cpp

jordan_polya.o: jordan_polya.cpp
	g++ -c jordan_polya.cpp

alternating.o: alternating.cpp
	g++ -c alternating.cpp

duffinian.o: duffinian.cpp
	g++ -c duffinian.cpp

clean:
	rm -f lab1 *.o
