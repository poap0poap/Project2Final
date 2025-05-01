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
#include <iomanip>

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
        if (!viewing){
            switch(rand()%3){
                case 1:
                    playerData[player].strength += 1;
                    playerData[player].stamina += 1;
                    playerData[player].wisdom += 1;
                    break;
                case 2:
                    playerData[player].strength += 2;
                    playerData[player].stamina += 2;
                    playerData[player].wisdom += 2;
                    break;
                default:
                    break;
            }

        }
        return "Basic";
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
        if (!viewing){
            playerData[player].strength += 5;
            playerData[player].stamina += 5;
            playerData[player].wisdom += 5;
            playerData[player].points += (playerData[player].points + 1)/2;
        }
        return "Custom Postive";
        break;
        case 'S':
        return "Start";
        case 'E':
        return "End";
        default:
        return "Exceeded Board Size";
        break;
    }
    return " ";
}

//menu display
void menuDisplay(){
    cout << endl;
    cout << "Press space to roll for turn" << endl;
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

//advisor information
void displayAdvisor(Board& game,int player){
    cout << "Advisor is a work in progress" << endl;
}

void displayLastEvent(int event){
    cout << event << endl;
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
void menuing(Board& game,int current_player,int board, int path, int* player, playerInfo* playerData,char keypress, int last_event){
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
            cout << "You are on a(n) " << tileAction(game,player[current_player],path,true,current_player,playerData) << " tile." << endl;
            break;
        case '5':
            displayLastEvent(last_event);
            break;
    }
}

//picks a random event and returns it for storage
int randomEvent(int events,int last_event){
    if (rand() % 2 == 0){
        pickEvent picker(events);
        int event = picker.getEvent();
        return event;

    }
    return last_event;
}

//creates our display
bool screen(Board& game,int current_player,int board, int* player, playerInfo* playerData,int player_path,int last_event){
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
                menuing(game, current_player , board, player_path, player, playerData, key, last_event);
                break;
        }
        key = _getch();
    }   
}

std::string getCurrentDate()
{
    std::time_t now = std::time(nullptr);
    std::tm tm = *std::localtime(&now);              // copy into tm by value
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();                                // returned by value
}


int main() {
   
    bool running = true;
    srand(time(0)); //Seed RNG once

    //data/variables
    int last_event = 0;
    int players = 2;
    playerInfo playerData[4];
    int total_events = 9;
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
        last_event = randomEvent(total_events,last_event);
        for (int b = 0; b < players; b++) {//loop for each player - changes between 0 & 1 for each path/player
            //the display
            running = screen(game, b, board, player, playerData,path[b],last_event);
            playerData[b].age += 1;
            if (!running) break;
            validatePlayerStats(playerData[b]);
        }  
    }

    //ending text
    std::string today = getCurrentDate();            // pass-by-value
    for (int i = 0; i < players; ++i) {
        playerData[i].datePlayed = today;            // stamp each player
    }

    for (int i = 0; i < players; ++i) {
        // sum up strength, wisdom, and stamina
        int totalStats     = playerData[i].strength
                           + playerData[i].wisdom
                           + playerData[i].stamina;
        // multiply by 10 and add to current wisdom
        int bonusWisdom    = totalStats * 10;
        playerData[i].wisdom += bonusWisdom;
    }
    
    // 2) (Optional) If you want to report the new wisdom value in your file,
    //    you could change the header and print p.wisdom instead of p.points.
    std::ofstream out("PridePoints.txt");
    out << "Pride Points Report — Date: " << today << "\n\n";
    out << std::left << std::setw(22) << "Player"
        << "Wisdom\n"
        << "----------------------\n";
    
    for (int i = 0; i < players; ++i) {
        // no pointers or pass-by-reference here—just direct array access
        out << std::left << std::setw(22)
            << (playerData[i].firstName + " " + playerData[i].lastName)
            << playerData[i].wisdom << "\n";
    }
    
    out.close();
    std::cout << "Saved PridePoints.txt with today's wisdom totals.\n";
}