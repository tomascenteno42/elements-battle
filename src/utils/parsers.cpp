#include "../main.h"

elements parseStringToElement(string stringToParse)
{
    // THIS 2 LINES REMOVES '\n' from e
    regex newlines_re("\n+");
    string result = regex_replace(stringToParse, newlines_re, "");

    if (result == "Fire" || result == "fire")
    {
        return FIRE;
    }
    else if (result == "Air" || result == "air")
    {
        return AIR;
    }
    else if (result == "Water" || result == "water")
    {
        return WATER;
    }
    else // PARA EVITAR ERRORES (escribir mal el elemento en characters.csv) COLOQUE COMO DEFAULT EL CASO DE EARTH
    {
        return EARTH;
    }
}
string parseElementToString(elements elementToParse)
{
    switch (elementToParse)
    {
    case FIRE:
        return "Fire";
    case WATER:
        return "Water";
    case EARTH:
        return "Earth";
    case AIR:
        return "Air";
    default:
        return "ELEMENTO INCOMPATIBLE.";
    }
}

terrains parseStringToTerrain(string colorToParse)
{
    if (colorToParse == "l")
    {
        return lake;
    }
    else if (colorToParse == "v")
    {
        return volcano;
    }
    else if (colorToParse == "c")
    {
        return cliff;
    }
    else if (colorToParse == "m")
    {
        return mountain;
    }
    else if (colorToParse == "p")
    {
        return path;
    }
    else
    {
        return empty;
    }
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

