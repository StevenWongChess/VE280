#include "grid.h"
#include "const.h"
#include "point.h"
#include "tile.h"
#include <iostream>
#include <iomanip>
#include <fstream>

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
    if(insideGrid(pt) && !isEmpty(pt)){
        setSquare(pt, getSquare(pt) + 1);
    }
    // TODO: Your implementation here
}

void union_two(const int &i, const int &j, const Direction &dir, unsigned int &result, Grid &g){
    struct Point p = {i, j};  
    if(g.insideGrid(adjacentPoint(p, dir)) && !g.isEmpty(p) && !g.isEmpty(adjacentPoint(p, dir))
        && g.getSquare(p)->points == g.getSquare(adjacentPoint(p, dir))->points){
        // ofstream oFile;
        // oFile.open("1.txt", std::ios_base::app);
        // oFile << i << " " << j << " " << dir << " " << g.getSquare(p)->points << " " << g.getSquare(adjacentPoint(p, dir))->points << endl;
        // oFile.close();
        result += 2 * g.getSquare(p)->points;
        g.upgradeTile(adjacentPoint(p, dir));
        g.clearSquare(p);
        g.shiftTiles(dir);
    } 
}

unsigned int Grid::collapseTiles(Direction dir) {
    // TODO: Your implementation here
    unsigned int result = 0;
    if(dir == UP){
        for(int i = 0; i < getHeight(); i++){
            for(int j = 0; j < getWidth(); j++){
                 union_two(i, j, dir, result, *this);
            }
        }
    }
    else if(dir == DOWN){
        for(int i = getHeight() - 1; i >= 0 ; i--){
            for(int j = 0; j < getWidth(); j++){
                 union_two(i, j, dir, result, *this);
            }
        }
    }    
    else if(dir == LEFT){
        for(int i = 0; i < getHeight(); i++){
            for(int j = 0; j < getWidth(); j++){
                 union_two(i, j, dir, result, *this);
            }
        }
    }
    else{
        for(int i = 0; i < getHeight(); i++){
            for(int j = getWidth() - 1; j >= 0; j--){
                 union_two(i, j, dir, result, *this);
            }
        }
    }
    return result;
}

bool Grid::shiftTile(const Point &dst, const Point &src) {
    // TODO: Your implementation here
    if(isEmpty(src) || !isEmpty(dst))
        return false;
    setSquare(dst, getSquare(src));
    clearSquare(src);
    return true;
}

void moveAll(Point p, const Direction dir, bool &result, Grid &g){
    while(g.insideGrid(adjacentPoint(p, dir))){
        result = g.shiftTile(adjacentPoint(p, dir), p) || result;
        // be careful of the order of short-circuit logic !!!
        p = adjacentPoint(p, dir);
    }   
}
        
bool Grid::shiftTiles(Direction dir) {
    // TODO: Your implementation here
    bool result = false;
    if(dir == LEFT){
        for(int i = 1; i < getWidth(); i++){
            for(int j = 0; j < getHeight(); j++){
                struct Point p = {j, i};
                moveAll(p, dir, result, *this);
            }
        }
    }
    else if(dir == RIGHT){
        for(int i = getWidth() - 2; i >= 0; i--){
            for(int j = 0; j < getHeight(); j++){
                struct Point p = {j, i};
                moveAll(p, dir, result, *this);
            }
        }   
    }
    else if(dir == UP){
        for(int i = 0; i < getWidth(); i++){
            for(int j = 1; j < getHeight(); j++){
                struct Point p = {j, i};
                moveAll(p, dir, result, *this);
            }
        }
    }
    else{
        for(int i = 0; i < getWidth(); i++){
            for(int j = getHeight() - 2; j >= 0; j--){
                struct Point p = {j, i};
                moveAll(p, dir, result, *this);
            }
        }
    }
    return result;
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
