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

int main(){
    int Players = 0;
    Board game(Players);
    game.initializeBoard();
    game.displayBoard();
    int i=0;
    bool b;
    while (true){
        cout << "move 0-1" << endl;
        cin >> i;
        if (i == 0){
           goto alex;
        }
        game.movePlayer(3);
        game.displayBoard();
    }
    alex:
    return 0;
}