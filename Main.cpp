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
        cout  << tileAction(game, player[current_player], current_player, current_player,  playerData) << endl;
        cout << endl;

        //if pos is farther then board stop
        if (game.getPlayerPosition(current_player) >= board){
            cout << "\nGame over\n";
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

void displayColumn(const vector<string>& lines, int columnIndex) {
    int start = columnIndex * 9;
    int end = min(start + 9, static_cast<int>(lines.size()));

    cout << "Displaying lines " << start + 1 << " to " << end << ":\n";
    for (int i = start; i < end; ++i) {
        cout << lines[i] << endl;
    }
}

bool inlitizeCharcters(playerInfo* playerData, int players){
    // random player data
    // need to make it a class
    //data for charcters
    bool charRunning,running = true;
    fstream characterFile("charcter.txt");
    int selectedLine;
    int keyValue;
    string line;
    vector<string> lines;
    while(getline(characterFile,line)){lines.push_back(line);}
    
    characterFile.close();

    if (lines.size() <= 1) {
        std::cout << "No valid data in the file!" << std::endl;
        return false;
    }

    // Remove the first line (e.g., header or title)
    lines.erase(lines.begin());
    int columnIndex = 0;
    int totalColumns = (lines.size() + 8) / 9; // Calculate total number of columns (round up)
    
    //loop runs each charcter
    for (int i = 0;i<players+1;i++){
        if (!running){
            return false;
        }
        //reset line checker and data relating to certain player
        characterFile.clear();
        characterFile.seekg(0, ios::beg);
        int currentLine = 0;
        columnIndex = 0;
        selectedLine = 0;
        charRunning = true;

        
        while(charRunning == true){
            system("cls");
            displayColumn(lines, columnIndex);
            char keypress = _getch();

            switch (keypress){
                case 'r':
                    selectedLine = rand() % line.size();
                    charRunning = false;
                    break;
                case '1': case '2': case '3': case '4': case '5': 
                case '6': case '7': case '8': case '9':
                    keyValue = keypress - '0';
                    selectedLine = ((columnIndex*9) + (keyValue-1));
                    charRunning = false;
                    break;
                case 77:
                    if (columnIndex < totalColumns - 1){
                        columnIndex++;
                    }
                    break;
                case 75:
                    if (columnIndex >0){
                        columnIndex--;
                    }
                    break;
                case 27:
                    charRunning = false;
                    running = false;
                    break;
                if (!charRunning){
                    break;
                }
            }
        }
        if(!running){return false;}
        if(selectedLine != -1)
        {
            istringstream lineStream(lines[selectedLine]);
            lineStream >> playerData[i].firstName >> playerData[i].lastName >> playerData[i].age 
                        >> playerData[i].strength >> playerData[i].stamina >> playerData[i].wisdom >> playerData[i].points;  
        }
    }
    system("cls");
    return true;
}

void randomEvent(int events){
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

    }
}





int main() {
   
    bool running = true;
    srand(time(0)); //Seed RNG once

    //data/variables
    int players = 1;
    playerInfo playerData[4];
    int total_events = 3;
    if(inlitizeCharcters(playerData, players)){}
    else {running = false;}

    int player[2] = {0}; //initlize player positions
    Board game(players);
    int board = game.getBoardSize();

    game.displayBoard(); //display board

    while (running){
        for (int i = 0; i < board; i++) {//loop for each tile - if get unlucky will reach end
            for (int b = 0; b < players + 1; b++) {//loop for each player - changes between 0 & 1 for each path/player
                //only rolling if space pressed
                cout << "Player: " << b+1 << endl;
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
            randomEvent(total_events);
            if (!running) break;
            
        }

        
    }

    //ending text
    cout << "Game terminated.\n";
    cout << "Press any key to exit";
    _getch();//waits until keypress to end
    return 0;

}