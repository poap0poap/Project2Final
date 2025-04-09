#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Board.h"

using namespace std;

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
    int Players = 0;
    int ready = 0;
    Board game(Players);
    game.initializeBoard();
    cout << "How many players are there? (1-4)" << endl;
    cin >> Players;
    if (Players < 0 && Players > 4){
        cout << "Invalid ammount of players. Please choose a number between 1 to 4." << endl;
    }    else {
        cout << "There are " << Players << " Players." << endl;
        ready = 1;
    };

    
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


    // game.displayBoard();
    // int i=0;
    // bool b;
    // while (true){
    //     cout << "move 0-1" << endl;
    //     cin >> i;
    //     if (i == 0){
    //        goto alex;
    //     }
    //     game.movePlayer(3);
    //     game.displayBoard();
    // }
    // alex:
    return 0;
}