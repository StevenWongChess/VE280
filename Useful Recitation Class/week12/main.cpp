#include "skip_list.h"
#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

int main() {
	srand(9);
    int test[10];
    int size = 10;
    for(auto i = 0; i < size; i++){
    	test[i] = i;
    }
    SkipList<int> skipList;
    for (int i = 0; i < size; i++) {
        skipList.insert(test[i]);
    }
    assert(skipList.search(3));
    assert(!skipList.search(11));
    skipList.remove(5);
    SkipList<int> b = skipList;
    // skipList.display();
    b.display();
    return 0;
}



