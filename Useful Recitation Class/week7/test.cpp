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

Direction charToDirection(char c) {
    Direction dir;
    switch (c) {
        case 'A':
            dir = UP;
            break;
        case 'B':
            dir = DOWN;
            break;
        case 'D':
            dir = LEFT;
            break;
        case 'C':
            dir = RIGHT;
            break;
        default:
            break;
    }
    return dir;
}

int main(int argc, char *argv[]) {
    srand(2048);
    Tile tiles[MAXTILES];

    for (int i = 0; i < MAXTILES; i++) {
        tiles[i] = {to_wstring((unsigned) pow(2, i + 1)), (unsigned) pow(2, i + 1), DEFAULT};
    }

    Game game(5, 6, tiles, MAXTILES);
    game.debugGrid();
    string state;

    cout << "Test shiftTiles: " << flush;
    game.shiftTiles(LEFT);
    state = "0 0 -1 -1 -1 -1 \n"
            "2 0 3 -1 -1 -1 \n"
            "0 -1 -1 -1 -1 -1 \n"
            "0 1 -1 -1 -1 -1 \n"
            "-1 -1 -1 -1 -1 -1 \n"
            "0\n";
    assert(game.dumpState() == state);
    game.shiftTiles(RIGHT);
    state = "-1 -1 -1 -1 0 0 \n"
            "-1 -1 -1 2 0 3 \n"
            "-1 -1 -1 -1 -1 0 \n"
            "-1 -1 -1 -1 0 1 \n"
            "-1 -1 -1 -1 -1 -1 \n"
            "0\n";
    assert(game.dumpState() == state);
    cout << "pass!" << endl;

    cout << "Test collapseTiles: " << flush;
    game.debugGrid();
    game.collapseTiles(UP);
    game.shiftTiles(UP);
    state = "2 1 3 0 -1 -1 \n"
            "-1 1 -1 1 -1 -1 \n"
            "-1 -1 -1 -1 -1 -1 \n"
            "-1 -1 -1 -1 -1 -1 \n"
            "-1 -1 -1 -1 -1 -1 \n"
            "8\n";
    assert(game.dumpState() == state);
    game.collapseTiles(DOWN);
    game.shiftTiles(DOWN);
    state = "-1 -1 -1 -1 -1 -1 \n"
            "-1 -1 -1 -1 -1 -1 \n"
            "-1 -1 -1 -1 -1 -1 \n"
            "-1 -1 -1 0 -1 -1 \n"
            "2 2 3 1 -1 -1 \n"
            "16\n";
    assert(game.dumpState() == state);
    cout << "pass!" << endl;

    cout << "Test checkWin: " << flush;
    unsigned int winIndex = (unsigned int) log2(WINPOINTS) - 1;
    state = "0 0 -1 -1 -1 -1 \n"
            "2 0 3 -1 -1 -1 \n"
            "0 -1 -1 -1 -1 -1 \n"
            "0 1 -1 -1 -1 -1 \n"
            "-1 -1 -1 -1 -1 " + to_string(winIndex) + " \n"
                                                      "0\n";
    game.loadState(state);
    assert(game.checkWin());
    state = "0 0 -1 -1 -1 -1 \n"
            "2 0 3 -1 -1 -1 \n"
            "0 -1 -1 -1 -1 -1 \n"
            "0 1 -1 -1 -1 -1 \n"
            "-1 -1 -1 -1 -1 " + to_string(winIndex - 1) + " \n"
                                                          "0\n";
    game.loadState(state);
    assert(!game.checkWin());
    cout << "pass!" << endl;

    cout << "Test checkLose: " << flush;
    state = "0 1 2 3 4 5 \n"
            "1 2 3 4 5 6 \n"
            "2 3 4 5 6 7 \n"
            "3 4 5 6 7 8 \n"
            "4 5 6 7 8 -1 \n"
            "0\n";
    game.loadState(state);
    assert(!game.checkLose());
    state = "0 1 2 3 4 5 \n"
            "1 2 3 4 5 6 \n"
            "2 3 4 5 6 7 \n"
            "3 4 5 6 7 8 \n"
            "5 6 7 8 9 8 \n"
            "0\n";
    game.loadState(state);
    assert(!game.checkLose());
    state = "0 1 2 3 4 5 \n"
            "1 2 3 4 5 6 \n"
            "2 3 4 5 6 7 \n"
            "3 4 5 6 7 8 \n"
            "4 5 6 7 8 9 \n"
            "0\n";
    game.loadState(state);
    assert(game.checkLose());
    cout << "pass!" << endl;

    cout << "Test random operations: " << flush;
    game.debugGrid();
    string operations = "DBDAABDBCACDBDDCADCCDAADD";
    for (char c : operations) {
        Direction dir = charToDirection(c);
        unsigned int points = game.collapseTiles(dir);
        bool shifted = game.shiftTiles(dir);
        if (points || shifted) {
            game.newTile();
        }
        if (game.checkWin()) {
            break;
        }
        if (game.checkLose()) {
            break;
        }
    }
    state = "2 3 0 -1 -1 -1 \n"
            "3 4 0 -1 -1 -1 \n"
            "2 0 -1 0 -1 -1 \n"
            "0 -1 -1 -1 -1 -1 \n"
            "-1 -1 -1 -1 -1 -1 \n"
            "180\n";
    assert(game.dumpState() == state);
    game.debugGrid();
    while (true) {
        char c = "ABCD"[rand() % 4];
        Direction dir = charToDirection(c);
        unsigned int points = game.collapseTiles(dir);
        bool shifted = game.shiftTiles(dir);
        if (points || shifted) {
            game.newTile();
        }
        if (game.checkWin()) {
            break;
        }
        if (game.checkLose()) {
            break;
        }
    }
    state = "1 -1 -1 -1 -1 -1 \n"
            "2 -1 1 0 -1 -1 \n"
            "0 4 5 -1 -1 -1 \n"
            "1 3 1 -1 1 -1 \n"
            "0 4 4 10 6 1 \n"
            "21788\n";
    assert(game.dumpState() == state);
    cout << "pass!" << endl;

    return 0;
}
