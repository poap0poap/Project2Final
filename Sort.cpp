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

void sortPlayersByPoints(int numPlayers, playerInfo playerData[])
{
    // For each position i, find the max in [i..end) and swap into i
    for (int i = 0; i < numPlayers - 1; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < numPlayers; ++j) {
            if (playerData[j].points > playerData[maxIdx].points) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            playerInfo tmp          = playerData[i];
            playerData[i]           = playerData[maxIdx];
            playerData[maxIdx]      = tmp;
        }
    }
}