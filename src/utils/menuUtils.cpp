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

void renderMenu(List *l, GameWindow *window)
{
    int choice = 1;

    if (choice >= 1 && choice < window->menu->GetChosenMenu()->getLength())
    {
        choice = getUserChoice(window);
        cout << "Choice: " << choice << endl;
        //validateUserChoice(choice, window->menu->GetChosenMenu()->getLength());

        if (window->menu->GetChosenMenu()->getLength() == 6)
        {
            renderMenuOption(l, choice, window);
            cout << "First Menu Options rendered" << endl;
        }
        else 
        {
            renderMenuOption2(l, choice, window);
            cout << "Second Menu Options rendered" << endl;
        }
    }
}

void renderMenuOption(List *l, int option, GameWindow* window)
{
    switch (option)
    {
    case 1:
        //addCharacter(l);
        break;
    case 2:
        //showAllCharactersNames(l);
        //eraseCharacter(l);
        break;
    case 3:
        //showAllCharactersNames(l);
        break;
    case 4:
        break;
    case 5:
        window->menu->ChangeChosen(2);
        cout << "REASSIGNED CHOSEN" << endl;
        break;
    case 6:
        window->clear();
        break;
    default:
        break;
    }
}

void renderMenuOption2(List *l, int option, GameWindow* window)
{
    switch (option)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        window->menu->ChangeChosen(1);
        cout << "REASSIGNED CHOSEN 2" << endl;
        break;
    default:
        break;
    }
}

void showMenuOptions(GameWindow* window)
{
    sf::Font font;
	font.loadFromFile(FONT_FILE);
    float pos = 410;

    for (int i = 0; i < window->menu->GetChosenMenu()->getLength(); i++)
    {
        sf::Text texto((to_string((i + 1)) + ") " + window->menu->GetChosenMenu()->getOption(i)), font, 20);
        texto.setFillColor(sf::Color::White);
	    texto.setPosition(sf::Vector2f(10, pos));
        pos += 50;
        window->draw(texto);
    }
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
