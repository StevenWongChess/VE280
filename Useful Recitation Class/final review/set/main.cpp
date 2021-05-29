#include "set.h"
#include <cstdlib>
#include <cassert>

int main() {
    srand(280);

    const int testSize = 24;
    double test[testSize];
    for (double &num : test) {
        num = (double) rand() / RAND_MAX;
    }

    Set<double> set;
    for (int i = 0; i < testSize / 2; i++) {
        set.insert(test[i]);
    }
    for (int i = 0; i < testSize / 2; i++) {
        assert(set.query(test[i]));
    }

    Set<double> setCopy(set);
    for (int i = testSize / 2; i < testSize; i++) {
        setCopy.insert(test[i]);
    }
    for (int i = 0; i < testSize; i++) {
        assert(setCopy.query(test[i]));
    }

    setCopy = set;
    for (int i = 0; i < testSize / 2; i++) {
        assert(setCopy.query(test[i]));
    }
    for (int i = testSize / 2; i < testSize; i++) {
        assert(!setCopy.query(test[i]));
    }

    for (int i = 0; i < testSize / 2; i++) {
        setCopy.remove(test[i]);
    }
    for (int i = 0; i < testSize / 2; i++) {
        assert(!setCopy.query(test[i]));
    }

    set.display();
}