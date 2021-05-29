#include "skip_list.h"
#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

int main() {
    srand(280);

    const int testSize = 24;
    double test[testSize];
    for (double &num : test) {
        num = (double) rand() / RAND_MAX;
    }

    SkipList<double> skipList;
    for (int i = 0; i < testSize / 2; i++) {
        skipList.insert(test[i]);
    }
    for (int i = 0; i < testSize / 2; i++) {
        assert(skipList.search(test[i]));
    }

    // skipList.display();
    SkipList<double> skipListCopy(skipList); 
    // cout << "haha\n";
    for (int i = testSize / 2; i < testSize; i++) {
        skipListCopy.insert(test[i]);
    }

    for (int i = 0; i < testSize; i++) {
        assert(skipListCopy.search(test[i]));
    }
    skipListCopy = skipList;
    // cout << "lala\n";
    for (int i = 0; i < testSize / 2; i++) {
        assert(skipListCopy.search(test[i]));
    }
    for (int i = testSize / 2; i < testSize; i++) {
        assert(!skipListCopy.search(test[i]));
    }

    for (int i = 0; i < testSize / 2; i++) {
        skipListCopy.remove(test[i]);
    }
    for (int i = 0; i < testSize / 2; i++) {
        assert(!skipListCopy.search(test[i]));
    }

    skipList.display();

    return 0;
} 