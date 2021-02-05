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

bool validDestinationFormat(std::string input)
{
    int pos = input.find(",");
    if (pos == -1) return false;
    std::string s1 = input.substr(0, pos);
    std::string s2 = input.substr(pos+1, input.length());
    return (stringIsNumeric(s1) && stringIsNumeric(s2));
}