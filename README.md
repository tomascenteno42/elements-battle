# Battle of the elements.

Battle of the elements is a elements themed game written in C++ using SFML multimedia library.

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
