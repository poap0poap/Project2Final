#include "Board.h"
#include <iostream>
#include <string>
#define BLACK "\033[48;2;0;0;0m" // Grassland Tile
#define YELLOW "\033[48;2;225;175;35m" // Change Advisor
#define PURPLE "\033[48;2;128;0;128m" // Riddle Tile
#define BLUE "\033[48;2;10;10;230m" // Calm Tile +2 Stat
#define PINK "\033[48;2;200;105;180m" // Calm Tile +3 Stat
#define GREEN "\033[48;2;0;128;0m"  // Graveyard Tile Move Back 10 and -1 Stat
#define BROWN "\033[48;2;139;69;19m" // Hyena Tile Move back to original position -3 Stamina
#define RED "\033[48;2;230;10;10m" // Custom Negative Tile -5 All Stats -50% Points
#define CYAN "\033[48;2;0;139;139m" // Custom Positive Tile +5 All Stats +50% Points
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

void Board::initializeTiles(int path)
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
        else if (black_count < 50 && (rand() % (total_tiles - i) < 50 - black_count)) {
            temp.color = 'B';
            black_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Yellow,Purple,BLue,Pink,Green,Brown,Red,Cyan
            // Total number of special tiles 1/2 board
            int color_choice = rand() % 8;
            switch (color_choice){
                case 0: temp.color = 'Y'; break;
                case 1: temp.color = 'P'; break;
                case 2: temp.color = 'L'; break;
                case 3: temp.color = 'I'; break;
                case 4: temp.color = 'G'; break;
                case 5: temp.color = 'O'; break;
                case 6: temp.color = 'R'; break;
                case 7: temp.color = 'C'; break;
            }
        }

        // Assign the tile to the board for the specified lane
        _tiles[path][i] = temp;
    }
}


int Board::getBoardSize() const
{
    return _BOARD_SIZE; // Returns the board size
}


Board::Board()
{
    for (int i = 0; i < _MAX_PLAYERS; ++i) {
        _player_path[i] = 0;
    }     
    // Initialize player position
    _player_position[0][_player_path[0]] = 0;
    // Initialize tiles
    initializeBoard(_paths);
}
Board::Board(int player_count, int player_paths[]) {
    if (player_count > _MAX_PLAYERS) {
        _player_count = _MAX_PLAYERS;
    } else {
        _player_count = player_count;
    }

    for (int i = 0; i < _player_count; ++i) {
        _player_path[i] = player_paths[i]; // Default path
        _player_position[i][_player_path[i]] = 0; // Initialize positions
    }

    for (int i = _player_count; i < _MAX_PLAYERS; ++i) {
        _player_path[i] = 0; // Mark inactive players
    }
    initializeBoard(_paths);
}

bool Board::isPlayerOnTile(int player_index, int pos)
{
    if (_player_position[player_index][_player_path[player_index]] == pos)
    {
        return true;
    }
    return false;
}

char Board::getTileIndex(int path, int pos)
{
    return _tiles[path][pos].color;
}

void Board::displayTile(int player_path, int pos)
{
    // string space = "                                       ";
    std::string color = "";
    std::string player_symbol = "";  // Default empty space

    // // Check if any player is on this tile
    // for (int i = 0; i < _player_count; ++i) {
    //     if (_player_path[i] == player_path && _player_position[i][player_path] == pos) {
    //         player_symbol = '1' + i;  // Show player number (1, 2, 3, ...)
    //         break;
    //     }
    // }
    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>

    // Determine color to display
    char tileColor = _tiles[player_path][pos].color;
    switch (tileColor) {
        case 'B': color = BLACK; break;
        case 'Y': color = YELLOW; break;
        case 'P': color = PURPLE; break;
        case 'L': color = BLUE; break;
        case 'I': color = PINK; break;
        case 'G': color = GREEN; break;
        case 'O': color = BROWN; break;
        case 'R': color = RED; break;
        case 'C': color = CYAN; break;
        case 'S': color = GREY; break;
        case 'E': color = ORANGE; break;
    }

    for (int i = 0; i < _player_count; ++i)
    {
        if (_player_path[i] == player_path && _player_position[i][player_path] == pos)
        {
            player_symbol += std::to_string(i + 1); // Player numbers: 1, 2, etc.
        }
    }

    // Pad with spaces to keep tile size consistent
    while (player_symbol.length() < 1) {
        player_symbol += " ";
    }

    std::cout << "\033[97m" << color << "|" << "\033[97m" << player_symbol << color << "|" << RESET;
}

void Board::displayTrack(int player_path)
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        if (i==_BOARD_SIZE/3||i==_BOARD_SIZE*2/3){std::cout << std::endl;}
        displayTile(player_path, i);
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
    _player_position[player_index][_player_path[player_index]] += spaces;
    if (_player_position[player_index][_player_path[player_index]] == _BOARD_SIZE - 1)
        {
            _player_position[player_index][_player_path[player_index]] = _BOARD_SIZE - 1;
             // Player reached last tile
             return true;
        }
    return false;
}

int Board::getPlayerPosition(int player_index) const
{
    if (player_index >= 0 && player_index <= _player_count)
    {
        return _player_position[player_index][_player_path[player_index]];
    }
    return -1;
}