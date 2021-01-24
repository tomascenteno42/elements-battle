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

terrains parseStringToColor(string colorToParse)
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
        return sf::Color::Cyan;
        break;
    case volcano:
        return sf::Color::Red;
        break;
    case cliff:
        return sf::Color::White;
        break;
    case mountain:
        return sf::Color::Black;
        break;
    case path:
        return sf::Color::Yellow;
        break;
    case empty:
        return sf::Color::Magenta;
        break;
    default:
        return sf::Color::Blue;
        break;
    }
}