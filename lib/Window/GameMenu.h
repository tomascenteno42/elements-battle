#ifndef GAMEMENU_H_
#define GAMEMENU_H_

#include "../../src/main.h"

class GameMenu : public Cell
{

public:
    Textbox *textbox;
    GameMenu(float xPos, float yPos, float ySize, float xSize, sf::Color color, Textbox *text) : Cell(xPos, yPos, ySize, xSize, color)
    {
        textbox = text;
    };

    ~GameMenu();
};

#endif
