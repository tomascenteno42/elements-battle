#include "../../src/main.h"

GameMenu::GameMenu(float xPos, float yPos, float ySize, float xSize, sf::Color color, GameWindow* window): 
    Cell(xPos, yPos, ySize, xSize, color)
    {   
        font.loadFromFile(FONT_FILE);
        setRequest("Ingrese una opción: ");
        textbox = new Textbox(30, sf::Color::White, true, font);
        menuList = new GenericList<Menu*>;
        fillMenuList();
        this -> window = window;
    }

void GameMenu::fillMenuList()
{
    const char * optionsFiles[4] = {OPTIONS_FILE_1, OPTIONS_FILE_2, OPTIONS_FILE_3, OPTIONS_FILE_4};

    const char * optionFile = "";
    int menuLength = 0;
    Menu* m = 0;
    for (int i = 0; i < 4; i ++)
    {
        optionFile = optionsFiles[i];
        menuLength = getAmountOfOptions(optionFile);
        m = new Menu(menuLength);
        fillMenu(m, optionFile);
        menuList->add(m, i+1);
    }

    currentMenu = menuList->get(1);
}

void GameMenu::changeCurrentMenu(size_t pos)
{
    currentMenu = menuList->get(pos);
    currentMenuIndex = static_cast<menus>(pos);
}

void GameMenu::setRequest(std::string req)
{
    request = sf::Text(req, font, 14);
}

Menu* GameMenu::getCurrentMenu()
{
    return currentMenu;
}




void GameMenu::drawCurrentMenu()
{
    float posY = 410;

    for (int i = 0; i < currentMenu->getLength(); i++)
    {
        sf::Text text((to_string((i + 1)) + ") " + currentMenu->getOption(i)), font, 14);
        text.setFillColor(sf::Color::White);
	    text.setPosition(sf::Vector2f(10, posY));
        posY += 25;
        window->draw(text);
    }
}

void GameMenu::processInput()
{
    std::string input = textbox -> getText();
    if (waitingForOptionChoice && !(stringIsNumeric(input) && stoi(input) >= 1 && stoi(input) <= currentMenu->getLength()))
        request.setString("Enter a valid choice"); 
    else
        processOption(currentMenuIndex, stoi(input), waitingForOptionChoice);
}

GameMenu::~GameMenu()
{
    delete textbox;    
    delete menuList;
}
