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

//Rolling dice. any size - determned by int value
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

void displayStats(Board& game,int player,playerInfo* playerData){
    cout << "Strength: " << playerData[player].strength << endl;
    cout << "Stamina: " << playerData[player].stamina << endl;
    cout << "Wisdom: " << playerData[player].wisdom << endl;
    cout << "Points: " << playerData[player].points << endl;
}
void displayMenu(){
    cout << "--- Cub Leveling ---\n";
    cout << "1. Player Stats\n";
    cout << "2. Character Information\n";
    cout << "3. Display Board\n";
    cout << "4. Display Advisor\n";
    cout << "5. Take your turn\n";
    cout << "6. Exit Game\n";
    cout << "Please select an option (1 - 6)." << endl;

}

int main(){
    int choice;
    int players = 0;
    int ready = 0;

    cout << "How many players are there? (2-4)" << endl;
    cin >> players;

    if (players < 2 || players > 4){
        cout << "Invalid ammount of players. Please choose a number between 2 to 4." << endl;
    }    else {
        cout << "There are " << players << " Players.\n" << endl;
        ready = 1;
    };

    Board game(players);
    game.initializeBoard(players);
 


    while (ready == 1) {
        displayMenu();
        cin >> choice;

        if (choice == 6) {
            cout << "Exiting Game." << endl;
            break;
        }

        switch (choice) {
            case 1:{
                cout << "Player Stats:" << endl;
            break;
            }

            case 2:{
                cout << "Character Information:" << endl;
            break;
            }

            case 3:{
                game.displayBoard();
            break;
            }

            case 4:{
                cout << "Your Advisor:" << endl;
            }

            case 5:{
                cout << "Roll the dice." << endl;
            break;
            }

            default:
                cout << "Invalid Option. Please select a valid option." << endl;
            break;
        }
    }
    
    return 0;
}