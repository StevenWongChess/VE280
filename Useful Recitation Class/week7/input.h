#ifndef INPUT_H
#define INPUT_H

#include "tile.h"
#include <string>

char getChar();
/* 
// EFFECTS: Return one character read from keyboard.
*/ 

unsigned int getTiles(std::string tilesFile, Tile *tiles);
/* 
// MODIFIES: "tiles"
// EFFECTS: Reads tile character from file "tilesFile", e.g. 2048, emoji.
//          Return the number of Tiles in the file "tilesFile".
//          Return 0 if any error occurs.
*/ 

#endif
