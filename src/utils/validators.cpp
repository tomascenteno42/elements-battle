#include "../main.h"

// Devuelve true si input tiene el formato numero,numero donde ambos numeros estan entre 0 y 7
bool validPosition(std::string input)
{
    int pos = input.find(",");
    if (pos == -1) return false;
    std::string s1 = input.substr(0, pos);
    std::string s2 = input.substr(pos+1, input.length());
    if (!stringIsNumeric(s1) || !stringIsNumeric(s2)) return false;

    return (stof(s1) >= 0 && stof(s1) <= 7 && stof(s2) >= 0 && stof(s2) <= 7);
}

bool validDestinationEnergy(GameWorld *world, Character *character, sf::Vector2f destination)
{
    int energyRequired = world->distances
                            [static_cast<int>(character->getElement()) - 1]
                            [int(character->getPos().x + 8 * character->getPos().y)]
                            [int(destination.x + 8 * destination.y)];

    return (energyRequired <= character->getEnergy());
}

bool positionIsEmpty(GameWorld* world, sf::Vector2f destination)
{
    return (!world->tiles[destination.x + 8 * destination.y]->isOccupied());
}

bool validMoveDestination(GameMenu* menu, Character* character, sf::Vector2f destination)
{
    if (!positionIsEmpty(menu->window->world, destination) && destination != character->getPos())
    {
        menu->setRequest("You can't move there, the cell is occupied. Try a different one");
        return false;
    }
    if (!validDestinationEnergy(menu->window->world, character, destination))
    {
        menu->setRequest("You can't move there, you lack energy. Try a different one");
        return false;
    }
    return true;
}