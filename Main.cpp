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


//picks a random event and returns it for storage
int randomEvent(int events,int last_event){
    if (rand() % 2 == 0){
        pickEvent picker(events);
        int event = picker.getEvent();
        return event;

    }
    return last_event;
}


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

struct Riddle{
    string question;
    string answer;
};

int main() {
    const int MAX_RIDDLES = 5;
    const int MAX_ADVISORS = 6;
    Riddle riddle[MAX_RIDDLES];
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
    lines.clear();

    ifstream riddleFile("riddles.txt");
    if (!riddleFile){
        cerr << "Unable to open riddles.txt\n";
    }
    else{
        string tmp;
        while (getline(riddleFile, tmp)) {
            if (!tmp.empty())
                lines.push_back(tmp);
        }
    }
    riddleFile.close();

    for (int i = 0; i < MAX_RIDDLES;i++){
        istringstream lineStream(lines[i]);
    
        // 1) read up to first '|'
        string rawQuestion;
        getline(lineStream, rawQuestion, '|');
    
        // 2) read up to end
        string rawAnswer;
        getline(lineStream, rawAnswer);

        riddle[i].question = rawQuestion;
        riddle[i].answer = rawAnswer;
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
                    playerData[i].age +=10;
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
                            case 'Y':{
                                bool advisorChange = true;
                                while (advisorChange){  
                                    clearScreen();
                                    cout << "Player " << b+1 << ", You have stumbled across a training camp.\nYou may now choose a new advisor.\n";
                                    for (int o = 0; o < MAX_ADVISORS; o++){
                                        cout << o+1 << ". " << advisor[o].name << endl; 
                                    }
                                    char keypress = _getch();
                                    switch (keypress){
                                        case '1':
                                        playerData[b].advisor.advisorID = advisor[0].advisorID;
                                        playerData[b].advisor.advisorName = advisor[0].name;
                                        playerData[b].advisor.advisorDetails = advisor[0].effects;
                                        advisorChange = false;
                                        break;
                                        case '2':
                                        playerData[b].advisor.advisorID = advisor[1].advisorID;
                                        playerData[b].advisor.advisorName = advisor[1].name;
                                        playerData[b].advisor.advisorDetails = advisor[1].effects;
                                        advisorChange = false;
                                        break;
                                        case '3':
                                        playerData[b].advisor.advisorID = advisor[2].advisorID;
                                        playerData[b].advisor.advisorName = advisor[2].name;
                                        playerData[b].advisor.advisorDetails = advisor[2].effects;
                                        advisorChange = false;
                                        break;
                                        case '4':
                                        playerData[b].advisor.advisorID = advisor[3].advisorID;
                                        playerData[b].advisor.advisorName = advisor[3].name;
                                        playerData[b].advisor.advisorDetails = advisor[3].effects;
                                        advisorChange = false;
                                        break;
                                        case '5':
                                        playerData[b].advisor.advisorID = advisor[4].advisorID;
                                        playerData[b].advisor.advisorName = advisor[4].name;
                                        playerData[b].advisor.advisorDetails = advisor[4].effects;
                                        advisorChange = false;
                                        break;
                                        case '6':
                                        playerData[b].advisor.advisorID = advisor[5].advisorID;
                                        playerData[b].advisor.advisorName = advisor[5].name;
                                        playerData[b].advisor.advisorDetails = advisor[5].effects;
                                        advisorChange = false;
                                        break;
                                        case 27:
                                        running = false;
                                        advisorChange = false;
                                        break;
                                        default:
                                            break;
                                    }
                                }
                                break;
                                }
                            case 'P':{
                                bool riddleRunning = true;
                                int randomRiddle = rand()%MAX_RIDDLES;
                                string riddleAns;
                                while (riddleRunning){  
                                    clearScreen();
                                    cout << "Player " << b+1 << ", You have stumbled across some ancient ruins.\nPlease answer carfully.\n";
                                    cout << riddle[randomRiddle].question << endl;
                                    cin >> riddleAns;

                                    if (riddleAns == riddle[randomRiddle].answer){
                                        riddleRunning = false;
                                        cout << "You got it right!" << endl;
                                        cout << riddleAns <<" is the correct answer to this riddle\n";
                                        playerData[b].wisdom +=10;
                                        playerData[b].points +=10;
                                    }
                                    else{
                                        cout << "Oh No, You got it wrong." << endl;
                                        cout << riddleAns << " is not the answer to this riddle.\n";
                                        cout << "Please try again next time\n";
                                        riddleRunning = false;
                                        playerData[b].wisdom -=10;
                                        playerData[b].points -=10;
                                    }
                                    cout << "\nPress any key to continue" << endl;
                                    _getch();
                                }
                                break;
                                }
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
                                            output = "Advisor change";
                                            t=false;
                                            break;
                                        case 'P':
                                            output = "Riddle";
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
                                            if (path[b]){output = "Poaching";}
                                            else{output = "Pitfall";}
                                            t=false;
                                            break;
                                        case 'C':
                                        if (path[b]){output = "Ancient hunting ground";}
                                        else{output = "Village";}
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
        if (game.getPlayerPosition(0) == game.getPlayerPosition(1)&&path[0]==path[1]){
            clearScreen();
            cout << "A fight broke out" << endl;
            if (playerData[0].strength>playerData[1].strength){
                playerData[0].points +=10;
                playerData[1].points -=10;
                cout << "Player 1 defeated Player 2 and stole 10 points" << endl;
            }
            else {
                playerData[1].points +=10;
                playerData[0].points -=10;
                cout << "Player 2 defeated Player 1 and stole 10 points" << endl;
            }
            cout << "Press anykey to continue." << endl;
            _getch();
        }
        outputFile<<"Turn: " << turn <<"\n";
        for (int i = 0; i < players; i++) {
            outputFile<<"Player " << i+1 << " stats: " << "\nName: " << playerData[i].firstName << " " << playerData[i].lastName <<"\nStrength: " << playerData[i].strength<<"\nStamina: "<< playerData[i].stamina<<"\nWisdom: "<< playerData[i].wisdom<<"\nPoints: "<< playerData[i].points<<"\nAge: "<< playerData[i].age<< "\n\n";
        }
        outputFile.close();
    }


    clearScreen();


    
    int playerDataFinal[players] = {1};

    for (int i = 0; i < players; i++) {
        // sum up strength, wisdom, and stamina
        playerDataFinal[i] += playerData[i].strength;
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
