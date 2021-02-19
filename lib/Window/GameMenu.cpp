#include "../../src/main.h"


GameMenu::GameMenu(float xPos, float yPos, float ySize, float xSize, sf::Color color, GameWindow* window)
    :Cell(xPos, yPos, ySize, xSize, color)
{
    font.loadFromFile(FONT_FILE);
    textbox = new Textbox(14, sf::Color::White, true, font);
    menuList = new GenericList<Menu*>;
    this -> window = window;
    fillMenuList();
    setRequest("Choose an option");
}


void GameMenu::fillMenuList()
{
    const char* optionsFiles[4] = {OPTIONS_FILE_1, OPTIONS_FILE_2, OPTIONS_FILE_3, OPTIONS_FILE_4};
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


void GameMenu::render(BST<string, Character*>* characterMap)
{
    std::string input = textbox->getText();
    textbox->setText("");
    
    if (input == "" || !stringIsNumeric(input) || stoi(input) < 1 || stoi(input) > currentMenu->getLength())
       setRequest("Enter a valid choice: ");
    else
        processOptionChoice(stoi(input), characterMap);
}


void GameMenu::processOptionChoice(int option, BST<string, Character*>* characterMap)
{
    switch (getCurrentMenuIndex())
    {
        case mainMenu:
            processMainMenuOption(option, characterMap);
            break;
        case charSelectionMenu:
            processCharMenuOption(option, characterMap);
            break;
        case gameMenu1:
            processGameMenu1Option(option);
            break;
        case gameMenu2:
            processGameMenu2Option(option);
            break;
    }
}
/* 
window->stats->showCharacterDetails = false;
window->stats->showCharacterList = false;
window->stats->showChosenChar = false;
 */
void GameMenu::processMainMenuOption(int option, BST<string, Character*>* characterMap)
{
    window->stats->showCharacterDetails = false;
    switch (option)
    {
        case 1:
            processAddCharacter(this, characterMap);
            break;
        case 2:
            processDeleteCharacter(this, characterMap);
            break;
        case 3:
            processShowCharacters(this, characterMap);
            break;
        case 4:
            processSearchCharacter(this, characterMap);
            window->stats->showCharacterList = false;
            break;
        case 5:
            window->stats->showCharacterList = false;
            processLoadGame(this, characterMap);
            break;
        case 6:
            window->close();
            break;
        default:
            break;
    }
}


void GameMenu::processCharMenuOption(int option, BST<string, Character*>* characterMap)
{
    switch (option)
    {
        case 1:
            window->stats->showChosenChar = false;
            processSearchCharacter(this, characterMap);
            setRequest("Choose an option");
            window->stats->showCharacterList = false;
            break;
        case 2:
            window->stats->showCharacterDetails = false;
            processShowCharacters(this, characterMap);
            break;        
        case 3:
            window->stats->showCharacterDetails = false;
            processCharacterSelection(this, characterMap);
            if (window->world->charactersSelected == 6)
            {
                changeCurrentMenu(gameMenu1);
                setRequest("Choose an option");
            }
            break;
        case 4:
            window->stats->showCharacterList = false;
            window->stats->showChosenChar = false;
            changeCurrentMenu(mainMenu);
            break;
        default:
            break;
    }

    if (option != 3)
        setRequest("Choose an option");
}


void GameMenu::processGameMenu1Option(int option)
{
    switch (option)
    {
        case 1:
            processSaveGame(this);
            break;
        case 2:
            processFeedOption(this);
            break;
        case 3:
            processMoveOption(this);
            break;
        case 4:
            changeCurrentMenu(gameMenu2);
            setRequest("Choose an option");
            break;
        default:
            break;     
    }
}


void GameMenu::processGameMenu2Option(int option)
{
    switch (option)
    {
        case 1:
            processAttackOption(this);
            break;
        case 2:
            processDefenseOption(this);
            break;
        case 3:
            break;
        default:
            break;
    }

    changeCurrentMenu(gameMenu1);
    window->world->canSave = false;
    window->world->advanceState(); // terminó el turno del personaje actual
    window->world->updateOccupiedStates();
    
    setRequest("Choose an option");

    if (window->world->gameOver())
        endGame(this);
}


menus GameMenu::getCurrentMenuIndex()
{
    return currentMenuIndex;
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

    window->draw(request);
}


GameMenu::~GameMenu()
{
    delete textbox;    
    delete menuList;
}
