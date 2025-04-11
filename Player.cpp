#include "Player.h"
#include "PlayerInfo.h"
#include "Utility.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <conio.h> // to get the keypress using _getch()


//diplay the column of names to select
void displayColumn(const std::vector<std::string>& lines, int columnIndex,int player) {
    int start = columnIndex * 9;
    int end = std::min(start + 9, static_cast<int>(lines.size()));

    std::cout << "Press esc to quit at any menu\n" << std::endl;
    std::cout << "Player " << player+1 << " selection" <<std::endl;
    std::cout << "Use left and right arrow keys to navigate pages or press 'R' for random charcter" <<std::endl;
    std::cout << "Displaying charcters " << start + 1 << " to " << end << ":\n";
    for (int i = start; i < end; ++i) {
        std::stringstream ss(lines[i]);
        std::string firstName, lastName;
        ss >> firstName >> lastName;

        std::cout << (i%9)+1 << ". " << firstName << " " << lastName << std::endl;
    }
}

bool inlitizeCharcters(playerInfo* playerData, int total_players){
    // random player data
    //data for charcters
    bool charRunning,running = true;
    std::fstream characterFile("charcter.txt");
    int selectedLine, keyValue;
    std::string line;
    std::vector<std::string> lines;
    while(getline(characterFile,line)){lines.push_back(line);}
    characterFile.close();

    if (lines.size() <= 1) {
        std::cout << "No valid data in the file" << std::endl;
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
        characterFile.seekg(0, std::ios::beg);
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
        if(!running){return false;}
        if(selectedLine != -1)
        {
            std::istringstream lineStream(lines[selectedLine]);
            lineStream >> playerData[i].firstName >> playerData[i].lastName >> playerData[i].age 
                        >> playerData[i].strength >> playerData[i].stamina >> playerData[i].wisdom >> playerData[i].points;  
        }
    }
    clearScreen();
    return true;
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

void displayAdvisor(int player_index){

}