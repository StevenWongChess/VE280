#ifndef CONST_H
#define CONST_H

#include <cmath>

const unsigned int MAXHEIGHT = 20; // Max number of rows
const unsigned int MAXWIDTH = 20; // Max number of columns
const unsigned int MINTILES = 11; // Min number of tiles
const unsigned int MAXTILES = 32; // Max number of tiles
const unsigned int TILEWIDTH = 8; // Character width of one tile output
const unsigned int STARTTILES = 2; // The number of starting tiles
const unsigned int TWOPERCENTAGE = 90; // The probability that "2" occurs instead of "4"
// const unsigned int WINPOINTS = 64;
const unsigned int WINPOINTS = (unsigned) pow(2, MINTILES); // The tile points to win (2048)
const bool PRINTCOLOR = true; // Whether to print colored output

#endif
