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
    
    if (!menu->waitingForOptionChoice)
        processUserInput(menu, input);
        // En este caso no se elige opcion del menu, ya se está en una opción y se está ingresando lo pedido
    else
    {
        if (input == "" || !stringIsNumeric(input) || stoi(input) < 1 || stoi(input) > menu->getCurrentMenu()->getLength())
            menu->setRequest("Enter a valid choice: ");
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
        case 1:     // Agregar pj
            menu->setRequest("Add a character: ");
            menu->waitingForOptionChoice = false;
            break;
        case 2:     // Eliminar pj
            menu->setRequest("Delete a character: ");
            menu->waitingForOptionChoice = false;
            break;
        case 3:     // Mostrar pjs
            menu->waitingForOptionChoice = true;
            break;
        case 4:     // Buscar pj
            menu->setRequest("Search character by name: ");
            menu->waitingForOptionChoice = false;
            break;
        case 5:     // Empezar juego
            menu->waitingForOptionChoice = true;
            menu->changeCurrentMenu(charSelectionMenu);
            break;
        case 6:     // Cerrar
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
        case 1:     // Buscar pj
            menu->setRequest("Search character by name: ");
            menu->waitingForOptionChoice = false;
            break;
        case 2:     // Mostrar pjs
            menu->waitingForOptionChoice = true;
            break;
        case 3:     // Seleccionar pj
            //menu->setRequest("Pick a character: ");
            //menu->waitingForOptionChoice = false;
            //orden: P1, P2, P1, P2, P1, P2
            //luego de que se eligen los 6 personajes tienen que posicionarlos
            menu->waitingForOptionChoice = true;
            menu->changeCurrentMenu(gameMenu1);
            break;
        case 4:     // Salir
            menu->waitingForOptionChoice = true;
            menu->changeCurrentMenu(mainMenu);
            break;
        default:
            break;
    }
}

void preprocessGameMenu1Option(GameMenu *menu, int option)
{
    Character* character = menu->window->world->currentCharacter;
    
    switch (option)
    {
        case 1:     // Guardar
            // Aca se llamaria a la funcion que guarda la partida
            menu->changeCurrentMenu(mainMenu);
            menu->waitingForOptionChoice = true;
            break;
        case 2:     // Alimentar
            character->feed();
            if (character->getElement() != AIR)
                menu->changeCurrentMenu(gameMenu2);
            menu->waitingForOptionChoice = true;
            break;
        case 3:     // Mover
            menu->setRequest("Enter where you would like to move: (ex: 2,5)");
            menu->waitingForOptionChoice = false;
            menu->waitingForValidInput = true;
            break;
        case 4:     // Pasar
            menu->waitingForOptionChoice = true;
            menu->changeCurrentMenu(gameMenu2);
            break;
        default:
            break;
    }
}

void preprocessGameMenu2Option(GameMenu *menu, int option)
{
    Character* character = menu->window->world->currentCharacter;

    switch (option)
    {
        case 1:     // Attack (further input is required only if the element is water)
            if (character->getElement() == WATER)
            {
                menu->setRequest("Attack at position (example: 2,5): ");
                menu->waitingForOptionChoice = false;
                menu->waitingForValidInput = true;
                break;
            }

            if (menu->window->world->currentPlayer == 1)
                character->attack(menu->window->world->player2Characters, {-1,-1});
            else
                character->attack(menu->window->world->player1Characters, {-1,-1});

            menu->waitingForOptionChoice = true;
            menu->changeCurrentMenu(gameMenu1);
            break;

        case 2:     // Defend (further input is required only if the element is air)
            if (character->getElement() == AIR)
            {
                menu->setRequest("Move to position (example: 2,5): ");
                menu->waitingForOptionChoice = false;
                menu->waitingForValidInput = true;
                break;
            }

            if (menu->window->world->currentPlayer == 1)
                character->defend(menu->window->world->player1Characters, {-1,-1});
            else
                character->defend(menu->window->world->player2Characters, {-1,-1});

            menu->waitingForOptionChoice = true;
            menu->changeCurrentMenu(gameMenu1);
            break;

        case 3:     // Pasar
            menu->waitingForOptionChoice = true;
            menu->changeCurrentMenu(gameMenu1);
            break;

        default:
            break;
    }
    if (menu->waitingForOptionChoice)
        menu->window->world->advanceState(); // terminó el turno del jugador actual
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
    // Aca van las opciones del mainMenu que requieren input del usuario
    switch (menu->currentOption)
    {
        case 1:     // Agregar pj
            std::cout << "Agregar personaje" << std::endl;
            break;
        case 2:     // Eliminar pj
            std::cout << "Eliminar personaje" << std::endl;
            break;
        case 4:     // Buscar pj
            std::cout << "Buscar personaje" << std::endl;
            break;

        default:
            break;
    }
    menu->waitingForOptionChoice = true;
}

void processCharMenuInput(GameMenu *menu, std::string input)
{
    // Aca van las opciones del charMenu que requieren input del usuario
    switch (menu->currentOption)
    {
        case 1:     // Buscar pj
            std::cout << "Buscar personaje" << std::endl;
            break;
        case 3:     // Seleccionar pj
            std::cout << "Seleccionar personaje" << std::endl;
            break;

        default:
            break;
    }
    //if (charactersSelected == 6) currentMenu = characterPositioningMenu;
    menu->waitingForOptionChoice = true;
}

void processGameMenu1Input(GameMenu *menu, std::string input)
{
    // Aca van las opciones del gameMenu1 que requieren input del usuario
    Character* character = menu->window->world->currentCharacter;
    sf::Vector2f destination;
    switch (menu->currentOption)
    {
        case 3:     // Mover
            if (!validPosition(input))
                menu->setRequest("Invalid position. Enter X,Y with X and Y between 0 and 7");
            else
            {
                destination = parseStringToVector2f(input);
                validateDestination(menu, character, destination); // cambia el estado de waitingForValidInput
            }

            if (!menu->waitingForValidInput)
            {
                processMoveChoice(menu->window, character, destination);
                menu->waitingForOptionChoice = true;
                menu->changeCurrentMenu(gameMenu2);
            }
            break;
        default:
            break;
    }  
}

void processGameMenu2Input(GameMenu *menu, std::string input)
{
    // Aca van las opciones del gameMenu2 que requieren input del usuario
    Character* character = menu->window->world->currentCharacter;
    sf::Vector2f position;
    switch (menu->currentOption)
    {
        case 1:     // Atacar (solo el personaje de agua necesita esto)
            if (!validPosition(input))
                menu->setRequest("Invalid position. Enter X,Y with X and Y between 0 and 7");
            else
            {
                menu->waitingForValidInput = false;
                position = parseStringToVector2f(input);
            }

            if (!menu->waitingForValidInput)
            {
                if (menu->window->world->currentPlayer == 1)
                    character->attack(menu->window->world->player2Characters, position);
                else
                    character->attack(menu->window->world->player1Characters, position);
                menu->waitingForOptionChoice = true;
                menu->changeCurrentMenu(gameMenu1);
            }

            break;

        case 2:     // Defender (solo el personaje de aire necesita esto)
            if (!validPosition(input))
                menu->setRequest("Invalid position. Enter X,Y with X and Y between 0 and 7");
            else
            {
                menu->waitingForValidInput = false;
                position = parseStringToVector2f(input);
            }

            if (!menu->waitingForValidInput)
            {
                if (menu->window->world->currentPlayer == 1)
                    character->defend(menu->window->world->player2Characters, position);
                else
                    character->defend(menu->window->world->player1Characters, position);
                menu->waitingForOptionChoice = true;
                menu->changeCurrentMenu(gameMenu1);
            }

            break;
        default:
            break;
    }
    menu->window->world->advanceState();
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



