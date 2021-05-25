#include "input.h"
#include "const.h"
#include <iostream>
#include <fstream>
#include <locale>

using namespace std;

#ifdef _WIN32

char getChar() {
    char c;
    cin >> c;
    return c;
}

#else

#include <termios.h>
#include <unistd.h>

char getChar() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

#endif

unsigned int getTiles(std::string tilesFile, Tile *tiles) {
    wifstream wif;
    wif.imbue(locale("en_US.UTF-8"));
    wif.open(tilesFile);
    if (!wif) {
        cout << "Error: Cannot open file " << tilesFile << "!" << endl;
        return 0;
    }
    wstring tileValue;
    unsigned int numTiles = 0;
    while (getline(wif, tileValue) && !tileValue.empty()) {
        if (numTiles >= MAXTILES) {
            cout << "Error: Too many tiles!" << endl << "Maximum number of tiles is " << MAXTILES << "." << endl;
            return 0;
        }
        tiles[numTiles] = {tileValue, (unsigned) pow(2, numTiles + 1), DEFAULT};
        numTiles++;
    }
    if (numTiles < MINTILES) {
        cout << "Error: Too few tiles!" << endl << "Minimum number of tiles is " << MINTILES << "." << endl;
        return 0;
    }
    return numTiles;
}
