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

void renderMenu(List *l, GameMenu *menu)
{
    std::string input = menu->textbox->getText();
    
    if (!menu->waitingForOptionChoice)
        processUserInput(menu, input);  // En este caso no se elige opcion del menu, ya se está en una opción y se está ingresando lo pedido
    else
    {
        if (!(stringIsNumeric(input) && stoi(input) >= 1 && stoi(input) <= menu->getCurrentMenu()->getLength()))
            menu->request.setString("Enter a valid choice: ");
        else
            processOptionChoice(menu, stoi(input)); // Se actualiza el mensaje de request según la opción del menú que se elija
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
            menu->setRequest("Bye");
            menu->waitingForOptionChoice = true;
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
            menu->setRequest("Pick a character: ");
            menu->waitingForOptionChoice = false;
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

void preprocessGameMenu1Option(GameMenu *menu, int option) {}
void preprocessGameMenu2Option(GameMenu *menu, int option) {}

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
}

void processGameMenu1Input(GameMenu *menu, std::string input) {}
void processGameMenu2Input(GameMenu *menu, std::string input) {}


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

/* MENU OPTIONS FUNCTIONALITY */

// option 1
void addCharacter(List *l)
{
    string line[3];
    string name;
    string element;

    cout << "Name of the character: ";
    cin >> line[0];

    cout << "Element of the character(Fire, Water, Earth, Air): ";
    cin >> element;

    validateElement(element);
    addCharacterToList(l, l->getQuantity() + 1, line, element);

    //clearScreen();
    cout << line[0] << " was added to the game!" << endl;
}

// option 2
void eraseCharacter(List *l)
{
    string name;
    int index = 0;

    cout << "Name of the character to erase: ";
    cin >> name;

    index = getIndexByCharacterName(l, name);

    if (index != 0)
    {
        l->drop(index);
        //clearScreen();
        cout << name << " has been erased from the game." << endl;
    }
    //else
        //notFoundCharacterNameError();
}

// option 3
void showAllCharactersNames(List *l)
{
    cout << "Characters: ";

    //printBlankLine();

    for (int i = 1; i <= l->getQuantity(); i++)
    {
        cout << "Character " << i << ": ";
        cout << l->get(i)->getName() << endl;
    }
    //printBlankLine();
}

//option 4
void searchCharacterStats(List *l)
{
    string name;
    int index = 0;
    cout << "Name of character you will like to see stats of: ";
    cin >> name;
    index = getIndexByCharacterName(l, name);
    if (index != 0)
    {
        //clearScreen();
        showCharacterStatsByIndex(l, index);
    }
    //else
        //notFoundCharacterNameError();
}

//option 5
void feedCharacter(List *l)
{
    string name;
    int index = 0;
    cout << "Name of character you will like to feed: ";
    cin >> name;
    index = getIndexByCharacterName(l, name);
    if (index != 0)
    {
        //clearScreen();
        feedCharacterByIndex(l, index);
    }
    //else
        //notFoundCharacterNameError();
}
