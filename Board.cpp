#include "Board.h"
#include <iostream>
#include <string>
#define BLACK "\033[48;2;0;0;0m" // Grassland Tile
#define YELLOW "\033[48;2;255;255;0m" // Change Advisor
#define PURPLE "\033[48;2;128;0;128m" // Riddle Tile
#define BLUE "\033[48;2;10;10;230m" // Calm Tile +2 Stat
#define PINK "\033[48;2;255;105;180m" // Calm Tile +3 Stat
#define GREEN "\033[48;2;0;128;0m"  // Graveyard Tile Move Back 10 and -1 Stat
#define BROWN "\033[48;2;139;69;19m" // Hyena Tile Move back to original position -3 Stamina
#define RED "\033[48;2;230;10;10m" // Custom Negative Tile -5 All Stats -50% Points
#define CYAN "\033[48;2;0;255;255m" // Custom Positive Tile +5 All Stats +50% Points

#define ORANGE "\033[48;2;230;115;0m" // End Tile
#define GREY "\033[48;2;128;128;128m" // Start Tile
#define RESET "\033[0m"

void Board::initializeBoard(int player_count)
{
    // Seed random number generator in your main function once
    for (int i = 0; i < 2; i++)
    {
        initializeTiles(i);  // This ensures each lane has a unique tile distribution
    }
}

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

void Board::initializeTiles(int player_index)
{
    Tile temp;
    int black_count = 0;
    int total_tiles = _BOARD_SIZE;

    // Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++)
    {   
        if (i == total_tiles - 1) {
            // Set the last tile as Orange
            temp.color = 'E';
        } 
        else if (i == 0) {
            // Set the Start tile as Grey
            temp.color = 'S';
        } 
        else if (black_count < 40 && (rand() % (total_tiles - i) < 40 - black_count)) {
            temp.color = 'B';
            black_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Yellow,Purple,BLue,Pink,Green,Brown,Red,Cyan
            int color_choice = rand() % 8;
            switch (color_choice)
            {
                case 0:
                    temp.color = 'Y'; // Yellow
                    break;
                case 1:
                    temp.color = 'P'; // Purple
                    break;
                case 2:
                    temp.color = 'L'; // Blue
                    break;
                case 3:
                    temp.color = 'I'; // Pink
                    break;
                case 4:
                    temp.color = 'G'; // Green
                    break;
                case 5:
                    temp.color = 'O'; //Brown
                    break;
                case 6:
                    temp.color = 'R'; //Red
                    break;
                case 7:
                    temp.color = 'C'; //Cyan
                    break;
            }
        }

        // Assign the tile to the board for the specified lane
        _tiles[player_index][i] = temp;
    }
}


int Board::getBoardSize() const
{
    return _BOARD_SIZE; // Returns the board size
}


Board::Board()
{
    _player_count = 1;

    // Initialize player position
    _player_position[0] = 0;
    // Initialize tiles
    initializeBoard(_player_count);
}
Board::Board(int player_count)
{
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    }
    else
    {
        _player_count = player_count;
    }

    // Initialize player position
    for (int i = 0; i < _player_count+1; i++)
    {
        _player_position[i] = 0;
    }

    // Initialize tiles

    initializeBoard(_player_count);
}

bool Board::isPlayerOnTile(int player_index, int pos)
{
    if (_player_position[player_index] == pos)
    {
        return true;
    }
    return false;
}

char Board::getTileIndex(int player_index, int pos)
{
    return _tiles[player_index][pos].color;
}

void Board::displayTile(int player_index, int pos)
{
    // string space = "                                       ";
    std::string color = "";
    int player = isPlayerOnTile(player_index, pos);

    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>

    // Determine color to display
    if (_tiles[player_index][pos].color == 'B')
    {
        color = BLACK;
    }
    else if (_tiles[player_index][pos].color == 'Y')
    {
        color = YELLOW;
    }
    else if (_tiles[player_index][pos].color == 'P')
    {
        color = PURPLE;
    }
    else if (_tiles[player_index][pos].color == 'L')
    {
        color = BLUE;
    }
    else if (_tiles[player_index][pos].color == 'I')
    {
        color = PINK;
    }
    else if (_tiles[player_index][pos].color == 'G')
    {
        color = GREEN;
    }
    else if (_tiles[player_index][pos].color == 'O')
    {
        color = BROWN;
    }
    else if (_tiles[player_index][pos].color == 'R')
    {
        color = RED;
    }
    else if (_tiles[player_index][pos].color == 'C')
    {
        color = CYAN;
    }
    else if (_tiles[player_index][pos].color == 'E')
    {
        color = ORANGE;
    }
    else if (_tiles[player_index][pos].color == 'S')
    {
        color = GREY;
    }

     if (player == true)
    {
        std::cout << color << "|" << (player_index + 1) << "|" << RESET;
    }
    else
    {
        std::cout << color << "| |" << RESET;
    }
}

void Board::displayTrack(int player_index)
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        if (i==_BOARD_SIZE/2){std::cout << std::endl;}
        displayTile(player_index, i);
    }
    std::cout << std::endl;
}

void Board::displayBoard()
{
    for (int i = 0; i < 2; i++)
    {
        displayTrack(i);
        if (i == 0) {
            std::cout << std::endl;  // Add an extra line between the two lanes
        }
    }
}

bool Board::movePlayer(int player_index,int spaces)
{
        // Increment player position
    _player_position[player_index] = _player_position[player_index]+spaces;
    if (_player_position[player_index] == _BOARD_SIZE - 1)
        {
             // Player reached last tile
             return true;
        }
    return false;
}

int Board::getPlayerPosition(int player_index) const
{
    if (player_index >= 0 && player_index <= _player_count)
    {
        return _player_position[player_index];
    }
    return -1;
}
