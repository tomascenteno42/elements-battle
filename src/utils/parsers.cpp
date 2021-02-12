#include "../main.h"

elements parseStringToElement(string stringToParse)
{
	std::transform(stringToParse.begin(), stringToParse.end(), stringToParse.begin(), [](unsigned char c){ return std::tolower(c); });

    if (stringToParse == "air")
        return AIR;
    if (stringToParse == "earth")
        return EARTH;
    if (stringToParse == "fire")
        return FIRE;
    if (stringToParse == "water")
        return WATER;
}

terrains parseStringToTerrain(string stringToParse)
{
    if (stringToParse == "l")
        return lake;
    else if (stringToParse == "v")
        return volcano;
    else if (stringToParse == "c")
        return cliff;
    else if (stringToParse == "m")
        return mountain;
    else if (stringToParse == "p")
        return path;
    else
        return empty;
}

sf::Color parseTerrainToSf(terrains terrain)
{

    switch (terrain)
    {
    case lake:
        return sf::Color(102,230,244); //Cyan
        break;
    case volcano:
        return sf::Color(231,69,65); //Red
        break;
    case cliff:
        return sf::Color(219,238,244); //White
        break;
    case mountain:
        return sf::Color(74,69,42); //Brown
        break;
    case path:
        return sf::Color(196,189,151); //Beige
        break;
    case empty:
        return sf::Color(96,74,123); //Purple
        break;
    default:
        return sf::Color::Blue;
        break;
    }
}

sf::Vector2f parseStringToVector2f(std::string input)
{
    int pos = input.find(",");
    std::string s1 = input.substr(0, pos);
    std::string s2 = input.substr(pos+1, input.length());
    return sf::Vector2f(stof(s1), stof(s2));
}

std::string parseElementToString(elements element)
{
    switch (element)
    {
        case AIR:
            return "air";
            break;
        case EARTH:
            return "earth";
            break;
        case FIRE:
            return "fire";
            break;
        case WATER:
            return "water";
            break;
        default:
            break;
    }
}

