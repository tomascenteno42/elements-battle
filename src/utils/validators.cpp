#include "../main.h"

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
