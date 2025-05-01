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
#include "PlayerInfo.h"
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

// //check for what tile you are on and applys effects
// string tileAction(Board& game, int player_position, int player_path, bool viewing, int player, playerInfo* playerData)
// {
//     char p = game.getTileIndex(player_path,player_position);// find landed tile using chosen path and current position
//     //describes events based on landed tile
//     switch(p){
//         case 'B':
//         if (!viewing){
//             switch(rand()%3){
//                 case 1:
//                     playerData[player].strength += 1;
//                     playerData[player].stamina += 1;
//                     playerData[player].wisdom += 1;
//                     break;
//                 case 2:
//                     playerData[player].strength += 2;
//                     playerData[player].stamina += 2;
//                     playerData[player].wisdom += 2;
//                     break;
//                 default:
//                     break;
//             }

//         }
//         return "Basic";
//         break;
//         case 'Y':
//         return "advisor change";
//         break;
//         case 'P':
//         return "riddle";
//         break;
//         case 'L':
//         if (!viewing){
//             playerData[player].strength += 2;
//             playerData[player].stamina += 2;
//             playerData[player].wisdom += 2;
//         }
//         return "+2 to stats";
//         break;
//         case 'I':
//         if (!viewing){
//             playerData[player].strength += 3;
//             playerData[player].stamina += 3;
//             playerData[player].wisdom += 3;
//         }
//         return "+3 to stats";
//         break;
//         case 'G':
//         if (!viewing){
//             playerData[player].strength -= 1;
//             playerData[player].stamina -= 1;
//             playerData[player].wisdom -= 1;
//         }
//         return "Graveyard";
//         break;
//         case 'O':
//         if (!viewing){
//             playerData[player].stamina -= 5;
//         }
//         return "Hyena";
//         break;
//         case 'R':
//         if (!viewing){
//             playerData[player].strength -= 5;
//             playerData[player].stamina -= 5;
//             playerData[player].wisdom -= 5;
//             playerData[player].points = (playerData[player].points + 1)/2;
//         }
//         return "Custom negitive";
//         break;
//         case 'C':
//         if (!viewing){
//             playerData[player].strength += 5;
//             playerData[player].stamina += 5;
//             playerData[player].wisdom += 5;
//             playerData[player].points += (playerData[player].points + 1)/2;
//         }
//         return "Custom Postive";
//         break;
//         case 'S':
//         return "Start";
//         case 'E':
//         return "End";
//         default:
//         return "Exceeded Board Size";
//         break;
//     }
//     return " ";
// }

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
// void displayStats(Board& game,int player,playerInfo* playerData){
//     cout << "Strength: " << playerData[player].strength << endl;
//     cout << "Stamina: " << playerData[player].stamina << endl;
//     cout << "Wisdom: " << playerData[player].wisdom << endl;
//     cout << "Points: " << playerData[player].points << endl;
// }

// //charcter inforemation
// void charInfo(Board& game,int player, playerInfo* playerData){
//     cout << "Name: " << playerData[player].firstName << " " << playerData[player].lastName << endl;
//     cout << "Age: " << playerData[player].age << endl;
// }

//advisor information
// void displayAdvisor(Board& game,int player){
//     cout << "Advisor is a work in progress" << endl;
// }

// void displayLastEvent(int event){
//     cout << event << endl;
// }

// //Movement
// bool movement(Board& game,int current_player,int board, int* player, playerInfo* playerData,int diceSize){
//     int dice = diceRoll(diceSize);
//     game.movePlayer(current_player, dice);
//     //move player current_playerased on dice
//     player[current_player] += dice;
//     //cout  << tileAction(game, player[current_player], current_player, false, current_player,playerData) << endl;
//     //cout << endl;

//     //if pos is farther then board stop
//     if (game.getPlayerPosition(current_player) >= board){
//         cout << "\nGame over\n";
//         return false;
//     }
//     else{
//         return true;
//     }
// }

// //menuing
// void menuing(Board& game,int current_player,int board, int path, int* player, playerInfo* playerData,char keypress, int last_event){
//     clearBelowLine(17); 
//     tile action ={}
//     switch(keypress){
//         case '1':
//             displayStats(game, current_player,playerData);
//             break;
//         case '2':
//             charInfo(game, current_player, playerData);
//             break;
//         case '3':
//             displayAdvisor(game, current_player);
//             break;
//         case '4':
//             cout << "You are on a(n) " << tileAction(game,player[current_player],path,true,current_player,playerData) << " tile." << endl;
//             break;
//         case '5':
//             displayLastEvent(last_event);
//             break;
//     }
// }

//picks a random event and returns it for storage
int randomEvent(int events,int last_event){
    if (rand() % 2 == 0){
        pickEvent picker(events);
        int event = picker.getEvent();
        return event;

    }
    return last_event;
}

std::vector<Advisor> loadAdvisors(std::string filename) {
    std::vector<Advisor> list;
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Failed to open advisors.txt\n";
        return list;               // return empty list on failure
    }

    std::string line;
    // skip the first line:
    std::getline(in, line);

    // now read the rest into 'list':
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        list.push_back({ line });
    }

    return list;                   // return the filled list
}

Advisor chooseAdvisor(std::vector<Advisor> all) {
    std::cout << "Choose your advisor:\n";
    for (size_t i = 0; i < all.size(); ++i)
        std::cout << "  " << (i+1) << ") " << all[i].name << "\n";

    int choice;
    while (true) {
        std::cout << "Enter the number of your advisor: ";
        std::cin >> choice;
        if (choice >= 1 && choice <= (int)all.size())
            return all[choice - 1];
        std::cout << "Invalid choice, please try again.\n";
    }
}

int main() {

    srand(time(0)); //Seed RNG once
    string output_file_name;
    output_file_name ="game_output";
    output_file_name += ".txt";
    int turn = 0;
    auto allAdvisors = loadAdvisors("advisors.txt");
    bool running = true;
    

    //data/variables
    int last_event = 0;
    const int players = 2;
    playerInfo playerData[4];
    int total_events = 9;
    int path[4];
    bool path_selector;
        // random player data
        //data for charcters
        bool charRunning = true;
        std::fstream characterFile("charcter.txt");
        int selectedLine, keyValue;
        std::string line;
        std::vector<std::string> lines;
        while(getline(characterFile,line)){lines.push_back(line);}
        characterFile.close();

        if (lines.size() <= 1) {
            std::cout << "No valid data in the file" << std::endl;
            running = false;
        }

        // Remove the first line (e.g., header or title)
        lines.erase(lines.begin());
        int columnIndex = 0;
        int totalColumns = (lines.size() + 8) / 9; // Calculate total number of columns (round up)
        
        //loop runs each charcter
        for (int i = 0;i<players;i++){
            if (!running){
                running = false;
            }
            //reset line checker and data relating to certain player
            characterFile.clear();
            characterFile.seekg(0, std::ios::beg);
            int currentLine = 0;
            columnIndex = 0;
            selectedLine = 0;
            charRunning = true;

            
            while(charRunning){
                clearBelowLine(0);
                int start = columnIndex * 9;
                int end = std::min(start + 9, static_cast<int>(lines.size()));

                std::cout << "Press esc to quit at any menu\n" << std::endl;
                std::cout << "Player " << i+1 << " selection" <<std::endl;
                std::cout << "Use left and right arrow keys to navigate pages or press 'R' for random charcter" <<std::endl;
                std::cout << "Displaying charcters " << start + 1 << " to " << end << ":\n";
                for (int i = start; i < end; ++i) {
                    std::stringstream ss(lines[i]);
                    std::string firstName, lastName;
                    ss >> firstName >> lastName;

                    std::cout << (i%9)+1 << ". " << firstName << " " << lastName << std::endl;
                }
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
                        std::stringstream ss(lines[selectedLine]);
                        std::string firstName, lastName, age , str, sta, wis, points;
                        ss >> firstName >> lastName >> age>>str>>sta>>wis>>points;
                        std::cout << "You picked " << firstName << " " << lastName << "\n" << "They are " << age <<" turns old"<< std::endl;
                        std::cout << "Their starting strength is " << str <<std::endl;
                        std::cout << "Their starting stamina is " << sta <<std::endl;
                        std::cout << "Their starting wisdom is " << wis <<std::endl;
                        std::cout << "Their starting points are " << points <<std::endl;
                        std::cout <<"Press Enter to confirm or any other to reselect"<< std::endl;
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
                        clearScreen();
                    }
                }
                
            }
            if(!running){break;}
            if(selectedLine != -1)
            {
                std::istringstream lineStream(lines[selectedLine]);
                lineStream >> playerData[i].firstName >> playerData[i].lastName >> playerData[i].age 
                            >> playerData[i].strength >> playerData[i].stamina >> playerData[i].wisdom >> playerData[i].points;  
            }
        }
        clearScreen();

    //path selctor
    for (int i = 0; i<players; i++){
        if (!running){break;}
        path_selector = true;
        while(path_selector){
            if (!running){break;}
            cout << "Which path would player " << i+1 <<" like" <<endl;
            cout << "Press 1 for the Easier path" << endl;
            cout << "Press 2 for the Harder path" << endl;
            char keypress = _getch();

            if (keypress == 27) {  // ESC key
                running = false;
                break; // Exit inner while loop
            }

            switch (keypress){
                case '1':
                    path[i] = 0;
                    path_selector = false;
                    playerData[i].advisor = chooseAdvisor(allAdvisors);
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
        clearScreen();
        cout << "Game ended during setup\n";
        cout << "Press any key to exit";
        _getch();
        return 0;
    }
    // int player[2] = {0}; //initlize player positions
    Board game(players,path);
    int board = game.getBoardSize();  

    string output;
    int out;
    bool z,t;
    int diceSize = 6;
    int player_position, dice;
    int winning = 0;
    

    while (running){
        winning = 0;
        for (int i = 0;i<players; i++){
            if (game.getPlayerPosition(i)+1==board){
                winning++;
            }
            if (winning == players){
                running = false;
                z=false;
                break;
            }
        }
        if (!running){break;}
        
        //save to file
        ofstream outputFile(output_file_name);
        turn++;
        outputFile<<"Turn: " << turn <<"\n";
        for (int i = 0; i < players; i++) {
            outputFile<<"Player " << i+1 << " stats: " << "\nName: " << playerData[i].firstName << " " << playerData[i].lastName <<"\nStrength: " << playerData[i].strength<<"\nStamina: "<< playerData[i].stamina<<"\nWisdom: "<< playerData[i].wisdom<<"\nPoints: "<< playerData[i].points<<"\nAge: "<< playerData[i].age<< "\n\n";
        }
        outputFile.close();


        last_event = randomEvent(total_events,last_event);
        for (int b = 0; b < players; b++) {//loop for each player - changes between 0 & 1 for each path/player
            player_position = game.getPlayerPosition(b);
            //the display
            clearScreen();
            char key;
            z = true;
            while(z){
                moveCursorToTop();
                game.displayBoard();
                cout << "Player: " << b+1 << endl;
                cout << "Current Event: " << last_event << endl;
                cout << winning << endl;
                menuDisplay();
                key = _getch();
                switch (key){
                    case 27:{
                        running = false;
                        z = false;
                        break;
                    }
                    case ' ':{
                        dice = diceRoll(diceSize);
                        if (game.getPlayerPosition(b)+dice >= board){
                            dice = board-game.getPlayerPosition(b)-1;
                        }
                        else{
                            
                            // player[b] += dice;
                        }
                    game.movePlayer(b, dice);
                    player_position = game.getPlayerPosition(b);
                        char p = game.getTileIndex(path[b],player_position);
                        switch(p){
                            case 'B':{
                                int basic = rand()%3;
                                switch(basic){
                                    case 1:
                                        playerData[b].strength++;
                                        playerData[b].stamina++;
                                        playerData[b].wisdom++;
                                        break;
                                    case 2:
                                        playerData[b].strength+=2;
                                        playerData[b].stamina+=2;
                                        playerData[b].wisdom+=2;
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            }
                            case 'Y':
                                break;
                            case 'P':
                                break;
                            case 'L':
                                    playerData[b].strength+=2;
                                    playerData[b].stamina+=2;
                                    playerData[b].wisdom+=2;
                                break;
                            case 'I':
                                    playerData[b].strength+=3;
                                    playerData[b].stamina+=3;
                                    playerData[b].wisdom+=3;
                                break;
                            case 'G':
                                    if (game.getPlayerPosition(b)>=10){
                                    game.movePlayer(b,-10);
                                    }
                                    else{
                                        game.movePlayer(b,-dice+1);
                                    }
                                    playerData[b].strength-=1;
                                    playerData[b].stamina-=1;
                                    playerData[b].wisdom-=1;
                                break;
                            case 'O':
                                    game.movePlayer(b,-dice);
                                    playerData[b].stamina-=3;
                                break;
                            case 'R':
                                    playerData[b].points -= (playerData[b].points+1)/2;
                                    playerData[b].strength-=5;
                                    playerData[b].stamina-=5;
                                    playerData[b].wisdom-=5;
                                break;
                            case 'C':
                                    playerData[b].points += (playerData[b].points+1)/2;
                                    playerData[b].strength+=5;
                                    playerData[b].stamina+=5;
                                    playerData[b].wisdom+=5;
                                break;
                            case 'S':
                                break;
                            case 'E':
                                break;
                            default:
                                break;
                            }
                        
                        //move player current_playerased on dice
                        
                        //cout  << tileAction(game, player[current_player], current_player, false, current_player,playerData) << endl;
                        //cout << endl;
                    
                        //if pos is farther then board stop
                        z = false;
                        running = true;
                        break;
                    }
                    default:
                        clearBelowLine(18); 
                        switch(key){
                            case '1':
                                cout << "Strength: " << playerData[b].strength << endl;
                                cout << "Stamina: " << playerData[b].stamina << endl;
                                cout << "Wisdom: " << playerData[b].wisdom << endl;
                                cout << "Points: " << playerData[b].points << endl;
                                break;
                            case '2':
                                cout << "Name: " << playerData[b].firstName << " " << playerData[b].lastName << endl;
                                cout << "Age: " << playerData[b].age << endl;
                                break;
                            case '3': {
                            std::string full = playerData[b].advisor.name;      // e.g. "Talon | …"
                            auto pos = full.find('|');
                            std::string nameOnly = (pos == std::string::npos)
                                                   ? full
                                                   : full.substr(0, pos);
                            if (!nameOnly.empty() && nameOnly.back()==' ')
                              nameOnly.pop_back();
                            
                            cout << "Player " << b+1 << "'s advisor is " << nameOnly << "." << endl;
                                break;
                            }
                            case '4':{
                                t = true;
                                while(t){
                                    char p = game.getTileIndex(path[b],player_position);// find landed tile using chosen path and current position
                                    //describes events based on landed tile
                                    switch(p){
                                        case 'B':
                                            output = "Basic";
                                            t=false;
                                            break;
                                        case 'Y':
                                            output = "advisor change";
                                            t=false;
                                            break;
                                        case 'P':
                                            output = "riddle";
                                            t=false;
                                            break;
                                        case 'L':
                                            output = "+2 to stats";
                                            t=false;
                                            break;
                                        case 'I':
                                            output = "+3 to stats";
                                            t=false;
                                            break;
                                        case 'G':
                                            output = "Graveyard";
                                            t=false;
                                            break;
                                        case 'O':
                                            output = "Hyena";
                                            t=false;
                                            break;
                                        case 'R':
                                            output = "Custom negitive";
                                            t=false;
                                            break;
                                        case 'C':
                                            output = "Custom Postive";
                                            t=false;
                                            break;
                                        case 'S':
                                            output = "Start";
                                            // output = "Start";
                                            t=false;
                                            break;
                                        case 'E':
                                            output = "End";
                                            t=false;
                                            break;
                                        default:
                                            output = game.getPlayerPosition(p);
                                            t=false;
                                            break;
                                    }
                                }
                                cout << "You are on a(n) " << output << " tile." << endl;
                                break;
                            }
                            case '5':
                                cout << last_event << endl; 
                                break;
                        }
                        break;
                }
            }   
            if (!(game.getPlayerPosition(b)>=board)){
            playerData[b].age += 1;
            }
            if (!running) break;
            if (playerData[b].strength <= 0) {
                playerData[b].strength = 0;
            }
            if (playerData[b].stamina <= 0) {
                playerData[b].stamina = 0;
            }
            if (playerData[b].wisdom <= 0) {
                playerData[b].wisdom = 0;
            }
            if (playerData[b].points < 0) {
                playerData[b].points = 0;
                if (playerData[b].strength != 0) {
                    playerData[b].strength--;
                }
                if (playerData[b].stamina != 0) {
                    playerData[b].stamina--;
                }
                if (playerData[b].wisdom != 0) {
                    playerData[b].wisdom--;
                }
            }
            
        }  
    }


    clearScreen();

    int playerDataFinal[players];

    for (int i = 0; i < players; ++i) {
        // sum up strength, wisdom, and stamina
        int totalStats = playerData[i].strength
                       + playerData[i].wisdom
                       + playerData[i].stamina;
        // multiply by 10 and add to current wisdom
        int bonusPoints = totalStats * 1;
        playerDataFinal[i] += bonusPoints;
    }

    // For each position i, find the max in [i..end) and swap into i
    for (int i = 0; i < players; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < players; ++j) {
            if (playerDataFinal[j] > playerDataFinal[maxIdx]) {
                maxIdx = j; 
            }
        }
        if (maxIdx != i) {
            int tmp          = playerDataFinal[i];
            playerDataFinal[i]           = playerDataFinal[maxIdx];
            playerDataFinal[maxIdx]      = tmp;
        }
    }


        int winner = 0;
        for (int i = 0; i < players; i++){
            if (playerDataFinal[i]>playerDataFinal[i-1]){
                winner = i;
            }
        }

    if (winning == players){
        game.displayBoard();
        cout << "Player " << winner+1 << " won." << endl;
        cout << "They had " << playerDataFinal[winner] << " points." << endl;

        _getch();
    }
    else{
        cout << "Game ended\n";
        cout << "Press any key to exit";
        _getch();//waits until keypress to exit
    }
    return 0;

}