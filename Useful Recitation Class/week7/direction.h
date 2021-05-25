#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction {
    UP, DOWN, LEFT, RIGHT
};
/*
// Type: Direction
// ------------------
// This type is used to represent direction, which can take on
// one of the four values: UP, DOWN, LEFT, and RIGHT.
*/

Direction opposite(Direction dir);
/* 
// EFFECTS: Returns opposite Direction of "dir".
*/ 

Direction rotateClockwise(Direction dir);
/* 
// EFFECTS: Returns the direction after rotating "dir" clockwise
//          by 90 degrees.
*/ 

#endif
