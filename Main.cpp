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

using namespace std;

//rolling dice. any size - determned by int value
int diceRoll(int dice_size){
    return 1 + rand() % dice_size;
}

void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // Clear screen and move cursor to top-left
}


void moveCursorToTop() {
    std::cout << "\033[H"; // Move cursor to top-left only
}

void clearBelowLine(int line) {
    // Move cursor to specified line (line starts from 1)
    std::cout << "\033[" << line << ";1H";
    // Clear everything from cursor to end of screen
    std::cout << "\033[J";
}

//will go to player.cpp
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

//diplay the column of names to select
void displayColumn(const vector<string>& lines, int columnIndex,int player) {
    int start = columnIndex * 9;
    int end = min(start + 9, static_cast<int>(lines.size()));

    cout << "Press esc to quit at any menu\n" << endl;
    cout << "Player " << player+1 << " selection" <<endl;
    cout << "Use left and right arrow keys to navigate pages or press 'R' for random charcter" <<endl;
    cout << "Displaying charcters " << start + 1 << " to " << end << ":\n";
    for (int i = start; i < end; ++i) {
        stringstream ss(lines[i]);
        string firstName, lastName;
        ss >> firstName >> lastName;

        cout << (i%9)+1 << ". " << firstName << " " << lastName << endl;
    }
}



//Move to player.cpp
//charcter selection
bool inlitizeCharcters(playerInfo* playerData, int total_players){
    // random player data
    //data for charcters
    bool charRunning,running = true;
    fstream characterFile("charcter.txt");
    int selectedLine, keyValue;
    string line;
    vector<string> lines;
    while(getline(characterFile,line)){lines.push_back(line);}
    characterFile.close();

    if (lines.size() <= 1) {
        cout << "No valid data in the file!" << endl;
        return false;
    }

    // Remove the first line (e.g., header or title)
    lines.erase(lines.begin());
    int columnIndex = 0;
    int totalColumns = (lines.size() + 8) / 9; // Calculate total number of columns (round up)
    
    //loop runs each charcter
    for (int i = 0;i<total_players;i++){
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

        
        while(charRunning){
            clearBelowLine(0);
            displayColumn(lines, columnIndex,i);
            char keypress = _getch();
            //if arrow keys are buggin check to see if the int is not represented in this list
            //cout << (int)keypress << endl;
            if (keypress == -32){
                keypress = _getch();
                switch(keypress){
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
                }
            }
            else{
                //cout << keypress << endl;
                // uses the pressed key to select option
                switch (keypress){
                    case 'r':
                        selectedLine = rand() % lines.size();
                        break;
                    case '1': case '2': case '3': case '4': case '5': 
                    case '6': case '7': case '8': case '9':
                        keyValue = keypress - '0';
                        selectedLine = ((columnIndex*9) + (keyValue-1));
                        break;
                    case 27:
                        charRunning = false;
                        running = false;
                        break;
                    if (!charRunning){
                        break;
                    }
                }
                if (selectedLine != -1){
                    if (!running){break;}
                    clearScreen();
                    stringstream ss(lines[selectedLine]);
                    string firstName, lastName, age , str, sta, wis, points;
                    ss >> firstName >> lastName >> age>>str>>sta>>wis>>points;
                    cout << "You picked " << firstName << " " << lastName << "\n" << "They are " << age <<" turns old"<< endl;
                    cout << "Their starting strength is " << str <<endl;
                    cout << "Their starting stamina is " << sta <<endl;
                    cout << "Their starting wisdom is " << wis <<endl;
                    cout << "Their starting points are " << points <<endl;
                    cout <<"Press Enter to confirm or any other to reselect"<< endl;
                    int press = _getch();
                    switch(press){
                        case 13://enter
                            charRunning = false;
                            break;
                        case 27:
                            charRunning = false;    
                            running = false;
                            break;
                        default:
                            selectedLine = -1;
                            charRunning = true;
                            break;
                    }
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
    clearScreen();
    return true;
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

//move to player.cpp
void validatePlayerStats(playerInfo& player) {
    if (player.strength < 0) {
        player.strength = 0;
    }
    if (player.stamina < 0) {
        player.stamina = 0;
    }
    if (player.wisdom < 0) {
        player.wisdom = 0;
    }
    if (player.points < 0) {
        player.points = 0;
        if (player.strength != 0) {
            player.strength--;
        }
        if (player.stamina != 0) {
            player.stamina--;
        }
        if (player.wisdom != 0) {
            player.wisdom--;
        }
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