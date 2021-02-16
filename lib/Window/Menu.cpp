#include "../../src/main.h"

Menu::Menu(int length)
{
    this->length = length;
    options = new string[length];
}

void Menu::addOption(string option)
{
    options[index] = option;
    index ++;
}

string Menu::getOption(int i)
{
    return options[i];
}

int Menu::getLength()
{
    return length;
}

Menu::~Menu()
{
    delete[] options;
}
