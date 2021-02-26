# Battle of the elements.

Battle of the elements is a elements themed game written in C++ using SFML multimedia library.

## Installing SFML (Linux)

```bash
sudo apt-get install libsfml-dev
```
## Creating an executable.

Creating executable.
```bash
make all
```
## Running the executable.
```
./bote
```

## Things to consider.
For cross-platform Makefile to work, keep in mind the following.
 
Be free to edit Makefile conditions for multiplatform compilation. Modify this `/usr/include/SFML/` by the location where you have installed SFML. Or in the case of windows, modify `*.dll` for the location where your SFML dll files are located.

```Makefile
ifeq ($(OS),Windows_NT)
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)  lib/Characters/*.cpp  lib/GameCells/*.cpp  lib/Window/*.cpp  src/utils/*.cpp  src/*.cpp  *.dll
else
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)  lib/Characters/*.cpp  lib/GameCells/*.cpp  lib/Window/*.cpp  src/utils/*.cpp  src/*.cpp  -L/usr/include/SFML/ -lsfml-graphics -lsfml-window -lsfml-system
endif
```

## Files

### characters.csv

This file contains all the game's existing characters.
Each line defines a character like so:
element,name,shield,maxLife

### Options

Each options file contains the options for a menu.

### mapStats.csv

This file contains the terrain for each cell in the game board, separated by commas.

+ l : lake
+ c : cliff
+ e : empty
+ v : volcano
+ p : path
+ m : mountain

### save.csv

This files contains all the needed information about the ongoing game.
First line is a number representing which player's turn it is, which is the same as the one who saved the game. 1 for Player 1, 2 for Player 2.
The next three lines describe the state of each of the three characters of the player who saved the game like so:
element,name,shield,life,maxLife,energy,isDefending,timesFed,row,col
The last three lines describe the state of each of the three characters of the remaining player.
