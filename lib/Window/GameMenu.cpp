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

    window->draw(request);
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
        case 1:     // Agregar pj
            processAddCharacter(this, characterMap);
            break;
        case 2:     // Eliminar pj
            processDeleteCharacter(this, characterMap);
            break;
        case 3:     // Mostrar pjs
            processShowCharacters(this, characterMap);
            break;
        case 4:     // Buscar pj
            processSearchCharacter(this, characterMap);
            window->stats->showCharacterList = false;
            break;
        case 5:     // Empezar juego
            window->stats->showCharacterList = false;
            processLoadGame(this, characterMap);
            break;
        case 6:     // Cerrar
            window->close();
            break;
        default:
            break;
    }
    setRequest("Choose an option");
}


void GameMenu::processCharMenuOption(int option, BST<string, Character*>* characterMap)
{
    switch (option)
    {
        case 1:     // Buscar pj
            window->stats->showCharacterList = false;
            window->stats->showChosenChar = false;
            processSearchCharacter(this, characterMap);
            setRequest("Choose an option");
            break;
        case 2:     // Mostrar pjs
            window->stats->showCharacterDetails = false;
            processShowCharacters(this, characterMap);
            setRequest("Choose an option");
            break;
        case 3:     // Seleccionar pj // Posicionar pj
            window->stats->showCharacterDetails = false;
            if (window->world->charactersSelected < 6)
                processCharacterSelection(this, characterMap);
            else
            {
                processCharacterPositioning(this);
                changeCurrentMenu(gameMenu1);
                setRequest("Choose an option");
            }
            break;
        case 4:     // Salir
            window->stats->showCharacterList = false;
            window->stats->showChosenChar = false;
            changeCurrentMenu(mainMenu);
            setRequest("Choose an option");
            break;
        default:
            break;
    }
}


void GameMenu::processGameMenu1Option(int option)
{
    switch (option)
    {
        case 1:     // Guardar
            processSaveGame(this);
            break;
        case 2:     // Alimentar
            processFeedOption(this);
            break;
        case 3:      // Mover
            processMoveOption(this);
            break;
        case 4:     // Pasar
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
        case 1:     // Attack
            processAttackOption(this);
            break;
        case 2:     // Defend
            processDefenseOption(this);
            break;
        case 3:     // Pasar
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


GameMenu::~GameMenu()
{
    delete textbox;    
    delete menuList;
}
