#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H
#include <string>
#include "Board.h"

struct Advisor{
    std::string name = "None";
};

struct playerInfo {
    std::string firstName;
    std::string lastName;
    Advisor advisor;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int points;
};

#endif