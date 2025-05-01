#include "Sort.h"           // which already includes PlayerInfo.h
#include <iostream>         // if you use any I/O here

using namespace std;

void endGame(int numPlayers, playerInfo playerData[])
{
    for (int i = 0; i < numPlayers; ++i) {
        // sum up strength, wisdom, and stamina
        int totalStats = playerData[i].strength
                       + playerData[i].wisdom
                       + playerData[i].stamina;
        // multiply by 10 and add to current wisdom
        int bonusPoints = totalStats * 10;
        playerData[i].points += bonusPoints;
    }
}
