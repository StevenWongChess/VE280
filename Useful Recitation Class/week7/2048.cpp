#include "const.h"
#include "input.h"
#include "direction.h"
#include "point.h"
#include "tile.h"
#include "grid.h"
#include "game.h"
#include "color.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <ctime>
#include <locale>

using namespace std;

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    wcout.imbue(locale("en_US.UTF-8"));
    srand((unsigned) time(nullptr));
    unsigned int height, width, numTiles;
    Tile tiles[MAXTILES];
    Color colors[] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, BRIGHT_RED, BRIGHT_GREEN, BRIGHT_YELLOW, BRIGHT_BLUE,
                      BRIGHT_MAGENTA, BRIGHT_CYAN};

    if (argc > 1) {
        if (argc < 4) {
            cout << "Error: Missing arguments!" << endl
                 << "Usage: ./2048 [<height> <width> <tiles-file>]" << endl;
            return 0;
        }
        height = (unsigned) atoi(argv[1]);
        width = (unsigned) atoi(argv[2]);
        if (height <= 0 || height > MAXHEIGHT) {
            cout << "Error: The grid height is illegal!" << endl;
            return 0;
        }
        if (width <= 0 || width > MAXWIDTH) {
            cout << "Error: The grid width is illegal!" << endl;
            return 0;
        }
        numTiles = getTiles(argv[3], tiles);
        if (!numTiles) return 0;
        for (int i = 0; i < numTiles; i++) {
            tiles[i].color = colors[i % 12];
        }
    } else {
        height = 4;
        width = 4;
        numTiles = MAXTILES;
        for (int i = 0; i < numTiles; i++) {
            tiles[i] = {to_wstring((unsigned) pow(2, i + 1)), (unsigned) pow(2, i + 1), colors[i % 12]};
        }
    }

    Game game(height, width, tiles, numTiles);
    //game.debugGrid();
    game.printGame();

    while (true) {
        char c = getChar();
        Direction dir;
        bool valid = true, exit = false;
        switch (c) {
            case 'q':
                exit = true;
                break;
            case 'w':
            case 'A':
                dir = UP;
                break;
            case 's':
            case 'B':
                dir = DOWN;
                break;
            case 'a':
            case 'D':
                dir = LEFT;
                break;
            case 'd':
            case 'C':
                dir = RIGHT;
                break;
            default:
                valid = false;
        }
        if (exit) break;
        if (!valid) continue;

        // unsigned int points = game.collapseTiles(dir);
        bool shifted = game.shiftTiles(dir);
        unsigned int points = game.collapseTiles(dir);
        // game.shiftTiles(dir);
        if (points || shifted) {
            game.newTile();
        }
        game.printGame();
        if (game.checkWin()) {
            game.printWin();
            break;
        }
        if (game.checkLose()) {
            game.printLose();
            break;
        }
    }
    return 0;
}
