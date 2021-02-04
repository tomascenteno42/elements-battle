#include "../../src/main.h"

GameMenu::GameMenu(float xPos, float yPos, float ySize, float xSize, sf::Color color)
    :Cell(xPos, yPos, ySize, xSize, color)
    {
        font.loadFromFile(FONT_FILE);
        textbox = new Textbox(14, sf::Color::White, true, font);
        menuList = new GenericList<Menu*>;
        setRequest("Choose an option: ");
        fillMenuList();
    };

void GameMenu::fillMenuList()
{
    const char *optionsFiles[4] = {OPTIONS_FILE_1, OPTIONS_FILE_2, OPTIONS_FILE_3, OPTIONS_FILE_4};
    int menuLength = 0;
    Menu* m = 0;
    for (int i = 0; i < 3; i ++)
    {
        menuLength = getAmountOfOptions(optionsFiles[i]);
        m = new Menu(menuLength);
        fillMenu(m, optionsFiles[i]);
        menuList->add(m, i+1);
    }
    currentMenu = menuList->get(1);
}

void GameMenu::changeCurrentMenu(menus menu)
{
    currentMenu = menuList->get(static_cast<int>(menu));
    currentMenuIndex = menu;
}

void GameMenu::setRequest(std::string req)
{
    request = sf::Text(req, font, 14);
    request.setPosition({10, 600});
}

Menu* GameMenu::getCurrentMenu()
{
    return currentMenu;
}

void GameMenu::processInput()
{
    std::string input = textbox -> getText();
    if (waitingForOptionChoice && !(stringIsNumeric(input) && stoi(input) >= 1 && stoi(input) <= currentMenu->getLength()))
        request.setString("Enter a valid choice: ");
    //else
        //processOption(currentMenuIndex, stoi(input), waitingForOptionChoice);
}

GameMenu::~GameMenu()
{
    delete textbox;    
    delete menuList;
}
