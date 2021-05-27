#include "deck.h"
#include "exceptions.h"

using namespace std;

Deck::Deck() : cards() {
    cards[0] = new Strike(SIX, DIAMONDS);
    cards[1] = new Strike(SEVEN, DIAMONDS);
    cards[2] = new Strike(EIGHT, DIAMONDS);
    cards[3] = new Strike(NINE, DIAMONDS);
    cards[4] = new Strike(TEN, DIAMONDS);
    cards[5] = new Strike(KING, DIAMONDS);
    cards[6] = new Strike(SEVEN, SPADES);
    cards[7] = new Strike(EIGHT, SPADES);
    cards[8] = new Strike(EIGHT, SPADES);
    cards[9] = new Strike(NINE, SPADES);
    cards[10] = new Strike(NINE, SPADES);
    cards[11] = new Strike(TEN, SPADES);
    cards[12] = new Strike(TEN, SPADES);
    cards[13] = new Strike(TEN, HEARTS);
    cards[14] = new Strike(TEN, HEARTS);
    cards[15] = new Strike(JACK, HEARTS);
    cards[16] = new Strike(TWO, CLUBS);
    cards[17] = new Strike(THREE, CLUBS);
    cards[18] = new Strike(FOUR, CLUBS);
    cards[19] = new Strike(FIVE, CLUBS);
    cards[20] = new Strike(SIX, CLUBS);
    cards[21] = new Strike(SEVEN, CLUBS);
    cards[22] = new Strike(EIGHT, CLUBS);
    cards[23] = new Strike(EIGHT, CLUBS);
    cards[24] = new Strike(NINE, CLUBS);
    cards[25] = new Strike(NINE, CLUBS);
    cards[26] = new Strike(TEN, CLUBS);
    cards[27] = new Strike(TEN, CLUBS);
    cards[28] = new Strike(JACK, CLUBS);
    cards[29] = new Strike(JACK, CLUBS);
    cards[30] = new Dodge(TWO, DIAMONDS);
    cards[31] = new Dodge(TWO, DIAMONDS);
    cards[32] = new Dodge(THREE, DIAMONDS);
    cards[33] = new Dodge(FOUR, DIAMONDS);
    cards[34] = new Dodge(FIVE, DIAMONDS);
    cards[35] = new Dodge(SIX, DIAMONDS);
    cards[36] = new Dodge(SEVEN, DIAMONDS);
    cards[37] = new Dodge(EIGHT, DIAMONDS);
    cards[38] = new Dodge(NINE, DIAMONDS);
    cards[39] = new Dodge(TEN, DIAMONDS);
    cards[40] = new Dodge(JACK, DIAMONDS);
    cards[41] = new Dodge(JACK, DIAMONDS);
    cards[42] = new Dodge(TWO, HEARTS);
    cards[43] = new Dodge(TWO, HEARTS);
    cards[44] = new Dodge(KING, HEARTS);
    cards[45] = new Peach(SIX, HEARTS);
    cards[46] = new Peach(QUEEN, CLUBS);
    cards[47] = new Peach(THREE, HEARTS);
    cards[48] = new Peach(FOUR, HEARTS);
    cards[49] = new Peach(SEVEN, HEARTS);
    cards[50] = new Peach(EIGHT, HEARTS);
    cards[51] = new Peach(NINE, HEARTS);
    cards[52] = new Peach(QUEEN, HEARTS);
    cards[53] = new ArrowBarrage(ACE, HEARTS);
    cards[54] = new BarbarianInvasion(SEVEN, HEARTS);
    cards[55] = new BarbarianInvasion(KING, HEARTS);
    cards[56] = new BarbarianInvasion(SEVEN, CLUBS);
    cards[57] = new SomethingForNothing(SEVEN, HEARTS);
    cards[58] = new SomethingForNothing(EIGHT, HEARTS);
    cards[59] = new SomethingForNothing(NINE, HEARTS);
    cards[60] = new SomethingForNothing(JACK, HEARTS);
    cards[61] = new BountifulHarvest(THREE, HEARTS);
    cards[62] = new BountifulHarvest(FOUR, HEARTS);
    cards[63] = new PeachGarden(ACE, HEARTS);
    cards[64] = new Dismantle(THREE, SPADES);
    cards[65] = new Dismantle(FOUR, SPADES);
    cards[66] = new Dismantle(QUEEN, SPADES);
    cards[67] = new Dismantle(QUEEN, HEARTS);
    cards[68] = new Dismantle(THREE, CLUBS);
    cards[69] = new Dismantle(FOUR, CLUBS);
    cards[70] = new Snatch(THREE, DIAMONDS);
    cards[71] = new Snatch(FOUR, DIAMONDS);
    cards[72] = new Snatch(THREE, SPADES);
    cards[73] = new Snatch(FOUR, SPADES);
    cards[74] = new Snatch(JACK, SPADES);
    cards[75] = new Duel(ACE, DIAMONDS);
    cards[76] = new Duel(ACE, SPADES);
    cards[77] = new Duel(ACE, CLUBS);
    for (const Card *card : cards) {
        pushCard(card);
    }
}

void Deck::pushCard(const Card *card) {
    size_t count = deck.empty() ? 0 : rand() % deck.size();
    auto it = deck.begin();
    for (size_t i = 0; i < count; i++) {
        it++;
    }
    deck.insert(it, card);
}

const Card *Deck::popCard() {
    if (deck.empty()) {
        throw EmptyDeckException();
    } else {
        const Card *card = deck.back();
        deck.pop_back();
        return card;
    }
}

Deck::~Deck() {
    for (const Card *card : cards) {
        delete card;
    }
}

Deck *getDeck() {
    static Deck deck;
    return &deck;
}