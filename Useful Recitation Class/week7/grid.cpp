#include "grid.h"
#include "const.h"
#include "point.h"
#include "tile.h"
#include <iostream>
#include <iomanip>

using namespace std;

Grid::Grid(unsigned int height, unsigned int width) : height(height), width(width), squares() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            squares[i][j] = nullptr;
        }
    }
}

unsigned int Grid::getHeight() const {
    return height;
}

unsigned int Grid::getWidth() const {
    return width;
}

bool Grid::insideGrid(const Point &pt) const {
    return pt.r >= 0 && pt.r < height && pt.c >= 0 && pt.c < width;
}

Tile *Grid::getSquare(const Point &pt) const {
    return squares[pt.r][pt.c];
}

void Grid::setSquare(const Point &pt, Tile *tile) {
    squares[pt.r][pt.c] = tile;
}

void Grid::clearSquare(const Point &pt) {
    setSquare(pt, nullptr);
}

void Grid::clearSquares() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            clearSquare({i, j});
        }
    }
}

bool Grid::isEmpty(const Point &pt) const {
    return getSquare(pt) == nullptr;
}

void Grid::upgradeTile(const Point &pt) {
    // TODO: Your implementation here
}

unsigned int Grid::collapseTiles(Direction dir) {
    // TODO: Your implementation here
    return 0;
}

bool Grid::shiftTile(const Point &dst, const Point &src) {
    // TODO: Your implementation here
    return false;
}

bool Grid::shiftTiles(Direction dir) {
    // TODO: Your implementation here
    return false;
}

void Grid::printGrid() const {
    for (int i = 0; i < height; i++) {
        wcout << "|";
        for (int j = 0; j < width; j++) {
            if (isEmpty({i, j})) {
                wcout << setw(TILEWIDTH) << " " << "\t";
            } else {
                squares[i][j]->printTile();
            }
            wcout << "|";
        }
        wcout << endl << endl;
    }
}
