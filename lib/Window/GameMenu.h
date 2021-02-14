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
    sf::Font font;

public:
    GameWindow* window;
    Textbox *textbox;
    sf::Text request;

    GameMenu(float xPos, float yPos, float ySize, float xSize, sf::Color color, GameWindow* window);

    void fillMenuList();
    void changeCurrentMenu(menus menu);
    void setRequest(std::string req);

    Menu* getCurrentMenu();
    menus getCurrentMenuIndex();

    /**
        Nucleus of menu logic, it renders menu options.
    */
    void render(BST<string, Character*>* characterMap);

    void processOptionChoice(int option, BST<string, Character*>* characterMap);

    void processMainMenuOption(int option, BST<string, Character*>* characterMap);
    void processCharMenuOption(int option, BST<string, Character*>* characterMap);
    void processGameMenu1Option(int option);
    void processGameMenu2Option(int option);
    

    void drawCurrentMenu();

    ~GameMenu();
};

#endif
