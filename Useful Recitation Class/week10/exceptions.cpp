#include "exceptions.h"
#include "player.h"
#include <string>

using namespace std;

InvalidInputException::InvalidInputException(const string &s) : m(s + " is an invalid input.") {}

const char *InvalidInputException::what() const noexcept {
    return m.c_str();
}

NonCastableCardException::NonCastableCardException(const Card *card) : m(
        (card == nullptr ? "nullptr" : card->toString()) + " cannot be casted.") {}

const char *NonCastableCardException::what() const noexcept {
    return m.c_str();
}

NonPlayableCardException::NonPlayableCardException(const Card *card) : m(
        (card == nullptr ? "nullptr" : card->toString()) + " cannot be played.") {}

const char *NonPlayableCardException::what() const noexcept {
    return m.c_str();
}

SelfTargetException::SelfTargetException(const Player *player) : m(
        player->getName() + " (yourself) cannot be selected as the target.") {}

const char *SelfTargetException::what() const noexcept {
    return m.c_str();
}

DeadTargetException::DeadTargetException(const Player *player) : m(
        player->getName() + " (dead) cannot be selected as the target.") {}

const char *DeadTargetException::what() const noexcept {
    return m.c_str();
}

GenderException::GenderException(const Player *player) : m(
        player->getName() + " (" + GENDER_NAMES[player->getHero()->getGender()] +
        ") cannot be selected as the target.") {}

const char *GenderException::what() const noexcept {
    return m.c_str();
}
