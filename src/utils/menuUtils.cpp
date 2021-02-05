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
    
    if (!menu->waitingForOptionChoice)
        processUserInput(menu, input);
        // En este caso no se elige opcion del menu, ya se está en una opción y se está ingresando lo pedido
    else
    {
        if (!(stringIsNumeric(input) && stoi(input) >= 1 && stoi(input) <= menu->getCurrentMenu()->getLength()))
            menu->request.setString("Enter a valid choice: ");
        else
            processOptionChoice(menu, stoi(input));
            // Se actualiza el mensaje de request según la opción del menú que se elija
            // Y la instancia de menu se prepara para el siguiente ingreso

// El proceso es: "Menu: ..., ..., 4 - Mover personaje, ..."
//                *El usuario ingresa 4
//                Ahora se preprocesa esa entrada y el menú sabe que lo siguiente que se va a ingresar es para mover
//                Pero aun no se llama a la funcion que procesa el movimiento porque necesitaria esperar input de nuevo
//                asi que necesito volver al ciclo de while window is  open
    }
}

void processOptionChoice(GameMenu *menu, int option)
{
    menu->currentOption = option;
    switch (menu->getCurrentMenuIndex())
    {
        case mainMenu:
            preprocessMainMenuOption(menu, option);
            break;
        case charSelectionMenu:
            preprocessCharMenuOption(menu, option);
            break;
        case gameMenu1:
            preprocessGameMenu1Option(menu, option);
            break;
        case gameMenu2:
            preprocessGameMenu2Option(menu, option);
            break;
    }
}

void preprocessMainMenuOption(GameMenu *menu, int option)
{
    switch (option)
    {
        case 1:
            menu->setRequest("Add a character: ");
            menu->waitingForOptionChoice = false;
            break;
        case 2:
            menu->setRequest("Delete a character: ");
            menu->waitingForOptionChoice = false;
            break;
        case 3:
            menu->setRequest("Showing all characters: ");
            menu->waitingForOptionChoice = false;
            break;
        case 4:
            menu->setRequest("Search character by name: ");
            menu->waitingForOptionChoice = false;
            break;
        case 5:
            menu->setRequest("Choose an option: ");
            menu->waitingForOptionChoice = true;
            menu->changeCurrentMenu(charSelectionMenu);
            break;
        case 6:
            menu->window->close();
            break;
        default:
            break;
    }
}

void preprocessCharMenuOption(GameMenu *menu, int option)
{
    switch (option)
    {
        case 1:
            menu->setRequest("Search character by name: ");
            menu->waitingForOptionChoice = false;
            break;
        case 2:
            menu->setRequest("Showing all characters: ");
            menu->waitingForOptionChoice = false;
            break;
        case 3:
            //menu->setRequest("Pick a character: ");
            //menu->waitingForOptionChoice = false;
            //orden: P1, P2, P1, P2, P1, P2
            //luego de que se eligen los 6 personajes tienen que posicionarlos
            menu->waitingForOptionChoice = true;
            menu->changeCurrentMenu(gameMenu1);
            break;
        case 4:
            menu->setRequest("Choose an option: ");
            menu->waitingForOptionChoice = true;
            menu->changeCurrentMenu(mainMenu);
            break;
        default:
            break;
    }
}

void preprocessGameMenu1Option(GameMenu *menu, int option)
{
    bool allCharactersPlayed = false;
    if (allCharactersPlayed) option = 4;

    switch (option)
    {
        case 1:
            menu->setRequest("The game was saved succesfully");
            // Aca se llamaria a la funcion que guarda la partida
            menu->changeCurrentMenu(mainMenu);
            menu->waitingForOptionChoice = true;
            break;
        case 2:
            menu->setRequest("Choose a character to feed: ");
            menu->waitingForOptionChoice = false;
            break;
        case 3:
            menu->setRequest("Enter where you would like to move: (ex: 2,5)");
            menu->waitingForOptionChoice = false;
            menu->waitingForValidInput = true;
            break;
        case 4:
            // Pasar opcion
            menu->waitingForOptionChoice = true;
            menu->changeCurrentMenu(gameMenu2);
            break;
        default:
            break;
    }
}

void preprocessGameMenu2Option(GameMenu *menu, int option)
{
    bool allCharactersPlayed = false;
    if (allCharactersPlayed) option = 3;

    switch (option)
    {
        case 1:
            menu->setRequest("Choose a character to attack with: ");
            menu->waitingForOptionChoice = false;
            break;
        case 2:
            menu->setRequest("Choose a character to defend: ");
            menu->waitingForOptionChoice = false;
            break;
        case 3:
            // Pasar opcion
            // cambiar de quien es el turno de jugar
            menu->waitingForOptionChoice = true;
            menu->changeCurrentMenu(gameMenu1);
            break;
        default:
            break;
    }   
}

void processUserInput(GameMenu *menu, std::string input)
{
    switch (menu->getCurrentMenuIndex())
    {
        case mainMenu:
            processMainMenuInput(menu, input);
            break;
        case charSelectionMenu:
            processCharMenuInput(menu, input);
            break;
        case gameMenu1:
            processGameMenu1Input(menu, input);
            break;
        case gameMenu2:
            processGameMenu2Input(menu, input);
            break;
    }
}

void processMainMenuInput(GameMenu *menu, std::string input)
{
    switch (menu->currentOption)
    {
        case 1:
            std::cout << "Agregar personaje" << std::endl;
            break;
        case 2:
            std::cout << "Eliminar personaje" << std::endl;
            break;
        case 3:
            std::cout << "Mostrar personajes" << std::endl;
            break;
        case 4:
            std::cout << "Buscar personaje" << std::endl;
            break;

        // En principio si la opcion es 5 o 6 no se llegaria a esta funcion
        default:
            break;
    }
    menu->waitingForOptionChoice = true;
}

void processCharMenuInput(GameMenu *menu, std::string input)
{
    switch (menu->currentOption)
    {
        case 1:
            std::cout << "Buscar personaje" << std::endl;
            break;
        case 2:
            std::cout << "Mostrar personajes" << std::endl;
            break;
        case 3:
            std::cout << "Seleccionar personaje" << std::endl;
            break;

        // En principio si la opcion es 4 no se llegaria a esta funcion
        default:
            break;
    }
    //if (charactersSelected == 6) currentMenu = characterPositioningMenu;
    menu->waitingForOptionChoice = true;
}

void processGameMenu1Input(GameMenu *menu, std::string input)
{
    Character* character = menu->window->world->player1Characters[0];
    sf::Vector2f destination;
    switch (menu->currentOption)
    {
        case 2:
            std::cout << "Alimentar personaje" << std::endl;
            menu->waitingForOptionChoice = true;
            break;
        case 3:
            if (!validDestinationFormat(input))
                menu->setRequest("Incorrect format, if you wanted to move to position X=0 Y=1, enter 0,1");
            else
            {
                destination = parseStringToVector2f(input);
                validateDestination(menu, character, destination); // cambia el estado de waitingForValidInput
            }

            if (!menu->waitingForValidInput)
            {
                processMoveChoice(menu->window, character, destination);
                menu->waitingForOptionChoice = true;
                menu->waitingForValidInput = false;
            }
            break;
        default:
            break;
    }  
}

void processGameMenu2Input(GameMenu *menu, std::string input)
{
    switch (menu->currentOption)
    {
        case 1:
            std::cout << "Atacar personaje" << std::endl;
            break;
        case 2:
            std::cout << "Defender personaje" << std::endl;
            break;
        default:
            break;
    }
    menu->waitingForOptionChoice = true;  
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
        {
            length++;
        }
    }
    else
    {
        cout << "FILE ERROR";
    }

    optionsFile.close();
    return length;
}

// ------------------------------------ MENU FUNCTIONALITY

void validateDestination(GameMenu *menu, Character *character, sf::Vector2f destination)
{
    GameWorld* world = menu->window->world;
    int energyRequired = world->distances
                            [static_cast<int>(character->getElement()) - 1]
                            [int(character->getPos().x + 8 * character->getPos().y)]
                            [int(destination.x + 8 * destination.y)];

    if (destination.x < 0 || destination.x > 7 || destination.y < 0 || destination.y > 7)
        menu->setRequest("Invalid destination. Try a different one");
    else if (world->tiles[destination.x + 8 * destination.y]->isOccupied())
        menu->setRequest("You can't move there, the cell is occupied. Try a different one");
    else if (energyRequired > character->getEnergy())
        menu->setRequest("You can't move there, you lack energy. Try a different one");
    else
        menu->waitingForValidInput = false;
}