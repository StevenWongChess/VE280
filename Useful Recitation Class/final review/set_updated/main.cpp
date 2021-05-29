#include "set.h"
#include <cstdlib>
#include <cassert>
#include <string>
#include <ostream>

using namespace std;

class Rectangle {
    int height;
    int width;
public:
    Rectangle(int height = rand(), int width = rand()) :
            height(height), width(width) {
    }

    int getArea() const {
        return height * width;
    }

    string toString() const {
        return to_string(height) + "*" + to_string(width);
    }

    friend bool operator>(const Rectangle &lhs, const Rectangle &rhs);

    friend bool operator==(const Rectangle &lhs, const Rectangle &rhs);

    friend ostream &operator<<(ostream &os, const Rectangle &rect);
};

bool operator>(const Rectangle &lhs, const Rectangle &rhs) {
    if (lhs.getArea() != rhs.getArea()) {
        return lhs.getArea() > rhs.getArea();
    } else {
        return lhs.height > rhs.width;
    }
}

bool operator==(const Rectangle &lhs, const Rectangle &rhs) {
    return lhs.height == rhs.height && lhs.width == rhs.width;
}

ostream &operator<<(ostream &os, const Rectangle &rect) {
    return os << rect.toString();
}

int main() {
    srand(280);

    const int testSize = 24;
    Rectangle test[testSize];

    Set<Rectangle> set;
    for (int i = 0; i < testSize / 2; i++) {
        set.insert(new Rectangle(test[i]));
        set.insert(new Rectangle(test[i]));
    }
    for (int i = 0; i < testSize / 2; i++) {
        assert(set.query(test[i]));
    }

    Set<Rectangle> setCopy(set);
    for (int i = testSize / 2; i < testSize; i++) {
        setCopy.insert(new Rectangle(test[i]));
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
        delete setCopy.remove(test[i]);
    }
    for (int i = 0; i < testSize / 2; i++) {
        assert(!setCopy.query(test[i]));
    }

    set.display();
}
