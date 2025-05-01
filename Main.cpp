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

// //creates our display
// bool screen(Board& game,int current_player,int board, int* player, playerInfo* playerData,int player_path,int last_event){
//     clearScreen();
//     game.displayBoard();
//     cout << "Player: " << current_player+1 << endl;
//     menuDisplay();
//     char key = _getch();
//     while(true){
//         moveCursorToTop();
//         game.displayBoard();
//         cout << "Player: " << current_player+1 << endl;
//         menuDisplay();
//         switch (key){
//             case 27:
//                 return false;
//                 break;
//             case ' ':
//                 return movement(game, current_player , board, player, playerData, 6);
//             default:
//                 menuing(game, current_player , board, player_path, player, playerData, key, last_event);
//                 break;
//         }
//         key = _getch();
//     }   
// }


struct RandomEvent {
    string name;        
    string effects;   
    int advisorID;   
};

struct Advisor{
    string name;
    string effects;
    int advisorID;
};

int main() {
    const int MAX_ADVISORS = 6;
    Advisor advisor[MAX_ADVISORS];
    srand(time(0)); //Seed RNG once
    string output_file_name;
    output_file_name ="game_output";
    output_file_name += ".txt";
    int turn = 0;
   
    bool running = true;
    
    const int MAX_EVENTS = 10;  
    RandomEvent eventData[MAX_EVENTS];
    int selectedLine = 0;
    vector<string> lines;
    ifstream eventFIle("random_events.txt");
    if (!eventFIle) {
        cerr << "Failed to open random_events.txt\n";
    } else {
        string tmp;
        while (getline(eventFIle, tmp)) {
            if (!tmp.empty())
                lines.push_back(tmp);
    }
    eventFIle.close();
}
    for (int n = 0; n<MAX_EVENTS;n++){
        istringstream lineStream(lines[n]);
    
        // 1) read up to first '|'
        string rawName;
        getline(lineStream, rawName, '|');
    
        // 2) read up to second '|'
        string rawEffects;
        getline(lineStream, rawEffects, '|');
    
        // 3) read the rest (the advisor ID)
        string rawAdv;
        getline(lineStream, rawAdv);
        int lessRawAdv = std::stoi(rawAdv);
        eventData[n].name = rawName;
        eventData[n].effects = rawEffects;
        eventData[n].advisorID = lessRawAdv;
    }

    playerInfo playerData[4];
    lines.clear();
    ifstream advisorFile("advisors.txt");
    if (!advisorFile) {
        cerr << "Failed to open advisors.txt\n";
    } else {
        string tmp;
        while (getline(advisorFile, tmp)) {
            if (!tmp.empty())
                lines.push_back(tmp);
    }
    advisorFile.close();
    

    //advisor data inilization
    for (int n = 0; n<MAX_ADVISORS;n++){
        istringstream lineStream(lines[n]);
    
        // 1) read up to first '|'
        string rawName;
        getline(lineStream, rawName, '|');
    
        // 2) read up to second '|'
        string rawDescrip;
        getline(lineStream, rawDescrip);

        advisor[n].name = rawName;
        advisor[n].effects = rawDescrip;
        advisor[n].advisorID = n+1;
    }
    }



    //data/variables
    int last_event = 0;
    const int players = 2;
    int total_events = 10;
    int path[4];
    bool selector;
        // random player data
        //data for charcters
        bool charRunning = true;
        fstream characterFile("charcter.txt");
        int keyValue;
        selectedLine = 0;
        string line;
        lines.clear();
        while(getline(characterFile,line)){lines.push_back(line);}
        characterFile.close();

        if (lines.size() <= 1) {
            cout << "No valid data in the file" << endl;
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
            characterFile.seekg(0, ios::beg);
            int currentLine = 0;
            columnIndex = 0;
            selectedLine = 0;
            charRunning = true;

            
            while(charRunning){
                clearBelowLine(0);
                int start = columnIndex * 9;
                int end = min(start + 9, static_cast<int>(lines.size()));

                cout << "Press esc to quit at any menu\n" << endl;
                cout << "Player " << i+1 << " selection" <<endl;
                cout << "Use left and right arrow keys to navigate pages or press 'R' for random charcter" <<endl;
                cout << "Displaying charcters " << start + 1 << " to " << end << ":\n";
                for (int i = start; i < end; ++i) {
                    stringstream ss(lines[i]);
                    string firstName, lastName;
                    ss >> firstName >> lastName;

                    cout << (i%9)+1 << ". " << firstName << " " << lastName << endl;
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
                        clearScreen();
                    }
                }
                
            }
            if(!running){break;}
            if(selectedLine != -1)
            {
                istringstream lineStream(lines[selectedLine]);
                lineStream >> playerData[i].firstName >> playerData[i].lastName >> playerData[i].age 
                            >> playerData[i].strength >> playerData[i].stamina >> playerData[i].wisdom >> playerData[i].points;
                            playerData[i].advisor.advisorID = 0;
                            playerData[i].advisor.advisorDetails = "No advisor selected";
                            playerData[i].advisor.advisorName = "None";  
            }
        }
        clearScreen();

    //path selctor
    for (int i = 0; i<players; i++){
        if (!running){break;}
        selector = true;
        while(selector){
            if (!running){break;}
            cout << "Which path would player " << i+1 <<" like" <<endl;
            cout << "Press 1 for the harder path" << endl;
            cout << "Press 2 for the easier path" << endl;
            char keypress = _getch();

            if (keypress == 27) {  // ESC key
                running = false;
                break; // Exit inner while loop
            }

            switch (keypress){
                case '1':
                    path[i] = 0;
                    selector = false;
                    break;
                case '2':
                    path[i] = 1;
                    playerData[i].points-=10;
                    selector = false;
                    break;
                default:
                    break;
            }
            clearScreen();
        }
    }

    //advisor selectors
    for (int i = 0; i<players;i++){
        selector = true;
        if (path[i]==1){
            while (selector){
                cout << "Player " << i+1  << " select advisor:" << endl;
                for (int o = 0; o < MAX_ADVISORS; o++){
                    cout << o+1 << ". " << advisor[o].name << endl; 
                }
                char keypress = _getch();
                switch (keypress){
                    case '1':
                    playerData[i].advisor.advisorID = advisor[0].advisorID;
                    playerData[i].advisor.advisorName = advisor[0].name;
                    playerData[i].advisor.advisorDetails = advisor[0].effects;
                    selector = false;
                    break;
                    case '2':
                    playerData[i].advisor.advisorID = advisor[1].advisorID;
                    playerData[i].advisor.advisorName = advisor[1].name;
                    playerData[i].advisor.advisorDetails = advisor[1].effects;
                    selector = false;
                    break;
                    case '3':
                    playerData[i].advisor.advisorID = advisor[2].advisorID;
                    playerData[i].advisor.advisorName = advisor[2].name;
                    playerData[i].advisor.advisorDetails = advisor[2].effects;
                    selector = false;
                    break;
                    case '4':
                    playerData[i].advisor.advisorID = advisor[3].advisorID;
                    playerData[i].advisor.advisorName = advisor[3].name;
                    playerData[i].advisor.advisorDetails = advisor[3].effects;
                    selector = false;
                    break;
                    case '5':
                    playerData[i].advisor.advisorID = advisor[4].advisorID;
                    playerData[i].advisor.advisorName = advisor[4].name;
                    playerData[i].advisor.advisorDetails = advisor[4].effects;
                    selector = false;
                    break;
                    case '6':
                    playerData[i].advisor.advisorID = advisor[5].advisorID;
                    playerData[i].advisor.advisorName = advisor[5].name;
                    playerData[i].advisor.advisorDetails = advisor[5].effects;
                    selector = false;
                    break;
                    case 27:
                    running = false;
                    selector = false;
                    break;
                    default:
                        break;
                }
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
        if (!running)break;
        
        //save to file
        ofstream outputFile(output_file_name);
        turn++;
        outputFile<<"Turn: " << turn <<"\n";
        for (int i = 0; i < players; i++) {
            outputFile<<"Player " << i+1 << " stats: " << "\nName: " << playerData[i].firstName << " " << playerData[i].lastName <<"\nStrength: " << playerData[i].strength<<"\nStamina: "<< playerData[i].stamina<<"\nWisdom: "<< playerData[i].wisdom<<"\nPoints: "<< playerData[i].points<<"\nAge: "<< playerData[i].age<< "\n\n";
        }
        outputFile.close();

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
                cout << "Current Event: " << eventData[last_event].name << endl;
                // cout << eventData[last_event].advisorID << endl;
                // cout << last_event << endl;
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
                                    playerData[b].stamina-=2;
                                break;
                            case 'R':
                                    playerData[b].points -= (playerData[b].points+1)/2;
                                    playerData[b].strength-=5;
                                    playerData[b].stamina-=5;
                                    playerData[b].wisdom-=5;
                                break;
                            case 'C':
                                    playerData[b].points += (playerData[b].points+1)/2;
                                    playerData[b].strength+=5   ;
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
                            case '3':
                                cout << "Advisor: " << playerData[b].advisor.advisorName << endl;
                                cout << playerData[b].advisor.advisorDetails << endl;
                                break;
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
                                            output = "advisor change - non functional";
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
                                cout << eventData[last_event].effects << endl; 
                                break;
                        }
                        break;
                }
            }   
                playerData[b].age += 1;
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
        last_event = randomEvent(total_events,last_event);
        for (int i = 0; i<players; i++){
            if (playerData[i].advisor.advisorID == eventData[last_event].advisorID){}
            else{
                switch (last_event){
                    case 1:
                        playerData[i].stamina -=2;
                        break;
                    case 2:
                        playerData[i].strength -=2;
                        break;
                    case 3:
                        playerData[i].wisdom -=2;
                        break;
                    case 4:
                        playerData[i].strength -=2;
                        playerData[i].stamina -=2;
                        playerData[i].wisdom -=2;
                        break;
                    case 5:
                        playerData[i].stamina -=3;
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    case 8:
                        playerData[i].wisdom -=5;
                        break;
                    case 9:
                        playerData[i].wisdom -=2;
                        break;
                    default:
                        break;
                }  
            }
                playerData[i].age += 1;
                if (!running) break;
                if (playerData[i].strength <= 0) {
                    playerData[i].strength = 0;
                }
                if (playerData[i].stamina <= 0) {
                    playerData[i].stamina = 0;
                }
                if (playerData[i].wisdom <= 0) {
                    playerData[i].wisdom = 0;
                }
                if (playerData[i].points < 0) {
                    playerData[i].points = 0;
                }
            
        }
        outputFile<<"Turn: " << turn <<"\n";
        for (int i = 0; i < players; i++) {
            outputFile<<"Player " << i+1 << " stats: " << "\nName: " << playerData[i].firstName << " " << playerData[i].lastName <<"\nStrength: " << playerData[i].strength<<"\nStamina: "<< playerData[i].stamina<<"\nWisdom: "<< playerData[i].wisdom<<"\nPoints: "<< playerData[i].points<<"\nAge: "<< playerData[i].age<< "\n\n";
        }
        outputFile.close();
    }


    clearScreen();


    
    int playerDataFinal[players] = {0};

    for (int i = 0; i < players; i++) {
        // sum up strength, wisdom, and stamina
        playerDataFinal[i] += playerData[i].strength+1;
        playerDataFinal[i] += playerData[i].wisdom;
        playerDataFinal[i] += playerData[i].stamina;
        playerDataFinal[i] += playerData[i].points;
    }


    int winner = 0;
    for (int i = 1; i < players; i++){
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
