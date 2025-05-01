#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H
#include <string>
#include "Board.h"

struct playerInfo {
    std::string firstName;
    std::string lastName;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int points;
};

#endif