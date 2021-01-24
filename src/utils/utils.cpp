#include "../main.h"
#include "utils.h"

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
    std::string element;

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

//MENU

void fillMenu(Menu *m)
{
    ifstream optionsFile;
    string option;

    optionsFile.open(OPTIONS_FILE);
    if (optionsFile.is_open())
    {
        while (getline(optionsFile, option, '\n'))
        {
            (*m).addOption(option);
        }
    }
    optionsFile.close();
}

void renderMenu(Menu *m, List *l)
{
    int choice = 1;

    while (choice >= 1 && choice < m->getLength())
    {
        renderGameTitle();
        printBlankLine();

        cout << "MENU";

        printBlankLine();

        m->showAllOptions();

        cout << "Option: ";
        choice = getUserChoice();
        validateUserChoice(choice, m->getLength());

        if (choice != m->getLength())
        {
            renderMenuOption(l, choice);
            waitForEnter();
            clearScreen();
        }
    }
}

void renderMenuOption(List *l, int option)
{
    clearScreen();

    switch (option)
    {
    case 1:
        addCharacter(l);
        break;
    case 2:
        showAllCharactersNames(l);
        eraseCharacter(l);
        break;
    case 3:
        showAllCharactersNames(l);
        break;
    case 4:
        showAllCharactersNames(l);
        searchCharacterStats(l);
        break;
    case 5:
        showAllCharactersNames(l);
        feedCharacter(l);
        break;
    }
}

void showMenuOptions(Menu *m)
{
    for (int i = 0; i < m->getLength(); i++)
    {
        cout << i + 1 << ") " << m->getOption(i) << endl;
    }
}

int getAmountOfOptions()
{
    ifstream optionsFile;
    string option;
    int length = 0;

    optionsFile.open(OPTIONS_FILE);

    if (optionsFile.is_open())
    {
        while (getline(optionsFile, option, '\n'))
        {
            length++;
        }
    }
    else
    {
        cout << "FILE ERROR";
    }
    optionsFile.close();

    return length;
}

int getUserChoice()
{
    int choice = 0;
    cin >> choice;

    return choice;
}

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

/* MENU OPTIONS FUNCTIONALITY */

// option 1
void addCharacter(List *l)
{
    string line[3];
    string name;
    string element;

    cout << "Name of the character: ";
    cin >> line[0];

    cout << "Element of the character(Fire, Water, Earth, Air): ";
    cin >> element;

    validateElement(element);
    addCharacterToList(l, l->getQuantity() + 1, line, element);

    clearScreen();
    cout << line[0] << " was added to the game!" << endl;
}

// option 2
void eraseCharacter(List *l)
{
    string name;
    int index = 0;

    cout << "Name of the character to erase: ";
    cin >> name;

    index = getIndexByCharacterName(l, name);

    if (index != 0)
    {
        l->drop(index);
        clearScreen();
        cout << name << " has been erased from the game." << endl;
    }
    else
        notFoundCharacterNameError();
}

// option 3
void showAllCharactersNames(List *l)
{
    cout << "Characters: ";

    printBlankLine();

    for (int i = 1; i <= l->getQuantity(); i++)
    {
        cout << "Character " << i << ": ";
        cout << l->get(i)->getName() << endl;
    }
    printBlankLine();
}

//option 4
void searchCharacterStats(List *l)
{
    string name;
    int index = 0;
    cout << "Name of character you will like to see stats of: ";
    cin >> name;
    index = getIndexByCharacterName(l, name);
    if (index != 0)
    {
        clearScreen();
        showCharacterStatsByIndex(l, index);
    }
    else
        notFoundCharacterNameError();
}

//option 5
void feedCharacter(List *l)
{
    string name;
    int index = 0;
    cout << "Name of character you will like to feed: ";
    cin >> name;
    index = getIndexByCharacterName(l, name);
    if (index != 0)
    {
        clearScreen();
        feedCharacterByIndex(l, index);
    }
    else
        notFoundCharacterNameError();
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

/* UTILS */
Elements parseStringToElement(string stringToParse)
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
string parseElementToString(Elements elementToParse)
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

void notFoundCharacterNameError()
{
    cout << "A character with that name couldn't be found" << endl;
}

void waitForEnter()
{
    cout << endl
         << endl
         << "Press ENTER to continue..." << endl;
    cin.get();
    cin.get();
}
void clearScreen()
{
    cout << string(25, '\n');
}

void renderGameTitle()
{
    cout << "WELCOME TO BATTLE OF THE ELEMENTS";
}

void printBlankLine()
{
    cout << endl
         << endl;
}

void validateElement(string &element)
{
    // ESTO ES HORRIBLE PERO NO SE ME OCURRE COMO VALIDARLO SIN ESTO.
    while (element != "Air" && element != "Fire" && element != "Water" && element != "Earth" && element != "air" && element != "fire" && element != "water" && element != "earth")
    {
        cout << "Wrong element, please try again. " << endl;
        cout << "The options are (Fire, Water, Air, Earth). ";
        cin >> element;
        cout << element;
    }
}

terrains parseStringToTerrain(std::string colorToParse)
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
bool intersects(GameCell *cell1, GameCell *cell2)
{
	float cell1x = (cell1->getPos()).x;
	float cell1y = (cell1->getPos()).y;
	float cell2x = (cell2->getPos()).x;
	float cell2y = (cell2->getPos()).y;
	return ((abs(cell1x - cell2x) + abs(cell1y - cell2y)) <= 50);
}

void setInitialMatrixes(GameWorld world, int distances[64][64], sf::Vector2f paths[64][64], elements element)
{
	for (int i = 0; i < 64; i++)
	{
		world.tiles[i]->setCost(element);
	}
	int costo;
	for (int i = 0; i < 64; i++)
	{
		costo = world.tiles[i]->getCost();
		for (int j = 0; j < 64; j++)
		{
			if (i != j)
				paths[i][j] = world.tiles[j]->getPos();
			if (i == j)
			{
				distances[i][j] = 0;
				paths[i][j] = sf::Vector2f(-50, -50);
			}
			else if (intersects(world.tiles[j], world.tiles[i]))
				distances[i][j] = costo;
			else
				distances[i][j] = 1000;
		}
	}
}

void printDistances(int distances[64][64])
{
	std::cout << "[" << std::endl;
	for (int i = 0; i < 16; i++)
	{
		std::cout << "[";
		for (int j = 0; j < 16; j++)
		{
			std::cout << distances[i][j] << ",";
		}
		std::cout << "]" << std::endl;
	}
	std::cout << "]" << std::endl;
}

void printPaths(sf::Vector2f paths[64][64])
{
	std::cout << "[" << std::endl;
	for (int i = 0; i < 16; i++)
	{
		std::cout << "[";
		for (int j = 0; j < 16; j++)
		{
			std::cout << "[" << paths[i][j].x / 50 << "," << paths[i][j].y / 50 << "],";
		}
		std::cout << "]" << std::endl;
	}
	std::cout << "]" << std::endl;
}

void shortestPathsFW(GameWorld world, int distances[64][64], sf::Vector2f paths[64][64], elements element)
{
	setInitialMatrixes(world, distances, paths, element);
	for (int k = 0; k < 64; k++)
	{
		GameCell *node = world.tiles[k];
		for (int i = 0; i < 64; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				int aux = distances[i][k] + distances[k][j];
				if (distances[i][j] > aux)
				{
					distances[i][j] = aux;
					paths[i][j] = node->getPos();
				}
			}
		}
	}
}

void loadMovementsStack(Stack *movStack, sf::Vector2f startingPos, sf::Vector2f endingPos, sf::Vector2f paths[64][64])
{
	if (movStack->isEmpty() || movStack->peek() != endingPos)
		movStack->push(endingPos);
	int row = int(startingPos.x + 8 * startingPos.y);
	int col = int(endingPos.x + 8 * endingPos.y);
	sf::Vector2f intPos = paths[row][col];
	intPos.x /= 50;
	intPos.y /= 50;
	if (movStack->peek() == intPos)
		return;
	loadMovementsStack(movStack, intPos, endingPos, paths);
	loadMovementsStack(movStack, startingPos, intPos, paths);
}

sf::Vector2f askDestination()
{
	string x, y;
	std::cout << "Move to x (0-7): ";
	std::cin >> x;
	std::cout << "Move to y (0-7): ";
	std::cin >> y;
	return sf::Vector2f(stof(x), stof(y));
}
