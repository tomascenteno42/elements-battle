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
    sf::Text request;

    /*
     * Fills all four menus with their options, retrieved from files
     */
    void fillMenuList();

    /*
     * Calls option processor of current menu
     */
    void processOptionChoice(int option, BST<string, Character*>* characterMap);
    
    /*
     * Processes chosen option in main menu
     */
    void processMainMenuOption(int option, BST<string, Character*>* characterMap);
    
    /*
     * Processes chosen option in character selection menu
     */
    void processCharMenuOption(int option, BST<string, Character*>* characterMap);
    
    /*
     * Processes chosen option in game menu 1
     */
    void processGameMenu1Option(int option);
    
    /*
     * Processes chosen option in game menu 2
     */
    void processGameMenu2Option(int option);

public:
    GameWindow* window;
    Textbox* textbox;

    GameMenu(float xPos, float yPos, float ySize, float xSize, sf::Color color, GameWindow* window);

    /*
     * Nucleus of menu logic, it renders menu options.
     */
    void render(BST<string, Character*>* characterMap);

    menus getCurrentMenuIndex();

    /*
     * Sets currentMenu and currentMenuIndex to the specified menu
     */
    void changeCurrentMenu(menus menu);

    void setRequest(std::string req);

    /*
     * Draws menu elements on window
     */
    void drawCurrentMenu();

    ~GameMenu();
};

#endif
