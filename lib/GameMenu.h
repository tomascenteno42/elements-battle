#ifndef GAMEMENU_H_
#define GAMEMENU_H_

#include "../src/main.h"

class GameMenu : public Cell
{

public:
    GameMenu(float xPos, float yPos, float ySize, float xSize, sf::Color color) : Cell(xPos, yPos, ySize, xSize, color){};
};

#endif