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

class playerAdvisor {
    private:
    int current_advisor[Board::_MAX_PLAYERS];
    public:
    void displayAdvisor(int player_index);
};

#endif