#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <vector>

class Game {
    // OVERVIEW: the high-level game manager
    std::vector<Player *> players;
public:
    const std::vector<Player *> &getPlayers();
    // EFFECTS: returns a const reference to "players"

    void printPlayers() const;
    // EFFECTS: prints all the players

    void addPlayer(const std::string &name, Camp camp);
    // EFFECTS: adds a player with the given "name" and "camp",
    //          adds a MyopicPlayer if "name" is "m", HumanPlayer otherwise

    void run();
    // EFFECTS: runs the game

    bool isOver() const;
    // EFFECTS: returns true if there is only one camp with alive players

    void printResult() const;
    // EFFECTS: prints a message for all the winners

    ~Game();  // destructor
};

extern Game *getGame();
// EFFECTS: returns the pointer to a static Game object

#endif
