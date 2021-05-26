#include "game.h"
#include "const.h"
#include "tile.h"
#include "grid.h"
#include <iostream>
#include <sstream>

using namespace std;

Game::Game(unsigned int height, unsigned int width, Tile tiles[], unsigned int numTiles) :
        grid(height, width), score(0), numTiles(numTiles) {
    for (int i = 0; i < numTiles; i++) {
        this->tiles[i] = tiles[i];
    }
    for (int i = 0; i < STARTTILES; i++) {
        newTile();
    }
}

unsigned int Game::getScore() const {
    return score;
}

void Game::debugGrid() {
    grid.clearSquares();
    grid.setSquare({2, 1}, &tiles[0]);
    grid.setSquare({3, 3}, &tiles[1]);
    grid.setSquare({1, 0}, &tiles[2]);
    grid.setSquare({0, 3}, &tiles[0]);
    grid.setSquare({1, 2}, &tiles[3]);
    grid.setSquare({3, 1}, &tiles[0]);
    grid.setSquare({1, 1}, &tiles[0]);
    grid.setSquare({0, 1}, &tiles[0]);
}

void Game::newTile() {
    int count = 0;
    for (int i = 0; i < grid.getHeight(); i++) {
        for (int j = 0; j < grid.getWidth(); j++) {
            if (grid.isEmpty({i, j})) {
                count++;
            }
        }
    }
    if (!count) return;
    count = rand() % count;
    for (int i = 0; i < grid.getHeight(); i++) {
        for (int j = 0; j < grid.getWidth(); j++) {
            if (grid.isEmpty({i, j})) {
                if (count) {
                    count--;
                } else {
                    grid.setSquare({i, j}, rand() % 100 < TWOPERCENTAGE ? &tiles[0] : &tiles[1]);
                    return;
                }
            }
        }
    }
}

unsigned int Game::collapseTiles(Direction dir) {
    unsigned int points = grid.collapseTiles(dir);
    score += points;
    return points;
}

bool Game::shiftTiles(Direction dir) {
    return grid.shiftTiles(dir);
}

bool Game::checkWin() const {
    // TODO: Your implementation here
    for(int i = 0; i < grid.getHeight(); i++){
        for(int j = 0; i < grid.getWidth(); i++){
            struct Point p = {i, j};
            if(!grid.isEmpty(p) && grid.getSquare(p)->points >= WINPOINTS){
                return true;
            }
        }
    }
    return false;
}

bool Game::checkLose() const {
    // TODO: Your implementation here
    for(int i = 0; i < grid.getHeight(); i++){
        for(int j = 0; j < grid.getWidth(); j++){
            struct Point p = {i, j};
            if(grid.isEmpty(p))
                return false;
        }
    }
    for(int i = 0; i < 4; i++){
        Grid tmp(grid.getHeight(), grid.getWidth());
        for (int i = 0; i < grid.getHeight(); i++) {
            for (int j = 0; j < grid.getWidth(); j++) {
                struct Point p = {i, j};
                tmp.setSquare(p, grid.getSquare(p));
            }
        }
        if(tmp.collapseTiles(static_cast<Direction>(i)) > 0){
            return false;
        }
    }
    return true;
}

void Game::printWin() const {
    for (int i = 0; i < numTiles; i++) {
        if (tiles[i].points == WINPOINTS) {
            wcout << "You've reached tile " << tiles[i].value << ". Congratulations!" << endl;
        }
    }
}

void Game::printLose() const {
    wcout << "Game Over!" << endl;
}

void Game::printGame() const {
    system("clear");
    wcout << "Welcome to 2048!" << endl << endl;
    grid.printGrid();
    wcout << "Your score: " << score << endl;
}

std::string Game::dumpState() const {
    ostringstream oss;
    int index;
    for (int i = 0; i < grid.getHeight(); i++) {
        for (int j = 0; j < grid.getWidth(); j++) {
            index = grid.getSquare({i, j}) == nullptr ? -1 : (int) (grid.getSquare({i, j}) - tiles);
            oss << index << " ";
        }
        oss << endl;
    }
    oss << score << endl;
    return oss.str();
}

void Game::loadState(const std::string &state) {
    istringstream iss(state);
    string line;
    int index;
    for (int i = 0; i < grid.getHeight(); i++) {
        for (int j = 0; j < grid.getWidth(); j++) {
            iss >> index;
            grid.setSquare({i, j}, index >= 0 ? &tiles[index] : nullptr);
        }
        getline(iss, line);
    }
    iss >> score;
}
