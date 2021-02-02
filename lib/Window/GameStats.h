#ifndef GAMESTATS_H_
#define GAMESTATS_H_

#include "../../src/main.h"

class GameStats : public Cell
{
public:
    GameStats(float xPos, float yPos, float ySize, float xSize, sf::Color color) : Cell(xPos, yPos, ySize, xSize, color){};
};

#endif
