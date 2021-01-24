#include "../main.h"

/* UTILS */

int getUserChoice()
{
    int choice = 0;
    cin >> choice;

    return choice;
}

void notFoundCharacterNameError()
{
    cout << "A character with that name couldn't be found" << endl;
}

void waitForEnter()
{
    cout << endl
         << endl
         << "Press ENTER to continue..." << endl;
    cin.get();
    cin.get();
}

void clearScreen()
{
    cout << string(25, '\n');
}

void renderGameTitle()
{
    cout << "WELCOME TO BATTLE OF THE ELEMENTS";
}

void printBlankLine()
{
    cout << endl
         << endl;
}