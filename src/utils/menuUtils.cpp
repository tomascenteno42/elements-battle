#include "../main.h"

// MENU UTILS

void fillMenu(Menu *m, const char* filename)
{
    ifstream optionsFile;
    string option;

    optionsFile.open(filename);
    if (optionsFile.is_open())
    {
        while (getline(optionsFile, option, '\n'))
        {
            (*m).addOption(option);
        }
    }
    optionsFile.close();
}

void renderMenu(GameMenu *menu)
{
    std::string input = menu->textbox->getText();
    menu->textbox->setText("");
    
    if (input == "" || !stringIsNumeric(input) || stoi(input) < 1 || stoi(input) > menu->getCurrentMenu()->getLength())
        menu->setRequest("Enter a valid choice: ");
    else
        processOptionChoice(menu, stoi(input));
}

void processOptionChoice(GameMenu *menu, int option)
{
    switch (menu->getCurrentMenuIndex())
    {
        case mainMenu:
            processMainMenuOption(menu, option);
            break;
        case charSelectionMenu:
            processCharMenuOption(menu, option);
            break;
        case gameMenu1:
            processGameMenu1Option(menu, option);
            break;
        case gameMenu2:
            processGameMenu2Option(menu, option);
            break;
    }
    menu->setRequest("Choose an option");
}

void processMainMenuOption(GameMenu *menu, int option)
{
    std::string input;
    switch (option)
    {
        case 1:     // Agregar pj
            menu->setRequest("Add a character: ");
            input = getUserInput(menu->window);
            std::cout << "Added character " << input << std::endl;
            break;
        case 2:     // Eliminar pj
            menu->setRequest("Delete a character: ");
            input = getUserInput(menu->window);
            std::cout << "Deleted character " << input << std::endl;            
            break;
        case 3:     // Mostrar pjs
            std::cout << "Showing all characters" << std::endl;
            break;
        case 4:     // Buscar pj
            menu->setRequest("Search character by name: ");
            input = getUserInput(menu->window);
            std::cout << "Searched character " << input << std::endl;            
            break;
        case 5:     // Empezar juego
            menu->changeCurrentMenu(charSelectionMenu);
            break;
        case 6:     // Cerrar
            menu->window->close();
            break;
        default:
            break;
    }
}

void processCharMenuOption(GameMenu *menu, int option)
{
    std::string input;
    switch (option)
    {
        case 1:     // Buscar pj
            menu->setRequest("Search character by name: ");
            input = getUserInput(menu->window);
            std::cout << "Searching character " << input << std::endl;            
            break;
        case 2:     // Mostrar pjs
            std::cout << "Showing all characters" << std::endl;
            break;
        case 3:     // Seleccionar pj
            //menu->setRequest("Pick a character: ");
            //menu->waitingForOptionChoice = false;
            //orden: P1, P2, P1, P2, P1, P2
            //luego de que se eligen los 6 personajes tienen que posicionarlos
            menu->changeCurrentMenu(gameMenu1);
            break;
        case 4:     // Salir
            menu->changeCurrentMenu(mainMenu);
            break;
        default:
            break;
    }
}

void processGameMenu1Option(GameMenu *menu, int option)
{
    Character* character = menu->window->world->currentCharacter;
    std::string input;
    
    switch (option)
    {
        case 1:     // Guardar
            // Aca se llamaria a la funcion que guarda la partida
            menu->changeCurrentMenu(mainMenu);
            break;
        case 2:     // Alimentar
            character->feed();
            if (character->getElement() != AIR)
                menu->changeCurrentMenu(gameMenu2);
            break;
        case 3: {     // Mover
            menu->setRequest("Enter where you would like to move: (ex: 2,5)");
            sf::Vector2f destination;
            bool validDest = false;
            while (!validDest)
            {
                destination = getPositionFromUser(menu);
                validDest = validMoveDestination(menu, character, destination);
            }
            processMoveChoice(menu->window, character, destination);
            menu->changeCurrentMenu(gameMenu2);
            break;
        }
        case 4:     // Pasar
            menu->changeCurrentMenu(gameMenu2);
            break;
        default:
            break;
    }
}

void processGameMenu2Option(GameMenu *menu, int option)
{
    Character* character = menu->window->world->currentCharacter;
    std::string input;

    switch (option)
    {
        case 1:     // Attack
            character->attack(menu->window);
            menu->changeCurrentMenu(gameMenu1);
            break;

        case 2:     // Defend
            character->defend(menu->window);
            menu->changeCurrentMenu(gameMenu1);
            break;

        case 3:     // Pasar
            menu->changeCurrentMenu(gameMenu1);
            break;

        default:
            break;
    }

    menu->window->world->advanceState(); // terminó el turno del personaje actual
}


int getAmountOfOptions(const char* filename)
{
    fstream optionsFile;

    optionsFile.open(filename);

    string option;
    int length = 0;

    if (optionsFile.is_open())
    {
        while (getline(optionsFile, option, '\n'))
            length++;
    }
    else
        cout << "FILE ERROR";

    optionsFile.close();
    return length;
}

std::string getUserInput(GameWindow* window)
{   
    std::string input;
    sf::Event event;
    bool stop = false;
    while (!stop)
    {
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::TextEntered:
                window->menu->textbox->typedOn(event);
                if (event.text.unicode == ENTER_KEY)
                {
                    stop = true;
                    input = window->menu->textbox->getText();
                    window->menu->textbox->setText("");
                }
                break;

            default:
                break;
            }
        }
        window->clear();
        drawScreen(window);
        window->display();
    }
    return input;
}

sf::Vector2f getPositionFromUser(GameMenu* menu)
{
    std::string input;
    sf::Vector2f position;
    bool validPos = false;
    while (!validPos)
    {
        input = getUserInput(menu->window);
        if (!validPosition(input))        
            menu->setRequest("Invalid position. Enter X,Y with X and Y between 0 and 7");
        else
        {
            position = parseStringToVector2f(input);
            validPos = true;
        }
    }
    return position;
}