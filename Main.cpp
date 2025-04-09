#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <thread>
#include <atomic>
#include "Board.h"
#include "GameExit.h"

using namespace std;

//rolling dice. any size - determned by int value
int diceRoll(int dice_size){
    return 1 + rand() % dice_size;
    
};

//check for what tile you are on and applys effects
string tileCheck(Board& game, int player_position, int player_path)
{
    char p = game.getTileIndex(player_path,player_position);// find landed tile using chosen path and current position
    //describes events based on landed tile
    if (p == 'B')
    {
        return "nothing happend";
    }
    else if (p == 'Y')
    {
        return "advisor change";
    }
    else if (p == 'P')
    {
        return "riddle";
    }
    else if (p == 'L')
    {
        return "+2 to stats";
    }
    else if (p == 'I')
    {
        return "+3 to stats";
    }
    else if (p == 'G')
    {
        return "Graveyard";
    }
    else if (p == 'O')
    {
        return "Hyena";
    }
    else if (p == 'R')
    {
        return "Custom negitive";
    }
    else if (p == 'C')
    {
        return "Custom Postive";
    }
    else
    {
        return "Exceeded Board Size Ending";
    }
};

int main() {
    //multi threading
    //allows game to always check for esc
    atomic<bool> running(true);
    thread quitThread(checkExit, ref(running));

    srand(time(0)); // Seed RNG once

    //data/variables
    int players = 1;
    int player[2] = {0}; // Initialize player positions
    Board game(players);
    int board = game.getBoardSize();

    game.displayBoard(); // display board

    while (running) {
        for (int i = 0; i < board; i++) {//loop for each tile - if get unlucky will reach end
            for (int b = 0; b < players + 1; b++) {//loop for each player - changes between 0 & 1 for each path/player
                cout << "Player " << b + 1 << " path: ";
                cout << "Press space to roll" << endl;
                //only rolling if space pressed
                while (running){
                    char keypress = _getch();
                    if (keypress == ' '){
                        int move = diceRoll(6);//dice size is 6 may change later
                        game.movePlayer(b, move);
                        game.displayTrack(b);
                        //move player based on dice
                        player[b] += move;
                        cout << tileCheck(game, player[b], b) << endl;

                        // if pos is farther then board stop
                        if (game.getPlayerPosition(b) >= board) {
                            cout << "Game over\n";
                            running = false;
                            break;
                        }
                        break;
                    }
                    //if esc press stop
                    if (keypress == 27){running = false; break;}
                }
            }
            if (!running) break;
        }

        // make space
        for (int i = 0; i < 3; i++) {
            cout << endl;
        }
        game.displayBoard();
    }

    running = false; // tell all threads to stop
    quitThread.join(); // wait for all threads to stop
    cout << "Game terminated.\n";

    cout << "Press any key to exit";
    _getch();
    return 0;
}