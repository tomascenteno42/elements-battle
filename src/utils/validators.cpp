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

// Devuelve true si input tiene el formato numero,numero donde ambos numeros estan entre 0 y 7
bool validPosition(std::string input)
{
    int pos = input.find(",");
    if (pos == -1) return false;
    std::string s1 = input.substr(0, pos);
    std::string s2 = input.substr(pos+1, input.length());
    std::cout << s1 << "\t" << s2 << std::endl;
    std::cout << stringIsNumeric(s1) << "\t" << stringIsNumeric(s2) << std::endl;
    if (!stringIsNumeric(s1) || !stringIsNumeric(s2)) return false;

    return (stof(s1) >= 0 && stof(s1) <= 7 && stof(s2) >= 0 && stof(s2) <= 7);
}


void validateDestination(GameMenu *menu, Character *character, sf::Vector2f destination)
{
    GameWorld* world = menu->window->world;
    int energyRequired = world->distances
                            [static_cast<int>(character->getElement()) - 1]
                            [int(character->getPos().x + 8 * character->getPos().y)]
                            [int(destination.x + 8 * destination.y)];

    if (world->tiles[destination.x + 8 * destination.y]->isOccupied())
        menu->setRequest("You can't move there, the cell is occupied. Try a different one");
    else if (energyRequired > character->getEnergy())
        menu->setRequest("You can't move there, you lack energy. Try a different one");
    else
        menu->waitingForValidInput = false;
}