#include "GameExit.h"
#include <iostream>

void checkExit(std::atomic<bool>& running) {
    while (running) { // Continuously check for key press
        if (_kbhit()) {               // Check if a key is pressed
            char key = _getch();      // Get the key pressed
            //std::cout << "Key pressed: " << (int)key << "\n";
            if (key == 27) {          // 27 = ASCII code for Esc key
                std::cout << "ESC pressed. Exiting...\n";
                running = false;      // Stop the game by changing the flag
                break;
            }
        }
    }
}