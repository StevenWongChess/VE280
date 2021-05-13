#!/bin/zsh
g++ -std=c++11 -Wall -o p3 p3.cpp simulation.cpp
./p3 species world-tests/outside-world 5 > 1.answer
diff 1.answer ./world-tests/outside-world.answer
./p3 species world-tests/overlap-world 5 > 1.answer
diff 1.answer ./world-tests/overlap-world.answer

test(){
	./p3 species world-tests/world$1 $2 v > 1.answer
	diff 1.answer ./world-tests/world${1}-verbose.answer
	./p3 species world-tests/world$1 $2 > 1.answer
	diff 1.answer ./world-tests/world${1}-concise.answer
}

test 1 5
test 2 20
test 3 40
