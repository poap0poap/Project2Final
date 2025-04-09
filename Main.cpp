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
    int Players,board;
    Players = 3;
    Board game(Players);
    board = game.getBoardSize();
    game.initializeBoard(Players);
    int move = 0;
    cout << "board1";
    game.displayTrack(1);
    cout << endl;
    for (int i=0;i<board;i++){
        cout << endl;
        for (int b=0;b<Players+1;b++){
            cout << "player "<< b+1 <<" spot: ";
            game.displayTrack(b);
            //cout << "starting pos " << game.getPlayerPosition(b) << endl;
            cin >> move;
            game.movePlayer(b,move);
            if (game.getPlayerPosition(b)>=board){
                return 0;
            }
        }
        for (int i=0;i<6;i++){
            cout << endl;
        }
    }
}