#include "point.h"
#include "direction.h"
#include <iostream>

using namespace std;

bool operator==(const Point &lhs, const Point &rhs) {
    return lhs.r == rhs.r && lhs.c == rhs.c;
}

bool operator!=(const Point &lhs, const Point &rhs) {
    return lhs.r != rhs.r || lhs.c != rhs.c;
}

ostream &operator<<(ostream &out, const Point &pt) {
    return out << "(" << pt.r << ", " << pt.c << ")";
}

Point adjacentPoint(const Point &pt, Direction dir) {
    Point adjPt;
    switch (dir) {
        case UP:
            adjPt = {pt.r - 1, pt.c};
            break;
        case DOWN:
            adjPt = {pt.r + 1, pt.c};
            break;
        case LEFT:
            adjPt = {pt.r, pt.c - 1};
            break;
        case RIGHT:
            adjPt = {pt.r, pt.c + 1};
            break;
    }
    return adjPt;
}
