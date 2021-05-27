#include "game.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

const vector<Player *> &Game::getPlayers() {
    return players;
}

void Game::printPlayers() const {
    size_t i = 1;
    for (Player *player:players) {
        cout << "[" << i << "] ";
        player->printName();
        cout << " ";
        player->printHealth();
        cout << " ";
        player->getHero()->printName();
        cout << endl;
        i++;
    }
}

void Game::addPlayer(const string &name, Camp camp) {
    Player *player;
    if (name == "m") {
        player = new MyopicPlayer(name, camp);
    } else {
        player = new HumanPlayer(name, camp);
    }
    players.push_back(player);
}

void Game::run() {
    shuffle(players.begin(), players.end(), default_random_engine((unsigned) time(nullptr)));
    if (isOver()) {
        printResult();
        return;
    }
    try {
        for (Player *player: players) {
            player->drawCards(4);
        }
        while (true) {
            for (Player *player: players) {
                if (player->getHealth()) {
                    player->printPlayer();
                    player->drawCards(2);
                    player->setStriked(false);
                    while (true) {
                        try {
                            player->playCard();
                            if (isOver()) {
                                printResult();
                                return;
                            }
                        } catch (DiscardException &e) {
                            break;
                        }
                    }
                    player->discardCards();
                    if (isOver()) {
                        printResult();
                        return;
                    }
                    cout << endl;
                }
            }
        }
    } catch (EmptyDeckException &e) {
        cout << "Deck is empty. It's a draw." << endl;
        return;
    }

}

bool Game::isOver() const {
    Camp firstCamp = CAMP_SIZE;
    for (Player *player: players) {
        if (player->getHealth()) {
            if (firstCamp == CAMP_SIZE) {
                firstCamp = player->getCamp();
            } else {
                if (firstCamp != player->getCamp()) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Game::printResult() const {
    for (Player *player: players) {
        if (player->getHealth()) {
            player->printName();
            cout << ", ";
        }
    }
    cout << "you have won!" << endl;
}

Game::~Game() {
    for (Player *player: players) {
        delete player;
    }
}

Game *getGame() {
    static Game game;
    return &game;
}
