#include "tile.h"
#include "const.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Tile::printTile() const {
    if (PRINTCOLOR) {
        wcout << setw(TILEWIDTH) << "\033[" << color << "m" << value << "\033[0m\t";
    } else {
        wcout << setw(TILEWIDTH) << value << "\t";
    }
}
