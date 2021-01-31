#ifndef GAMEMENU_H_
#define GAMEMENU_H_

#include "../src/main.h"

class GameMenu : public Cell
{
private:
    GenericList<Menu*>* MenuList;
    Menu* ChosenMenu;

public:
    Textbox *textbox;

    GameMenu(float xPos, float yPos, float ySize, float xSize, sf::Color color, Textbox *text) : 
    Cell(xPos, yPos, ySize, xSize, color)
    {
        textbox = text;
        MenuList = new GenericList<Menu*>;
    };

    void FillMenuList();
    void ChangeChosen(size_t pos);
    Menu* GetChosenMenu();

    ~GameMenu();
};

#endif
