#include "../main.h"

void validateUserChoice(int &option, int menuLength)
{
    while (option < 1 || option > menuLength)
    {
        cout << endl
             << endl;
        cout << "Incorrect option" << endl;
        cout << "Enter new option: ";
        cin >> option;
    }
}

void validateElement(string &element)
{
    while (element != "Air" && element != "Fire" && element != "Water" && element != "Earth" && element != "air" && element != "fire" && element != "water" && element != "earth")
    {
        cout << "Wrong element, please try again. " << endl;
        cout << "The options are (Fire, Water, Air, Earth). ";
        cin >> element;
        cout << element;
    }
}
