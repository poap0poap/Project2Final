#ifndef GAMEEXIT_H  
#define GAMEEXIT_H

#include <atomic> // If you're using threads
#include <conio.h> // For key detection (Windows)

// Declare the game quit function
void checkExit(std::atomic<bool>& running);

#endif