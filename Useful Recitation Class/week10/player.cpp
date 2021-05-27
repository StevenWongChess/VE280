#include "player.h"
#include "deck.h"
#include "game.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

Player::Player(const string &name, Camp camp) : name(name), camp(camp), hero(newHero()), health(hero->getLife()) {}

string Player::getName() const {
    return name;
}

void Player::printName() const {
    cout << "\033[" << camp << ";97m " << name << " \033[0m";
}

Camp Player::getCamp() const {
    return camp;
}

const Hero *Player::getHero() const {
    return hero;
}

unsigned int Player::getHealth() const {
    return health;
}

void Player::increaseHealth() {
    if (health < hero->getLife()) {
        health++;
    }
}

void Player::decreaseHealth() {
    if (health) {
        health--;
    }
    if (!health) {
        printPlayer();
        for (Player *player:getGame()->getPlayers()) {
            try {
                const Card *card = player->requestCard(PEACH);
                player->printPlay(card, this);
                increaseHealth();
                break;
            } catch (DiscardException &e) {
                continue;
            }
        }
        if (!health) {
            printName();
            cout << " is killed!" << endl;
        }
    }
}

void Player::printHealth() const {
    for (unsigned int i = 0; i < health; i++) {
        cout << "[@]";
    }
    for (unsigned int i = 0; i < hero->getLife() - health; i++) {
        cout << "[ ]";
    }
}

bool Player::getStriked() const {
    return striked;
}

void Player::setStriked(bool striked) {
    this->striked = striked;
}

size_t Player::getNumCards() const {
    return cards.size();
}

void Player::printCards() const {
    size_t i = 1;
    for (const Card *card: cards) {
        cout << "[" << i << "] " << endl;
        card->printCard();
        i++;
    }
}

const Card *Player::eraseCard(size_t index) {
    const Card *card = cards[index];
    cards.erase(cards.begin() + index);
    return card;
}

void Player::pushCard(const Card *card) {
    cards.push_back(card);
}

void Player::printPlayer() const {
    printName();
    cout << " ";
    printHealth();
    cout << " ";
    hero->printHero();
}

void Player::drawCard() {
    cards.push_back(getDeck()->popCard());
}

void Player::drawCards(size_t num) {
    for (size_t i = 0; i < num; i++) {
        drawCard();
    }
}

void Player::printPlay(const Card *card) const {
    printName();
    cout << " plays " << ACTION_NAMES[card->getAction()] << "!" << endl;
    card->printCard();
}


void Player::printPlay(const Card *card, const Player *target) const {
    printName();
    cout << " plays " << ACTION_NAMES[card->getAction()] << " towards ";
    target->printName();
    cout << "!" << endl;
    card->printCard();
}

void Player::printHit(const Card *card) {
    printName();
    cout << " is hit by " << ACTION_NAMES[card->getAction()] << "!" << endl;
}

void Player::discardCard(size_t index) {
    getDeck()->pushCard(cards[index]);
    cards.erase(cards.begin() + index);
}

Player::~Player() {
    delete hero;
}

HumanPlayer::HumanPlayer(const string &name, Camp camp) : Player(name, camp) {}

void HumanPlayer::readCommand(string &command, vector<size_t> &args) const {
    string line;
    size_t arg;
    cin >> command;
    getline(cin, line);
    istringstream iss(line);
    args.clear();
    while (iss >> arg) {
        args.push_back(arg);
    }
}

void HumanPlayer::handleGeneralCommand(const string &command, const vector<size_t> &args) const {
    if (command == "cards") {
        if (!args.empty()) {
            throw InvalidInputException("Command");
        }
        printCards();
    } else if (command == "players") {
        if (!args.empty()) {
            throw InvalidInputException("Command");
        }
        getGame()->printPlayers();
    } else if (command == "player") {
        if (args.empty()) {
            this->printPlayer();
        } else {
            if (args.size() > 1 || args[0] == 0 || args[0] > getGame()->getPlayers().size()) {
                throw InvalidInputException("Command");
            }
            getGame()->getPlayers()[args[0] - 1]->printPlayer();
        }
    } else if (command == "clear") {
        system("clear");
    } else {
        throw InvalidInputException(command);
    }
}

void HumanPlayer::playCard() {
    while (true) {
        cout << endl;
        printName();
        cout << ": Please select a card." << endl << "> ";
        string command;
        vector<size_t> args;
        readCommand(command, args);
        try {
            if (command == "card" || command == "card*") {
                try {
                    const Card *card;
                    if (command == "card") {
                        if (args.size() != 1 || args[0] > cards.size()) {
                            throw InvalidInputException("Command");
                        } else if (args[0] == 0) {
                            throw DiscardException();
                        } else {
                            card = cards[args[0] - 1];
                        }
                    } else {
                        if (args.size() > 1 || (!args.empty() && (args[0] == 0 || args[0] > cards.size()))) {
                            throw InvalidInputException("Command");
                        } else {
                            card = args.empty() ? nullptr : cards[args[0] - 1];
                            card = hero->castCard(card);
                        }
                    }
                    card->takeEffect(this, getGame()->getPlayers());
                    if (!args.empty()) {
                        discardCard(args[0] - 1);
                    }
                    return;
                } catch (CardException &e) {
                    cout << e.what() << endl;
                    continue;
                } catch (TargetException &e) {
                    cout << e.what() << endl;
                    continue;
                }
            } else {
                handleGeneralCommand(command, args);
            }
        } catch (InvalidInputException &e) {
            cout << e.what() << endl;
            continue;
        }
    }
}

Player *HumanPlayer::selectTarget() {
    while (true) {
        cout << endl;
        printName();
        cout << ": Please select a target." << endl << "> ";
        string command;
        vector<size_t> args;
        readCommand(command, args);
        try {
            if (command == "target") {
                if (args.size() != 1 || args[0] == 0 || args[0] > getGame()->getPlayers().size()) {
                    throw InvalidInputException("Command");
                } else {
                    return getGame()->getPlayers()[args[0] - 1];
                }
            } else {
                handleGeneralCommand(command, args);
            }
        } catch (InvalidInputException &e) {
            cout << e.what() << endl;
            continue;
        }
    }
}

const Card *HumanPlayer::requestCard(Action action) {
    while (true) {
        cout << endl;
        printName();
        cout << ": Please select a " << ACTION_NAMES[action] << " card." << endl << "> ";
        string command;
        vector<size_t> args;
        readCommand(command, args);
        try {
            if (command == "card" || command == "card*") {
                try {
                    const Card *card;
                    if (command == "card") {
                        if (args.size() != 1 || args[0] > cards.size()) {
                            throw InvalidInputException("Command");
                        } else if (args[0] == 0) {
                            throw DiscardException();
                        } else {
                            card = cards[args[0] - 1];
                        }
                    } else {
                        if (args.size() > 1 || (!args.empty() && (args[0] == 0 || args[0] > cards.size()))) {
                            throw InvalidInputException("Command");
                        } else {
                            card = args.empty() ? nullptr : cards[args[0] - 1];
                            card = hero->castCard(card);
                        }
                    }
                    if (card->getAction() != action) {
                        throw NonPlayableCardException(card);
                    } else {
                        if (!args.empty()) {
                            discardCard(args[0] - 1);
                        }
                        return card;
                    }
                } catch (CardException &e) {
                    cout << e.what() << endl;
                    continue;
                } catch (TargetException &e) {
                    cout << e.what() << endl;
                    continue;
                }
            } else {
                handleGeneralCommand(command, args);
            }
        } catch (InvalidInputException &e) {
            cout << e.what() << endl;
            continue;
        }
    }
}

void HumanPlayer::discardCards() {
    while (cards.size() > health) {
        cout << endl;
        printName();
        cout << ": Please discard " << cards.size() - health << " cards." << endl << "> ";
        string command;
        vector<size_t> args;
        readCommand(command, args);
        try {
            if (command == "discard") {
                if (args.size() != cards.size() - health) {
                    throw InvalidInputException("Command");
                }
                for (size_t arg:args) {
                    if (arg == 0 || arg > cards.size()) {
                        throw InvalidInputException("Command");
                    }
                }
                for (size_t i = 0; i < args.size() - 1; i++) {
                    if (args[i] >= args[i + 1]) {
                        throw InvalidInputException("Command");
                    }
                }
                reverse(args.begin(), args.end());
                for (size_t arg:args) {
                    discardCard(arg - 1);
                }
                break;
            } else {
                handleGeneralCommand(command, args);
            }
        } catch (InvalidInputException &e) {
            cout << e.what() << endl;
            continue;
        }
    }
}

MyopicPlayer::MyopicPlayer(const string &name, Camp camp) : Player(name, camp) {}

void MyopicPlayer::playCard() {
    // TODO: Improve MyopicPlayer's card playing strategies
    if (!cards.empty()) {
        try {
            cards[rand() % cards.size()]->takeEffect(this, getGame()->getPlayers());
        } catch (exception &e) {}
    }
    throw DiscardException();
};

Player *MyopicPlayer::selectTarget() {
    // TODO: Improve MyopicPlayer's target selecting strategies
    return getGame()->getPlayers()[rand() % getGame()->getPlayers().size()];
}

const Card *MyopicPlayer::requestCard(Action action) {
    const Card *card;
    for (size_t i = 0; i < cards.size(); i++) {
        card = cards[i];
        if (card->getAction() == action) {
            discardCard(i);
            return card;
        }
    }
    for (size_t i = 0; i < cards.size(); i++) {
        try {
            card = hero->castCard(cards[i]);
            if (card->getAction() == action) {
                discardCard(i);
                return card;
            }
        } catch (NonCastableCardException &e) {
            continue;
        }
    }
    try {
        card = hero->castCard(nullptr);
        if (card->getAction() == action) {
            return card;
        }
    } catch (NonCastableCardException &e) {
    }
    throw DiscardException();
}

void MyopicPlayer::discardCards() {
    size_t size = cards.size();
    if (size > health) {
        for (size_t i = 0; i < size - health; i++) {
            getDeck()->pushCard(cards.front());
            cards.pop_front();
        }
    }
}
