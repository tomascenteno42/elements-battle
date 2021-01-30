#include "../../src/main.h"

Menu::Menu(int quantiy)
{
    length = quantiy;
    options = new string[length];
}

void Menu::addOption(string opcion)
{
    options[index] = opcion;
    index++;
}

string Menu::getOption(int i)
{
    return options[i];
}

int Menu::getLength()
{
    return length;
}

void Menu::showAllOptions()
{
    for (int i = 0; i < length; i++)
    {
        cout << i + 1 << ") " << getOption(i) << endl;
    }
}

Menu::~Menu()
{
    delete[] options;
}
