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

using namespace std;

//rolling dice. any size - determned by int value
int diceRoll(int dice_size){
    return 1 + rand() % dice_size;
    
};

struct playerInfo {
    string firstName;
    string lastName;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int points;
};

//check for what tile you are on and applys effects
string tileAction(Board& game, int player_position, int player_path, int player, playerInfo* playerData)
{
    char p = game.getTileIndex(player_path,player_position);// find landed tile using chosen path and current position
    cout << endl;
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
        playerData[player].strength += 2;
        playerData[player].stamina += 2;
        playerData[player].wisdom += 2;
        return "+2 to stats";
    }
    else if (p == 'I')
    {
        playerData[player].strength += 3;
        playerData[player].stamina += 3;
        playerData[player].wisdom += 3;
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
}

//menu display
void menuDisplay(){
    cout << endl;
    cout << "Press space to roll for turn" << endl;
    cout << "Press 1 for Stats" << endl;
    cout << "Press 2 for current Charcter" << endl;
    cout << "Press 3 for current Boardstate" << endl;
    cout << "Press 4 for current Advisor" << endl;
    cout << endl;
}

//stat display
void displayStats(Board& game,int player,playerInfo* playerData){
    cout << "Strength: " << playerData[player].strength << endl;
    cout << "Stamina: " << playerData[player].stamina << endl;
    cout << "Wisdom: " << playerData[player].wisdom << endl;
    cout << "Points: " << playerData[player].points << endl;
}

//charcter inforemation
void charInfo(Board& game,int player, playerInfo* playerData){
    cout << "Name: " << playerData[player].firstName << " " << playerData[player].lastName << endl;
    cout << "Age: " << playerData[player].age << endl;
}

//display board
void displayBoard(Board& game,int player){
    cout << "current boardstate:"<< endl;
    game.displayBoard();
}

//advisor information
void displayAdvisor(Board& game,int player){
    cout << "Advisor is a work in progress" << endl;
}

//rolling turn actions
int turn(Board& game,int current_player,int board, int* player, playerInfo* playerData){
    char keypress = _getch();
    if (keypress == ' '){
        int move = diceRoll(6);//dice size is 6 may change later
        game.movePlayer(current_player, move);
        //cout << "Player " << current_player + 1 << " path: ";
        game.displayTrack(current_player);
        //move player current_playerased on dice
        player[current_player] += move;
        cout << tileAction(game, player[current_player], current_player, current_player,  playerData) << endl;

        //if pos is farther then board stop
        if (game.getPlayerPosition(current_player) >= board){
            cout << "Game over\n";
            return -1;
        }
        return 0;
    }
    else{
        switch (keypress){
            case '1':
                displayStats(game, current_player,playerData);
                break;
            case '2':
                charInfo(game, current_player, playerData);
                break;
            case '3':
                displayBoard(game, current_player);
                break;
            case '4':
                displayAdvisor(game, current_player);
                break;
            case '5':
                cout << "just press space" << endl;
                break;
            case 27: //if esc press stop
                return -1;
            default:
                cout << "issues" << endl;
                break;
        }
    }
    cout << endl;
    return 1;
}


int main() {
   
    bool running = true;
    srand(time(0)); //Seed RNG once

    //data/variables
    int players = 1;

    // random player data
    // need to make it a class
    fstream characterFile("charcter.txt");
    int randomLine;
    int lineCount = 0;
    string line;
    playerInfo playerData[4];
    while(getline(characterFile,line)){lineCount++;}
    for (int i = 0;i<players+1;i++){
        randomLine = 1 + rand() % lineCount;
        characterFile.clear();
        characterFile.seekg(0, ios::beg);
        int currentLine = 0;
        while(getline(characterFile,line)){
            currentLine++;
            if (currentLine == randomLine){
                istringstream lineStream(line);
                lineStream >> playerData[i].firstName >> playerData[i].lastName >> playerData[i].age 
                           >> playerData[i].strength >> playerData[i].stamina >> playerData[i].wisdom >> playerData[i].points;
                break;
            }    
        }
    }
    characterFile.close();

    int player[2] = {0}; //initlize player positions
    Board game(players);
    int board = game.getBoardSize();

    game.displayBoard(); //display board

    while (running){
        for (int i = 0; i < board; i++) {//loop for each tile - if get unlucky will reach end
            for (int b = 0; b < players + 1; b++) {//loop for each player - changes between 0 & 1 for each path/player
                //only rolling if space pressed
                menuDisplay();
                while (running){
                    int run = turn(game, b, board, player, playerData);
                    if (run == -1){
                        running = false;
                        break;
                    }
                    else if (run == 0){
                        break;
                    }
                    else if (run == 1){}
                }
            }

            if (rand() % 2 == 0){
                cout << endl;
                cout << "random event occurs" << endl;
            }
            if (!running) break;
        }

        
    }

    //ending text
    cout << "Game terminated.\n";
    cout << "Press any key to exit";
    _getch();//waits until keypress to end
    return 0;

}