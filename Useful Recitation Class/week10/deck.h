#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <list>

const int NUM_CARDS = 78;

class Deck {
    // OVERVIEW: container of LTK cards,
    //           "cards" contain all the game cards,
    //           "deck" contains the cards available to draw
    const Card *cards[NUM_CARDS];
    std::list<const Card *> deck;
public:
    Deck();  // constructor

    void pushCard(const Card *card);
    // REQUIRES: "card" doesn't point to a hand card of any player
    // EFFECTS: places "card" at a random position in "deck"

    const Card *popCard();
    // EFFECTS: returns the card at the end of "deck" and removes it from "deck"

    ~Deck();  // destructor
};

extern Deck *getDeck();
// EFFECTS: returns the pointer to a static Deck object

#endif
