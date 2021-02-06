#include "../../src/main.h"

GameMenu::GameMenu(float xPos, float yPos, float ySize, float xSize, sf::Color color, GameWindow* window)
    :Cell(xPos, yPos, ySize, xSize, color)
    {
        font.loadFromFile(FONT_FILE);
        textbox = new Textbox(14, sf::Color::White, true, font);
        menuList = new GenericList<Menu*>;
        this -> window = window;
        setRequest("Choose an option: ");
        fillMenuList();
    };

void GameMenu::fillMenuList()
{
    const char *optionsFiles[4] = {OPTIONS_FILE_1, OPTIONS_FILE_2, OPTIONS_FILE_3, OPTIONS_FILE_4};
    int menuLength = 0;
    Menu* m = 0;
    for (int i = 0; i < 4; i ++)
    {
        menuLength = getAmountOfOptions(optionsFiles[i]);
        m = new Menu(menuLength);
        fillMenu(m, optionsFiles[i]);
        menuList->add(m, i+1);
    }
    changeCurrentMenu(mainMenu);
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

menus GameMenu::getCurrentMenuIndex()
{
    return currentMenuIndex;
}

void GameMenu::drawCurrentMenu()
{
    float pos = 410;

    for (int i = 0; i < currentMenu->getLength(); i++)
    {
        sf::Text text((to_string((i + 1)) + ") " + currentMenu->getOption(i)), font, 14);
        text.setFillColor(sf::Color::White);
	    text.setPosition(sf::Vector2f(10, pos));
        pos += 25;
        window->draw(text);
    }

    if (waitingForOptionChoice) setRequest("Choose an option: ");

    window->draw(request);
}

GameMenu::~GameMenu()
{
    delete textbox;    
    delete menuList;
}
