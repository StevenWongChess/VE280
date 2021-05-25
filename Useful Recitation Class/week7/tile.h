#ifndef TILE_H
#define TILE_H

#include "color.h"
#include <string>

struct Tile {
    std::wstring value;
    unsigned int points;
    Color color;

    void printTile() const;
};
/*
// Type: Tile
// ------------------
// The type Tile is used to represent a tile on
// the grid. Each Tile type has its value, points
// and color. "value" is tile's string content like
// "2048" or emoji. "points" is the points to add
// when a tile is collapsed. For example, when two
// tiles with 4 points merge, 8 points should be
// added to the player's score.
*/

#endif
