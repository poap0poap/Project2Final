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
#include "Board.h"
#include "Player.h"
#include "Utility.h"

using namespace std;

//rolling dice. any size - determned by int value
int diceRoll(int dice_size){
    return 1 + rand() % dice_size;
}


class  pickEvent{
    private:
    const int totalEvents;
    public:
    pickEvent(int total) : totalEvents(total) {}

    int getEvent() {
        return rand() % totalEvents;
    }
};

//check for what tile you are on and applys effects
string tileAction(Board& game, int player_position, int player_path, bool viewing, int player, playerInfo* playerData)
{
    char p = game.getTileIndex(player_path,player_position);// find landed tile using chosen path and current position
    //describes events based on landed tile
    switch(p){
        case 'B':
        return "nothing happend";
        break;
        case 'Y':
        return "advisor change";
        break;
        case 'P':
        return "riddle";
        break;
        case 'L':
        if (!viewing){
            playerData[player].strength += 2;
            playerData[player].stamina += 2;
            playerData[player].wisdom += 2;
        }
        return "+2 to stats";
        break;
        case 'I':
        if (!viewing){
            playerData[player].strength += 3;
            playerData[player].stamina += 3;
            playerData[player].wisdom += 3;
        }
        return "+3 to stats";
        break;
        case 'G':
        if (!viewing){
            playerData[player].strength -= 1;
            playerData[player].stamina -= 1;
            playerData[player].wisdom -= 1;
        }
        return "Graveyard";
        break;
        case 'O':
        if (!viewing){
            playerData[player].stamina -= 5;
        }
        return "Hyena";
        break;
        case 'R':
        if (!viewing){
            playerData[player].strength -= 5;
            playerData[player].stamina -= 5;
            playerData[player].wisdom -= 5;
            playerData[player].points = (playerData[player].points + 1)/2;
        }
        return "Custom negitive";
        break;
        case 'C':
        playerData[player].strength += 5;
            playerData[player].stamina += 5;
            playerData[player].wisdom += 5;
            playerData[player].points += (playerData[player].points + 1)/2;
        return "Custom Postive";
        break;
        case 'S':
        return "Start";
        default:
        return string(1,p);
        return "Exceeded Board Size";
        break;
    }
    return " ";
}

//menu display
void menuDisplay(){
    cout << endl;
    cout << "Space to roll for turn" << endl;
    cout << "1. Stats" << endl;
    cout << "2. Current Charcter" << endl;
    cout << "3. Current Advisor" << endl;
    cout << "4. Current tile effects" << endl;
    cout << "5. Last event" << endl;
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

//Movement
bool movement(Board& game,int current_player,int board, int* player, playerInfo* playerData,int diceSize){
    int dice = diceRoll(diceSize);
    game.movePlayer(current_player, dice);
    //move player current_playerased on dice
    player[current_player] += dice;
    //cout  << tileAction(game, player[current_player], current_player, false, current_player,playerData) << endl;
    //cout << endl;

    //if pos is farther then board stop
    if (game.getPlayerPosition(current_player) >= board){
        cout << "\nGame over\n";
        return false;
    }
    else{
        return true;
    }
}

//menuing
void menuing(Board& game,int current_player,int board, int* player, playerInfo* playerData,char keypress){
    clearBelowLine(17); 
    switch(keypress){
        case '1':
            displayStats(game, current_player,playerData);
            break;
        case '2':
            charInfo(game, current_player, playerData);
            break;
        case '3':
            displayAdvisor(game, current_player);
            break;
        case '4':
            cout << "You are on a(n) " << tileAction(game,player[current_player],current_player,true,current_player,playerData) << " tile." << endl;
            break;
        case '5':
            break;
    }
}

//picks a random event and returns it for storage
int randomEvent(int events,int last_event){
    if (rand() % 2 == 0){
        pickEvent picker(events);
        int event = picker.getEvent();
        switch (event) {
            case 0:
                std::cout << "Event 1 occurs" << std::endl;
                break;
            case 1:
                std::cout << "Event 2 occurs" << std::endl;
                break;
            case 2:
                std::cout << "Event 3 occurs" << std::endl;
                break;
            default:
                std::cout << "Unknown event" << std::endl;
        }
        return event;

    }
    return last_event;
}

//creates our display
bool screen(Board& game,int current_player,int board, int* player, playerInfo* playerData){
    clearScreen();
    game.displayBoard();
    cout << "Player: " << current_player+1 << endl;
    menuDisplay();
    char key = _getch();
    while(true){
        moveCursorToTop();
        game.displayBoard();
        cout << "Player: " << current_player+1 << endl;
        menuDisplay();
        switch (key){
            case 27:
                return false;
                break;
            case ' ':
                return movement(game, current_player , board, player, playerData, 6);
            default:
                menuing(game, current_player , board, player, playerData, key);
                break;
        }
        key = _getch();
    }   
}



int main() {
   
    bool running = true;
    srand(time(0)); //Seed RNG once

    //data/variables
    int last_event;
    int players = 2;
    playerInfo playerData[4];
    int total_events = 3;
    int path[4];
    bool path_selector;
    if(inlitizeCharcters(playerData, players)){}
    else {running = false;}

    //remove this from main
    for (int i = 0; i<players; i++){
        if (!running){break;}
        path_selector = true;
        while(path_selector){
            if (!running){break;}
            cout << "Which path would player " << i+1 <<" like" <<endl;
            cout << "Press 1 for the easier path" << endl;
            cout << "Press 2 for the harder path" << endl;
            char keypress = _getch();

            if (keypress == 27) {  // ESC key
                running = false;
                break; // Exit inner while loop
            }

            switch (keypress){
                case '1':
                    path[i] = 0;
                    path_selector = false;
                    break;
                case '2':
                    path[i] = 1;
                    path_selector = false;
                    break;
                default:
                    break;
            }
            clearScreen();
        }
    }

    if(!running){
        cout << "Game ended during setup\n";
        cout << "Press any key to exit";
        _getch();//waits until keypress to exit
        return 0;
    }
    int player[2] = {0}; //initlize player positions
    Board game(players,path);
    int board = game.getBoardSize();  

    while (running){
        for (int b = 0; b < players; b++) {//loop for each player - changes between 0 & 1 for each path/player
            //the display
            running = screen(game, b, board, player, playerData);
            playerData[b].age += 1;
            if (!running) break;
            validatePlayerStats(playerData[b]);
        }  
        last_event = randomEvent(total_events,last_event);
    }

    //ending text
    cout << "Game ended\n";
    cout << "Press any key to exit";
    _getch();//waits until keypress to exit
    return 0;

}