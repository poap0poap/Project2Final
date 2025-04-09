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

using namespace std;

//check for what tile you are on and applys effects
string tileCheck(Board& game, int player_position, int player_path)
{
    char p = game.getTileIndex(player_path,player_position);
    //cout << p;
    if (p == 'B')
    {
        return "nothing happend";
    }
    else if (p == 'Y')
    {
        return "advisor change";
    }
    else if (p == 'P')
    {
        return "riddle";
    }
    else if (p == 'L')
    {
        return "+2 to stats";
    }
    else if (p == 'I')
    {
        return "+3 to stats";
    }
    else if (p == 'G')
    {
        return "Graveyard";
    }
    else if (p == 'O')
    {
        return "Hyena";
    }
    else if (p == 'R')
    {
        return "Custom negitive";
    }
    else if (p == 'C')
    {
        return "Custom Postive";
    }
    else
    {
        return "Exceeded Board Size Ending";
    }
};

int main(){
    // number of players and size of board and moves
    int players,board,move;
    int player[2];
    // get number of players
    players = 1;
    //inilize board under name game
    Board game(players);
    board = game.getBoardSize();
    move = 0;
    game.displayBoard();
    for (int i=0;i<board;i++)//runs for total number or tiles
    {
        for (int b=0;b<players+1;b++)//gives each player a chance to move
        {
            //labels and displays path
            cout << "player "<< b+1 <<" path: "; 
            //input number for spaces moved
            cout << "how many spaces to move: ";
            cin >> move;
            game.movePlayer(b,move);
            game.displayTrack(b);
            //tile check
            player [b]  = player[b] + move;
            cout << tileCheck(game,player[b],b) << endl;
            //overflow check
            if (game.getPlayerPosition(b)>=board){
                cout << "game over" << endl;
                goto end;
            }
        }
        //clears terminal after each turn
        for (int i=0;i<3;i++){
            cout << endl;
        }
        game.displayBoard();
    }
    end:
    cout << "press any key to exit";
    _getch();
}