#include "direction.h"

Direction opposite(Direction dir) {
    Direction opDir;
    switch (dir) {
        case UP:
            opDir = DOWN;
            break;
        case DOWN:
            opDir = UP;
            break;
        case LEFT:
            opDir = RIGHT;
            break;
        case RIGHT:
            opDir = LEFT;
            break;
    }
    return opDir;
}

Direction rotateClockwise(Direction dir) {
    Direction rotDir;
    switch (dir) {
        case UP:
            rotDir = RIGHT;
            break;
        case DOWN:
            rotDir = LEFT;
            break;
        case LEFT:
            rotDir = UP;
            break;
        case RIGHT:
            rotDir = DOWN;
            break;
    }
    return rotDir;
}
