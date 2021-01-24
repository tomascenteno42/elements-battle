#include "../main.h"

// MENU UTILS

void fillMenu(Menu *m)
{
    ifstream optionsFile;
    string option;

    optionsFile.open(OPTIONS_FILE);
    if (optionsFile.is_open())
    {
        while (getline(optionsFile, option, '\n'))
        {
            (*m).addOption(option);
        }
    }
    optionsFile.close();
}

void renderMenu(Menu *m, List *l)
{
    int choice = 1;

    while (choice >= 1 && choice < m->getLength())
    {
        renderGameTitle();
        printBlankLine();

        cout << "MENU";

        printBlankLine();

        m->showAllOptions();

        cout << "Option: ";
        choice = getUserChoice();
        validateUserChoice(choice, m->getLength());

        if (choice != m->getLength())
        {
            renderMenuOption(l, choice);
            waitForEnter();
            clearScreen();
        }
    }
}

void renderMenuOption(List *l, int option)
{
    clearScreen();

    switch (option)
    {
    case 1:
        addCharacter(l);
        break;
    case 2:
        showAllCharactersNames(l);
        eraseCharacter(l);
        break;
    case 3:
        showAllCharactersNames(l);
        break;
    case 4:
        showAllCharactersNames(l);
        searchCharacterStats(l);
        break;
    case 5:
        showAllCharactersNames(l);
        feedCharacter(l);
        break;
    }
}

void showMenuOptions(Menu *m)
{
    for (int i = 0; i < m->getLength(); i++)
    {
        cout << i + 1 << ") " << m->getOption(i) << endl;
    }
}

int getAmountOfOptions()
{
    ifstream optionsFile;
    string option;
    int length = 0;

    optionsFile.open(OPTIONS_FILE);

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

    clearScreen();
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
        clearScreen();
        cout << name << " has been erased from the game." << endl;
    }
    else
        notFoundCharacterNameError();
}

// option 3
void showAllCharactersNames(List *l)
{
    cout << "Characters: ";

    printBlankLine();

    for (int i = 1; i <= l->getQuantity(); i++)
    {
        cout << "Character " << i << ": ";
        cout << l->get(i)->getName() << endl;
    }
    printBlankLine();
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
        clearScreen();
        showCharacterStatsByIndex(l, index);
    }
    else
        notFoundCharacterNameError();
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
        clearScreen();
        feedCharacterByIndex(l, index);
    }
    else
        notFoundCharacterNameError();
}
