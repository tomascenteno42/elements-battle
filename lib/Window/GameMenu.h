#ifndef GAMEMENU_H_
#define GAMEMENU_H_

#include "../../src/main.h"

class GameWindow;

class GameMenu : public Cell
{
private:
    GenericList<Menu*>* menuList;
    Menu* currentMenu;
    menus currentMenuIndex;
    int currentOption = 0;

    sf::Font font;

public:
    GameWindow* window;
    Textbox *textbox;
    sf::Text request;
    bool waitingForOptionChoice = true;

    GameMenu(float xPos, float yPos, float ySize, float xSize, sf::Color color, GameWindow* window);

    void fillMenuList();
    void changeCurrentMenu(menus menu);
    void setRequest(std::string req);

    Menu* getCurrentMenu();

    void processInput();
    void showCurrentMenu();

    ~GameMenu();
};

#endif
