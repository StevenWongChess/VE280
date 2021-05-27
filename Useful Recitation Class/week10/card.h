#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

enum Suit {
    SPADES, HEARTS, CLUBS, DIAMONDS, SUIT_SIZE
};

extern const char *SUIT_NAMES[SUIT_SIZE];

enum Spot {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, SPOT_SIZE
};

extern const char *SPOT_NAMES[SPOT_SIZE];

enum Action {
    STRIKE,
    DODGE,
    PEACH,
    ARROW_BARRAGE,
    BARBARIAN_INVASION,
    SOMETHING_FOR_NOTHING,
    BOUNTIFUL_HARVEST,
    PEACH_GARDEN,
    DISMANTLE,
    SNATCH,
    DUEL,
    ACTION_SIZE
};

extern const char *ACTION_NAMES[ACTION_SIZE];

class Player;

const size_t CARD_WIDTH = 13;

class Card {
    // OVERVIEW: virtual base class for all LTK cards
protected:
    Spot spot;
    Suit suit;
    Action action;
public:
    Card(Spot spot, Suit suit, Action action);  // constructor

    virtual Spot getSpot() const;
    // EFFECTS：returns the spot of card

    virtual Suit getSuit() const;
    // EFFECTS: returns the suit of card

    virtual Action getAction() const;
    // EFFECTS: returns the action of card

    virtual std::string toString() const;
    // EFFECTS: returns a string containing the card information

    virtual void printCard() const;
    // EFFECTS: pretty-prints the card

    virtual void takeEffect(Player *source, const std::vector<Player *> &targets) const = 0;
    // REQUIRES: "source" is non-nullptr, "targets" includes all the game players
    // EFFECTS: implements the effect of card,
    //          throws a NonPlayableCardException if the card cannot be played,
    //          throws a TargetException if the selected target is invalid

    virtual ~Card() = default;  // destructor
};


class Strike : public Card {
    // OVERVIEW: derived class from Card to implement Strike
public:
    Strike(Spot spot, Suit suit);  // constructor

    void takeEffect(Player *source, const std::vector<Player *> &targets) const override;
    // REQUIRES: "source" is non-nullptr, "targets" includes all the game players
    // EFFECTS: strikes another player,
    //          can be avoided using a Dodge, otherwise causes −1 health damage,
    //          can only be played once in a turn
};

class Dodge : public Card {
    // OVERVIEW: derived class from Card to implement Dodge
public:
    Dodge(Spot spot, Suit suit);  // constructor

    void takeEffect(Player *source, const std::vector<Player *> &targets) const override;
    // REQUIRES: "source" is non-nullptr, "targets" includes all the game players
    // EFFECTS: none
};

class Peach : public Card {
    // OVERVIEW: derived class from Card to implement Peach
public:
    Peach(Spot spot, Suit suit);  // constructor

    void takeEffect(Player *source, const std::vector<Player *> &targets) const override;
    // REQUIRES: "source" is non-nullptr, "targets" includes all the game players
    // EFFECTS: recovers one health point without exceeding the maximum value
};

class ArrowBarrage : public Card {
    // OVERVIEW: derived class from Card to implement Arrow Barrage
public:
    ArrowBarrage(Spot spot, Suit suit);  // constructor

    void takeEffect(Player *source, const std::vector<Player *> &targets) const override;
    // REQUIRES: "source" is non-nullptr, "targets" includes all the game players
    // EFFECTS: takes effect on all players, except the current player,
    //          must play a Dodge or receive −1 health damage
};

class BarbarianInvasion : public Card {
    // OVERVIEW: derived class from Card to implement Barbarian Invasion
public:
    BarbarianInvasion(Spot spot, Suit suit);  // constructor

    void takeEffect(Player *source, const std::vector<Player *> &targets) const override;
    // REQUIRES: "source" is non-nullptr, "targets" includes all the game players
    // EFFECTS: takes effect on all players, except the current player,
    //          must play a Strike or receive −1 health damage
};

class SomethingForNothing : public Card {
    // OVERVIEW: derived class from Card to implement Something for Nothing
public:
    SomethingForNothing(Spot spot, Suit suit);  // constructor

    void takeEffect(Player *source, const std::vector<Player *> &targets) const override;
    // REQUIRES: "source" is non-nullptr, "targets" includes all the game players
    // EFFECTS: draws two cards
};

class BountifulHarvest : public Card {
    // OVERVIEW: derived class from Card to implement Bountiful Harvest
public:
    BountifulHarvest(Spot spot, Suit suit);  // constructor

    void takeEffect(Player *source, const std::vector<Player *> &targets) const override;
    // REQUIRES: "source" is non-nullptr, "targets" includes all the game players
    // EFFECTS: each player draws one card
};

class PeachGarden : public Card {
    // OVERVIEW: derived class from Card to implement Peach Garden
public:
    PeachGarden(Spot spot, Suit suit);  // constructor

    void takeEffect(Player *source, const std::vector<Player *> &targets) const override;
    // REQUIRES: "source" is non-nullptr, "targets" includes all the game players
    // EFFECTS: all players regain one health point;
};

class Dismantle : public Card {
    // OVERVIEW: derived class from Card to implement Dismantle
public:
    Dismantle(Spot spot, Suit suit);  // constructor

    void takeEffect(Player *source, const std::vector<Player *> &targets) const override;
    // REQUIRES: "source" is non-nullptr, "targets" includes all the game players
    // EFFECTS: discards a random card of another player
};

class Snatch : public Card {
    // OVERVIEW: derived class from Card to implement Snatch
public:
    Snatch(Spot spot, Suit suit);  // constructor

    void takeEffect(Player *source, const std::vector<Player *> &targets) const override;
    // REQUIRES: "source" is non-nullptr, "targets" includes all the game players
    // EFFECTS: seizes a random card of another player
};

class Duel : public Card {
    // OVERVIEW: derived class from Card to implement Duel
public:
    Duel(Spot spot, Suit suit);  // constructor

    void takeEffect(Player *source, const std::vector<Player *> &targets) const override;
    // REQUIRES: "source" is non-nullptr, "targets" includes all the game players
    // EFFECTS: challenges another player into a duel during which the two players have to play Strike cards,
    //          the first one not playing Strike gets -1 health damage
};

#endif
