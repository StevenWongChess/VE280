echo "n----hard----\n"
g++ -Wall -std=c++11 -o test hard_test.cpp recursive.cpp p2.cpp
./test
echo "n----simple----\n"
g++ -Wall -std=c++11 -o test simple_test.cpp recursive.cpp p2.cpp
./test
echo "\n----treeins----\n"
g++ -Wall -std=c++11 -o test treeins_test.cpp recursive.cpp p2.cpp
./test