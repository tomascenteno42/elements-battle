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

    window->draw(request);
}

void GameMenu::render()
{
    if (window->world->gameOver() && currentMenuIndex != mainMenu)
    {
        if (window->world->players[0]->charactersAlive == 0)
            std::cout << "PLAYER 2 WON" <<  std::endl;
        else
            std::cout << "PLAYER 1 WON" <<  std::endl;
            
        changeCurrentMenu(mainMenu);
        return;
    }


    std::string input = textbox->getText();
    textbox->setText("");
    
    if (input == "" || !stringIsNumeric(input) || stoi(input) < 1 || stoi(input) > getCurrentMenu()->getLength())
       setRequest("Enter a valid choice: ");
    else
        processOptionChoice(stoi(input));
}

void GameMenu::processOptionChoice(int option)
{
    switch (getCurrentMenuIndex())
    {
        case mainMenu:
            processMainMenuOption(option);
            break;
        case charSelectionMenu:
            processCharMenuOption(option);
            break;
        case gameMenu1:
            processGameMenu1Option(option);
            break;
        case gameMenu2:
            processGameMenu2Option(option);
            break;
    }
    setRequest("Choose an option");
    if (window->world->gameOver())
        setRequest("Press Enter to return to main menu");
}

void GameMenu::processMainMenuOption(int option)
{
    switch (option)
    {
        case 1:     // Agregar pj
            processAddCharacter(this);
            break;
        case 2:     // Eliminar pj
            processDeleteCharacter(this);
            break;
        case 3:     // Mostrar pjs
            processShowCharacters(this);
            break;
        case 4:     // Buscar pj
            processSearchCharacter(this);
            break;
        case 5:     // Empezar juego
            // Aca habria que cargar partida en el caso de que exista una partida cargada, yendo directamente a gameMenu1
            // En caso contrario se inicia un juego nuevo y se tienen que seleccionar los personajes
            changeCurrentMenu(charSelectionMenu);
            break;
        case 6:     // Cerrar
            window->close();
            break;
        default:
            break;
    }
}

void GameMenu::processCharMenuOption(int option)
{
    switch (option)
    {
        case 1:     // Buscar pj
            processSearchCharacter(this);
            break;
        case 2:     // Mostrar pjs
            processShowCharacters(this);
            break;
        case 3:     // Seleccionar pj // Posicionar pj
            if (window->world->charactersSelected < 5)
                processSelectCharacter(this);
            else
            {
                processSelectCharacter(this);
                processPlaceCharacters(this);
                changeCurrentMenu(gameMenu1);
            }
            break;
        case 4:     // Salir
            changeCurrentMenu(mainMenu);
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
            changeCurrentMenu(mainMenu);
            break;
        case 2:     // Alimentar
            processFeedOption(this);    // El cambio de menu se hace dentro de la funcion, así no se pierde el turno si
            break;                      // se intenta alimentar a un personaje de aire
        case 3:      // Mover
            processMoveOption(this);
            changeCurrentMenu(gameMenu2);
            break;
        case 4:     // Pasar
            changeCurrentMenu(gameMenu2);
            break;
        default:
            break;
            
    }
    window->world->updateOccupiedStates();
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
    window->world->advanceState(); // terminó el turno del personaje actual
    window->world->updateOccupiedStates();
}



GameMenu::~GameMenu()
{
    delete textbox;    
    delete menuList;
}
