#include "../main.h"

/* UTILS */

bool stringIsNumeric(std::string s)
{
    for(int i = 0; i < (s.length() - 1); i ++) {
        if ((int)s[i] >= 10) {
            return false;
        }
    }
    return true;
}

int getUserChoice(GameMenu* menu)
{
    int choice = 0;
    
    choice = stoi(menu->textbox->getText());

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