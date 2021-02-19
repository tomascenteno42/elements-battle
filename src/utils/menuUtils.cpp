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


void processAddCharacter(GameMenu *menu, BST<string, Character*>* characterMap)
{
	string elementStr, name, shieldStr, maxLifeStr;
    Character* character = 0;
    elementStr = getCharElementFromUser(menu);
    name = getCharNameFromUser(menu);
    shieldStr = getCharShieldFromUser(menu);
    maxLifeStr = getCharLifeFromUser(menu);
    character = createNewCharacterFromStrings(elementStr, name, maxLifeStr, shieldStr);
    characterMap->insert(name, character);
    menu->window->stats->setCharacterList(characterMap->keysInOrder());
}

void processDeleteCharacter(GameMenu *menu, BST<string, Character*>* characterMap)
{
    std::string name;
    menu->setRequest("Delete character named: ");
    name = getUserInput(menu->window);
    if (characterMap->search(name)){
        characterMap->erase(name);
        menu->window->stats->setCharacterList(characterMap->keysInOrder());
    }
    else
        menu->setRequest("That character does not exist. Choose an option");
}

void processSearchCharacter(GameMenu *menu, BST<string, Character*>* characterMap)
{
    std::string name;
    menu->setRequest("Search character by name: ");
    name = getUserInput(menu->window);
    Character *character = 0;
    if (characterMap->search(name))
    {
        character = characterMap->getData(name);
        menu->window->stats->setCharacterDetails(character);
        menu->window->stats->showCharacterDetails = true;
    }
    else
        menu->setRequest("That character does not exist. Choose an option");
}

void processShowCharacters(GameMenu *menu, BST<string, Character*>* characterMap)
{
    std::vector<std::string> names = characterMap->keysInOrder();
    menu->window->stats->setCharacterList(names);
    menu->window->stats->showCharacterList = true;
}

void processCharacterSelection(GameMenu* menu, BST<string, Character*>* characterMap)
{
    menu->window->stats->showChosenChar = true;

    std::string name;
    menu->setRequest("Select character by name: ");
    name = getCharNameFromUser(menu);
    Character* character = 0;
    int player = menu->window->world->charactersSelected % 2;
    if (characterMap->search(name) && !menu->window->world->characterIsInGame(name))
    {
        character = characterMap->getData(name);
        menu->window->world->players[player]->addCharacter(character);
        menu->window->stats->setChosenCharacters(character->getName(), menu->window->world->charactersSelected);
        menu->window->world->charactersSelected ++;
        menu->setRequest("Choose an option");
    }
    else
        menu->setRequest("Either that character is already selected or it does not exist. Choose an option");
}


void processCharacterPositioning(GameMenu* menu)
{
    int player = rand() % 1;
    int index;
    Character* character = 0;
    sf::Vector2f pos;
    for (int i = 0; i < 6; i ++)
    {
        if (i == 0 || i == 1)
            index = 0;
        else if (i == 2 || i == 3)
            index = 1;
        else
            index = 2;

        character = menu->window->world->players[player]->characters[index];

        bool validPos = false;
        menu->setRequest("Position character " + character->getName() +  " at: (ex.: 2,5)");
        while (!validPos)
        {
            pos = getPositionFromUser(menu);
            if (positionIsEmpty(menu->window->world, pos))
                validPos = true;
            else
                menu->setRequest("That cell is occupied, choose a different one");
        }
        character->setPos(pos);
        menu->window->world->tiles->getData(1 + pos.x + 8*pos.y)->data->setOccupied(true);
        player = (player + 1) % 2;
    }
    menu->window->stats->showCharacterList = false;
}


void processLoadGame(GameMenu* menu, BST<string, Character*>* characterMap)
{
    fstream file;
    file.open(SAVE_FILE, ios::in);

    if (file.is_open())
    {
        loadGameData(file, menu->window->world, characterMap);
        file.close();
        menu->changeCurrentMenu(gameMenu1);
    }
    else
    {
        menu->window->setWorld(new GameWorld());
        menu->changeCurrentMenu(charSelectionMenu);
    }
}


void processSaveGame(GameMenu *menu)
{
    if (menu->window->world->canSave)
    {
        saveGameData(menu->window->world);
        menu->window->setWorld(new GameWorld());
        menu->changeCurrentMenu(mainMenu);
        menu->setRequest("Choose an option");
    }
    else
        menu->setRequest("Saving is only available at the beggining of the turn. Choose another option: ");
}


void processFeedOption(GameMenu *menu)
{
    Character* character = menu->window->world->currentCharacter;
    character->feed(menu->window);
    if (character->getElement() != AIR)
    {
        menu->changeCurrentMenu(gameMenu2);
        menu->setRequest("Choose an option");
    }
    else
        menu->setRequest("You can't feed an air character. Choose another option: ");
}


void processMoveOption(GameMenu *menu)
{
    Character* character = menu->window->world->currentCharacter;
    sf::Vector2f destination = getDestinationFromUser(menu);

    if (destination == character->getPos())
    {
        menu->changeCurrentMenu(gameMenu2);
        menu->setRequest("Choose an option");   
        return;
    }

    int energyRequired = menu->window->world->distances
                        [static_cast<int>(character->getElement()) - 1]
                        [int(character->getPos().x + 8 * character->getPos().y)]
                        [int(destination.x + 8 * destination.y)];
                            
    character->move(menu->window, destination, energyRequired);

    menu->window->world->updateOccupiedStates();
    menu->changeCurrentMenu(gameMenu2);
    menu->setRequest("Choose an option");
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


void endGame(GameMenu *menu)
{
    remove(SAVE_FILE);

    if (menu->window->world->players[0]->lost())
        menu->window->stats->setInfoText("PLAYER 2 WON");
    else
        menu->window->stats->setInfoText("PLAYER 1 WON");

    menu->setRequest("Enter any text to return to main menu");
    getUserInput(menu->window);
    menu->changeCurrentMenu(mainMenu);
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