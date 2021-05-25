#ifndef GRID_H
#define GRID_H

#include "const.h"
#include "point.h"
#include "tile.h"

class Grid {
    unsigned int height; // Number of rows.
    unsigned int width; // Number of columns.
    Tile *squares[MAXHEIGHT][MAXWIDTH]; // A 2D array storing either nullptr or
                                        // a Tile pointer to Game's tiles array.

public:
    Grid(unsigned int height, unsigned int width);
    /* 
    // MODIFIES: this
    // EFFECTS: Construct an empty grid with height and width.
    */ 

    unsigned int getHeight() const;
    /* 
    // EFFECTS: Return the grid height.
    */ 

    unsigned int getWidth() const;
    /* 
    // EFFECTS: Return the grid width.
    */ 

    bool insideGrid(const Point &pt) const;
    /* 
    // EFFECTS: Check whether a point "pt" is inside the grid.
    */ 

    Tile *getSquare(const Point &pt) const;
    /*
    // REQUIRES: "pt" is inside the grid.
    // EFFECTS: Return the tile pointer of the square at "pt".
    */ 

    void setSquare(const Point &pt, Tile *tile);
    /*
    // REQUIRES: "pt" is inside the grid.
    // MODIFIES: this
    // EFFECTS: Point the square pointer at "pt" to "tile".
    */ 

    void clearSquare(const Point &pt);
    /* 
    // MODIFIES: this
    // EFFECTS: Clear one square.
    */ 

    void clearSquares();
    /* 
    // MODIFIES: this
    // EFFECTS: Clear all the squares.
    */ 

    bool isEmpty(const Point &pt) const;
    /*
    // REQUIRES: "pt" is inside the grid.
    // EFFECTS: Return whether the square at "pt" is empty.
    */ 

    void upgradeTile(const Point &pt);
    /*
    // REQUIRES: "pt" is inside the grid and non-empty
    //           and the next level of tile exists.
    // MODIFIES: this
    // EFFECTS: Upgrade the tile at "pt" to the next level.
    //          For example, Tile "2" will become Tile "4".
    */ 

    unsigned int collapseTiles(Direction dir);
    /* 
    // MODIFIES: this
    // EFFECTS: Collapse all the possible tiles along direction "dir"
    //          When two tiles merge, they become one upgraded tile.
    //          Accumulate the points of the merged tiles.
    //          Return the totally earned points in this round.
    */ 
   
    bool shiftTile(const Point &dst, const Point &src);
    /*
    // REQUIRES: "dst" and "src" are both inside the grid.
    // EFFECTS: Shift/move the tile from "src" to "dst".
    //          Return whether a position change occurs.
    */ 

    bool shiftTiles(Direction dir);
    /* 
    // EFFECTS: Move all the possible tiles along direction "dir"
    //          without collapsing/merging any of them.
    //          Return whether there's any shifted tiles.
    */ 

    void printGrid() const;
    /* 
    // EFFECTS: Print the whole grid.
    */ 
};

#endif
