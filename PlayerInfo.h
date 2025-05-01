#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H
#include <string>
#include "Board.h"

class playerInfo {
    public:
    std::string firstName;
    std::string lastName;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int points;
    struct Advisor{
        int advisorID;
        std::string advisorName;
        std::string advisorDetails;
    } advisor;
};

#endif