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
    bool ready = false;

    srand(time(0));

    for (int i = 0; i < 1;){
    cout << "How many players are there? (2-4)" << endl;
    cin >> players;

    while (cin.fail()) {
        cin.clear(); // reset fail flag
        cin.ignore(1000, '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number between 2 and 4." << endl;
        cin >> players;
    }

    if (players < 2 || players > 4){
        cout << "Invalid ammount of players. Please choose a number between 2 to 4.\n" << endl;
    }    else {
        cout << "There are " << players << " Players.\n" << endl;
        ready = false;
        i++;
    };
}
    Board game(players);
    game.initializeBoard(players);

    while (ready == 1) {
        for (int currentPlayer = 0; currentPlayer < players; currentPlayer++) {
            cout << "\n--- Player " << currentPlayer + 1 << "'s Turn ---\n";
            bool turnDone = false;
    
            while (!turnDone) {
                displayMenu();
                cin >> choice;
    
                if (choice == 6) {
                    cout << "Exiting Game." << endl;
                    ready = false;
                    break;
                }
    
                switch (choice) {
                    case 1:
                        cout << "Player Stats:\n" << endl;
                        // You need to pass actual player data here
                        break;
                    case 2:
                        cout << "Character Information:\n" << endl;
                        break;
                    case 3:
                        game.displayBoard();
                        break;
                    case 4:
                        cout << "Your Advisor:\n" << endl;
                        break;
                    case 5:
                        cout << "Rolling the dice...\n";
                        // Perform movement logic here
                        turnDone = true;  // end the current player's turn
                        break;
                    default:
                        cout << "Invalid Option. Try again.\n";
                        break;
                }
            }
        }
    }
    
    return 0;
}