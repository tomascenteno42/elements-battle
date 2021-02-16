#include "../main.h"

/* UTILS */

bool dataIsInVector(std::vector<int> vector, int data)
{
    for (int i = 0; i < vector.size(); i ++)
    {
        if (vector[i] == data)
            return true;
    }
    return false;
}

Character* createNewCharacter(elements element, std::string name, float maxLife, int shield)
{
    Character* character = 0;
    switch (element)
    {
        case AIR:
            character = new AirCharacter(name, maxLife, shield);
            break;
        case EARTH:
            character = new EarthCharacter(name, maxLife, shield);
            break;
        case FIRE:
            character = new FireCharacter(name, maxLife, shield);
            break;
        case WATER:
            character = new WaterCharacter(name, maxLife, shield);
            break;
        default:
            break;                                                                
    }
    return character;
}