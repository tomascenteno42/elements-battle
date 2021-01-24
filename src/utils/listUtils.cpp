#include "../main.h"

/* LIST */

void fillList(List *l)
{
    int filePosition = 0;
    int index = 1;
    string line[3];
    string element;

    ifstream personajes;

    personajes.open(CHARACTERS_FILE);

    if (personajes.is_open())
    {
        while (getline(personajes, line[0], '\n'))
        {
            element = getCharacterElementFromFile(filePosition);
            filePosition += (int)element.length() + 1;

            getCharacterDataFromFile(filePosition, line);
            filePosition += (int)line[0].length() + (int)line[1].length() + (int)line[2].length() + 2;

            addCharacterToList(l, index, line, element);
            index++;
        }
    }
    personajes.close();
}

void addCharacterToList(List *l, int index, string line[], string element)
{
    Character *character = 0;

    string name = line[0];
    int life = 0;
    int shield = 0;

    if (line[1] == "")
        shield = rand() % 3;
    else
        shield = stoi(line[1]);

    if (line[2] == "")
        life = rand() % 100 + 10;
    else
        life = stoi(line[2]);

    switch (parseStringToElement(element))
    {
    case AIR:
    {
        character = new AirCharacter(name, AIR, life, shield);
        (*l).add(character, index);
        break;
    }
    case FIRE:
    {
        character = new FireCharacter(name, FIRE, life, shield);
        (*l).add(character, index);
        break;
    }
    case WATER:
    {
        character = new WaterCharacter(name, WATER, life, shield);
        l->add(character, index);
        break;
    }
    case EARTH:
    {
        character = new EarthCharacter(name, EARTH, life, shield);
        (*l).add(character, index);
        break;
    }
    }
}

string getCharacterElementFromFile(int position)
{

    ifstream archivo;
    string element;

    archivo.open(CHARACTERS_FILE);
    archivo.seekg(position, ios::beg);

    getline(archivo, element, ',');

    archivo.close();
    return element;
}

void getCharacterDataFromFile(int position, string line[])
{
    ifstream archivo;

    archivo.open(CHARACTERS_FILE);
    archivo.seekg(position, ios::beg);

    getline(archivo, line[0], ',');
    getline(archivo, line[1], ',');
    getline(archivo, line[2], '\n');
}

/* LIST UTILITY FUNCTIONS */
void feedCharacterByIndex(List *l, int index)
{
    l->get(index);
    l->get(index)->feed();
}

void showCharacterStatsByIndex(List *l, int index)
{
    Character *c = l->get(index);
    cout << "Name: " << c->getName() << endl;
    cout << "Element: " << parseElementToString(c->getElement()) << endl;
    cout << "Vida: " << c->getLife() << endl;
    cout << "Escudo: " << c->getShield() << endl;
    cout << "Energia: " << c->getEnergy() << endl;
}

int getIndexByCharacterName(List *l, string name)
{
    for (int i = 1; i <= l->getQuantity(); i++)
    {
        if (l->get(i)->getName() == name)
        {
            return i;
        }
    }
    return 0;
}
