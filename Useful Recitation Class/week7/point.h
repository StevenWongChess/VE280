#ifndef POINT_H
#define POINT_H

#include "direction.h"
#include <iostream>

struct Point {
    int r;
    int c;
};
/*
// Type: Point
// ------------------
// The type Point is used to represent a coordinate.
// "r" is for row and "c" is for column.
*/

bool operator==(const Point &lhs, const Point &rhs);
/* 
// EFFECTS: Overload "==" operator to compare Point type.
//          Returns whether two points are the same.
*/ 

bool operator!=(const Point &lhs, const Point &rhs);
/* 
// EFFECTS: Overload "!=" operator to compare Point type.
//          Returns whether two points are different.
*/ 

std::ostream &operator<<(std::ostream &out, const Point &pt);
/* 
// MODIFIES: "out"
// EFFECTS: Returns ostream "out" after inserting "pt" output.
*/ 

Point adjacentPoint(const Point &pt, Direction dir);
/* 
// EFFECTS: Returns the adjacent point of "pt" to the direction "dir".
*/ 

#endif
