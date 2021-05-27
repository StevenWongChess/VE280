#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "hero.h"
#include "exceptions.h"
#include <deque>

enum Camp {
    RED = 41, GREEN = 42, YELLOW = 43, BLUE = 44, CAMP_SIZE = 4
};

class Player {
    // OVERVIEW: virtual base class for a game player
protected:
    std::string name;
    Camp camp;
    Hero *hero;
    unsigned int health;
    bool striked;
    std::deque<const Card *> cards;
public:
    Player(const std::string &name, Camp camp);  // constructor

    virtual std::string getName() const;
    // EFFECTS: returns the name of player

    virtual void printName() const;
    // EFFECTS: prints the name of player with color

    virtual Camp getCamp() const;
    // EFFECTS: returns the camp of player

    virtual const Hero *getHero() const;
    // EFFECTS: returns the hero of player

    virtual unsigned int getHealth() const;
    // EFFECTS: returns the health of player

    virtual void increaseHealth();
    // EFFECTS: increases the health of player by one point without exceeding the maximum value

    virtual void decreaseHealth();
    // EFFECTS: decreases the health of player by one point,
    //          if it's decreased to zero, asks any player to play a Peach

    virtual void printHealth() const;
    // EFFECTS: pretty-prints the health of player

    virtual bool getStriked() const;
    // EFFECTS: returns the "striked" value

    virtual void setStriked(bool striked);
    // EFFECTS: sets the "striked" value

    virtual size_t getNumCards() const;
    // EFFECTS: returns the size of "cards"

    virtual void printCards() const;
    // EFFECTS: pretty-prints "cards"

    virtual const Card *eraseCard(size_t index);
    // REQUIRES: 0 <= index < cards.size()
    // EFFECTS: removes the card at "index" from "cards" and returns the pointer to it

    virtual void pushCard(const Card *card);
    // REQUIRES: "card" doesn't point to a card in deck
    // EFFECTS: inserts "card" into the end of "cards"

    virtual void printPlayer() const;
    // EFFECTS: pretty-prints the player

    virtual void drawCard();
    // EFFECTS: inserts the card at the end of deck to "cards"

    virtual void drawCards(size_t num);
    // EFFECTS: inserts "num" cards at the end of deck to "cards"

    virtual void playCard() = 0;
    // EFFECTS: plays a card,
    //          throws a DiscardException if refusing to play a card

    virtual void printPlay(const Card *card) const;
    // EFFECTS: prints the message of the current player playing "card"

    virtual void printPlay(const Card *card, const Player *target) const;
    // EFFECTS: prints the message of the current player playing "card" towards "target"

    virtual void printHit(const Card *card);
    // EFFECTS: prints the message of the current player being hit by "card"

    virtual Player *selectTarget() = 0;
    // EFFECTS: selects a target

    virtual const Card *requestCard(Action action) = 0;
    // EFFECTS: responds with a card which has the required "action"

    virtual void discardCard(size_t index);
    // REQUIRES: 0 <= index < cards.size()
    // EFFECTS: removes the card at "index" from "cards" and put it back to deck

    virtual void discardCards() = 0;
    // EFFECTS: removes the required number of cards from "cards" and puts them back to deck

    virtual ~Player();  // destructor
};

class HumanPlayer : public Player {
    // OVERVIEW: derived class from Player to implement HumanPlayer
private:
    void readCommand(std::string &command, std::vector<size_t> &args) const;
    // EFFECTS: reads a command and writes into "command" and "args"

    void handleGeneralCommand(const std::string &command, const std::vector<size_t> &args) const;
    // EFFECTS: handles general commands including "clear", "players", "player", "cards"

public:
    HumanPlayer(const std::string &name, Camp camp);  // constructor

    void playCard() override;
    // EFFECTS: plays a card according to the HumanPlayer's command,
    //          keeps prompting for new command if the card cannot be played correctly

    Player *selectTarget() override;
    // EFFECTS: selects a target according to the HumanPlayer's command,
    //          keeps prompting for new command if the selected target is invalid

    const Card *requestCard(Action action) override;
    // EFFECTS: responds with a card which has the required "action",
    //          keeps prompting for new command if the selected card is invalid

    void discardCards() override;
    // EFFECTS: removes the required number of cards from "cards" and puts them back to deck,
    //          keeps prompting for new command if not enough cards are discarded
};

class MyopicPlayer : public Player {
    // OVERVIEW: derived class from Player to implement MyopicPlayer
public:
    MyopicPlayer(const std::string &name, Camp camp);  // constructor

    void playCard() override;
    // EFFECTS: iterates over "cards" until any card is found to be playable,
    //          then iterates over "cards" again until any card is found to be playable after casting,
    //          then attempts to use hero's ability without any card,
    //          returns immediately if any single move above succeeds

    Player *selectTarget() override;
    // EFFECTS: selects a target in a different camp from the current player

    const Card *requestCard(Action action) override;
    // EFFECTS: iterates over "cards" until any card is found to have "action",
    //          then iterates over "cards" again until any card is found to have "action" after casting,
    //          then attempts to use hero's ability without any card

    void discardCards() override;
    // EFFECTS: randomly selects the required number of cards,
    //          removes them from "cards" and puts them back to deck
};

#endif
