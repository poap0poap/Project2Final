# How to run

## Using g++
before compiling  make sure to have Board.cpp, Board.h, Main.cpp, PlayerInfo.h, Tile.h, Utility.cpp, Utility.h  
Use this to compile  
```
g++ -Werror -Wall -Wpedantic -std=c++17  Main.cpp Board.cpp Utility.cpp -o Main
```
Once compliled make sure in include advisors.txt, charcter.txt, random_events.txt, and riddles.txt in the same directory as Main.exe  
## Running Main.exe

make sure in the directory that has Main.exe you include advisors.txt, charcter.txt, random_events.txt, and riddles.txt  
Use this to compile the code:  g++ Main.cpp Board.cpp Utility.cpp -o Main
