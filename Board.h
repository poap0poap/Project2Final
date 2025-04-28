#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"

class Board
{
public:
    static const int _MAX_PLAYERS = 4;
private:
    static const int _BOARD_SIZE = 102;
    Tile _tiles[2][_BOARD_SIZE];
    static const int _paths = 2;
    int _player_path[_MAX_PLAYERS];
    int _player_count;
    int _player_position[_MAX_PLAYERS][_paths];
    void displayTile(int player_index, int pos);
    void initializeTiles(int player_index);
    bool isPlayerOnTile(int player_index, int pos);

public:
    Board();
    Board(int player_count, int player_paths[]);
    int getBoardSize() const;
    void displayTrack(int player_index);
    void initializeBoard(int player_count);
    void displayBoard();
    bool movePlayer(int player_index, int spaces);
    int getPlayerPosition(int player_index) const;
    char getTileIndex(int path, int pos);
};

#endif