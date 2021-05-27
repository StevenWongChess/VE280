#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "card.h"
#include "player.h"
#include <exception>
#include <string>

class EmptyDeckException : public std::exception {
    // OVERVIEW: exception class,
    //           thrown by a Deck when it's empty
};

class DiscardException : public std::exception {
    // OVERVIEW: exception class,
    //           thrown by a Player when refusing to play any card
};

class InvalidInputException : public std::exception {
    // OVERVIEW: exception class,
    //           thrown by a HumanPlayer when the input command is invalid
    const std::string m;

public:
    InvalidInputException(const std::string &s);  // constructor

    virtual const char *what() const noexcept;
    // EFFECTS: returns the error message as a C-style string
};

class CardException : public std::exception {
    // OVERVIEW: virtual exception class,
    //           thrown when a Card is played incorrectly
public:
    virtual const char *what() const noexcept = 0;
    // EFFECTS: returns the error message as a C-style string
};

class NonCastableCardException : public CardException {
    // OVERVIEW: exception class derived from CardException,
    //           thrown by a Hero when a Card is found to be non-castable
    const std::string m;

public:
    NonCastableCardException(const Card *card);  // constructor

    virtual const char *what() const noexcept;
    // EFFECTS: returns the error message as a C-style string
};

class NonPlayableCardException : public CardException {
    // OVERVIEW: exception class derived from CardException,
    //           thrown by a Card when it's found to be non-playable
    const std::string m;

public:
    NonPlayableCardException(const Card *card);  // constructor

    virtual const char *what() const noexcept;
    // EFFECTS: returns the error message as a C-style string
};

class TargetException : public std::exception {
    // OVERVIEW: virtual exception class,
    //           thrown by a Card when the target is found to be invalid
public:
    virtual const char *what() const noexcept = 0;
    // EFFECTS: returns the error message as a C-style string
};

class SelfTargetException : public TargetException {
    // OVERVIEW: exception class derived from TargetException,
    //           thrown by a Card when the target is found to be same as source
    const std::string m;
public:
    SelfTargetException(const Player *player);  // constructor

    virtual const char *what() const noexcept;
    // EFFECTS: returns the error message as a C-style string
};

class DeadTargetException : public TargetException {
    // OVERVIEW: exception class derived from TargetException,
    //           thrown by a Card when the target is found to be dead
    const std::string m;
public:
    DeadTargetException(const Player *player);  // constructor

    virtual const char *what() const noexcept;
    // EFFECTS: returns the error message as a C-style string
};

class GenderException : public TargetException {
    // OVERVIEW: exception class derived from TargetException,
    //           thrown by a Card when the target is found to have a wrong gender
    const std::string m;
public:
    GenderException(const Player *player);  // constructor

    virtual const char *what() const noexcept;
    // EFFECTS: returns the error message as a C-style string
};

#endif
