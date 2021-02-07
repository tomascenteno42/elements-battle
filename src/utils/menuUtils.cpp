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
            m->addOption(option);
        }
    }
    optionsFile.close();
}


void processAddCharacter(GameMenu *menu)
{
    std::string input;
    menu->setRequest("Add a character: ");
    input = getUserInput(menu->window);
    std::cout << "Added character " << input << std::endl;
}

void processDeleteCharacter(GameMenu *menu)
{
    std::string input;
    menu->setRequest("Delete a character: ");
    input = getUserInput(menu->window);
    std::cout << "Deleted character " << input << std::endl;            
}

void processSearchCharacter(GameMenu *menu)
{
    std::string input;
    menu->setRequest("Search character by name: ");
    input = getUserInput(menu->window);
    std::cout << "Searched character " << input << std::endl;            
}

void processShowCharacters(GameMenu *menu)
{
    std::cout << "Showing all characters" << std::endl;
}

void processSaveGame(GameMenu *menu)
{
    std::cout << "Saved succesfully" << std::endl;
}

void processFeedOption(GameMenu *menu)
{
    Character* character = menu->window->world->currentCharacter;
    character->feed();
    if (character->getElement() != AIR)
        menu->changeCurrentMenu(gameMenu2);
}

void processMoveOption(GameMenu *menu)
{
    Character* character = menu->window->world->currentCharacter;
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
}

void processAttackOption(GameMenu *menu)
{
    Character* character = menu->window->world->currentCharacter;
    character->attack(menu->window);
}

void processDefenseOption(GameMenu *menu)
{
    Character* character = menu->window->world->currentCharacter;
    character->defend(menu->window);
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