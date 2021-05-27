#ifndef HERO_H
#define HERO_H

#include "card.h"
#include <vector>

enum Kingdom {
    WEI = 34, SHU = 31, WU = 32, NEUTRAL = 90, KINGDOM_SIZE = 4
};

enum Gender {
    MALE, FEMALE, GENDER_SIZE
};

extern const char *GENDER_NAMES[GENDER_SIZE];

class Hero {
    // OVERVIEW: virtual base class for all LTK heroes
protected:
    Kingdom kingdom;
    Gender gender;
    unsigned int life;
    std::string name;
    std::string asciiArt;
    std::vector<const Card *> castedCards;
public:
    Hero(Kingdom kingdom, Gender gender, unsigned int life,
         const std::string &name, const std::string &asciiArt);  // constructor

    virtual Kingdom getKingdom() const;
    // EFFECTS: returns the kingdom of hero

    virtual Gender getGender() const;
    // EFFECTS: returns the gender of hero

    virtual unsigned int getLife() const;
    // EFFECTS: returns the life of hero

    virtual std::string getName() const;
    // EFFECTS: returns the name of hero

    virtual void printName() const;
    // EFFECTS: prints the name of hero with color

    virtual void printHero() const;
    // EFFECTS: prints the name and ASCII Art of hero with color

    virtual const Card *castCard(const Card *card) = 0;
    // REQUIRES: "card" is either a nullptr or a pointer to one player's hand card
    // EFFECTS: returns the casted card according to hero's ability,
    //          throws a NonCastableCardException if "card" cannot be casted

    virtual ~Hero();  // destructor
};

class ZhaoYun : public Hero {
    // OVERVIEW: derived class from Hero to implement Zhao Yun
public:
    ZhaoYun();  // constructor

    const Card *castCard(const Card *card) override;
    // REQUIRES: "card" is either a nullptr or a pointer to one player's hand card
    // EFFECTS: treats Strike as Dodge or Dodge as Strike.
};

class ZhenJi : public Hero {
    // OVERVIEW: derived class from Hero to implement Zhen Ji
public:
    ZhenJi();  // constructor

    const Card *castCard(const Card *card) override;
    // REQUIRES: "card" is either a nullptr or a pointer to one player's hand card
    // EFFECTS: treats black color suit card as Dodge.
};

class HuaTuo : public Hero {
    // OVERVIEW: derived class from Hero to implement Hua Tuo
public:
    HuaTuo();  // constructor

    const Card *castCard(const Card *card) override;
    // REQUIRES: "card" is either a nullptr or a pointer to one player's hand card
    // EFFECTS: treats red color suit card as Peach.
};

class LuBu : public Hero {
    // OVERVIEW: derived class from Hero to implement Lu Bu
public:
    LuBu();  // constructor

    const Card *castCard(const Card *card) override;
    // REQUIRES: "card" is either a nullptr or a pointer to one player's hand card
    // EFFECTS: when a Strike is played, the target must use two Dodge to dodge the Strike
};

class DiaoChan : public Hero {
    // OVERVIEW: derived class from Hero to implement Diao Chan
public:
    DiaoChan();  // constructor

    const Card *castCard(const Card *card) override;
    // REQUIRES: "card" is either a nullptr or a pointer to one player's hand card
    // EFFECTS: one card can be discarded to select two Male Heroes and have them Duel each other
};

extern Hero *newHero();
// EFFECTS: returns a pointer to a random Hero which is dynamic allocated

#endif
