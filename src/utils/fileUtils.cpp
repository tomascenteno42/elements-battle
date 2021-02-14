#include "../main.h"

void openFile(string path, fstream& file)
{
	file.open(path, ios::in);		// ios::in => si el file no existe, no crea nada y no abre nada

	if (!file.is_open()) {
		cout << "No se encontró un archivo con nombre " << path << ".\n"
			 << "Se creará automáticamente ahora un archivo en blanco de nombre "
			 << path << "." << endl;
		file.open(path, ios::out);	// ios::out => si el file no existe, lo crea y lo abre
		file.close();
		file.open(path, ios::in);
	}
}


void loadMapData(GameWorld* world)
{
    fstream file;
    openFile(MAPSTATS_FILE, file);

	GameCell *cell;
	string color;

	int cellCounter = 0;
	int x = 0, y = 0;

	while (getline(file, color, ','))
	{
		terrains terrain = parseStringToTerrain(color);
		switch (terrain)
		{
		case lake:
			cell = new LakeCell(x, y , 50, 50);
			break;
		case volcano:
			cell = new VolcanoCell(x, y , 50, 50);
			break;
		case mountain:
			cell = new MountainCell(x, y , 50, 50);
			break;
		case cliff:
			cell = new CliffCell(x, y , 50, 50);
			break;
		case path:
			cell = new PathCell(x, y , 50, 50);
			break;
		case empty:
			cell = new EmptyCell(x, y , 50, 50);
			break;
		default:
			break;
		}

		if (terrain == empty)
			world->tiles->fillNode(cell, 15, cellCounter+1);
		else
			world->tiles->fillNode(cell, 1, cellCounter+1);
		

		cellCounter++;

		if (cellCounter % 8)
			x += 50;
		else
        {
			x = 0;
			y += 50;
        }
	}

	file.close();
}

void loadCharacterData(BST<string, Character*>* characterMap)
{ 
	fstream file;
	openFile(CHARACTERS_FILE, file);

	string elementStr, name, shieldStr, maxLifeStr;
	Character* character = 0;
	while (getline(file, elementStr, ',')) {
		getline(file, name, ',');
		getline(file, shieldStr, ',');
		getline(file, maxLifeStr);
		character = createNewCharacterFromStrings(elementStr, name, maxLifeStr, shieldStr);
		characterMap->insert(name, character);
	}

	file.close();
}

void loadGameData(fstream& file, GameWorld* world)
{
    string playerStr, elementStr, name, shieldStr, lifeStr, maxLifeStr, energyStr, rowStr, colStr;

	getline(file, playerStr);

    int player = stoi(playerStr);
    world -> currentPlayer = player - 1;

    Character* character = 0;
    int counter = 0;
	while (getline(file, elementStr, ','))
	{
        if (counter == 3) // cambiar jugador
            player = (player % 2) + 1;

        getline(file, name, ',');
		getline(file, shieldStr, ',');
		getline(file, lifeStr, ',');
        getline(file, maxLifeStr, ',');
        getline(file, energyStr, ',');
        getline(file, rowStr, ',');
        getline(file, colStr);

        character = createNewCharacterFromStrings(elementStr, name, maxLifeStr, shieldStr);
        character->setLife(stof(lifeStr));
        character->setEnergy(stoi(energyStr));
        character->setPos(sf::Vector2f(stof(colStr), stof(rowStr)));

        world->addCharacter(character, player);

        counter ++;
	}


	Character* currentCharacter = world->players[world->currentPlayer]->characters[0];
	int i = 0;
	while (currentCharacter->isDead())
	{
		i ++;
		currentCharacter = world->players[world->currentPlayer]->characters[i];
	}
	world->currentCharacter = currentCharacter;
	world->charactersPlayed = i;
	world->updateOccupiedStates();
}

void saveGameData(GameWorld* world)
{
    ofstream file(SAVE_FILE);
	int player = world->currentPlayer;

	file << player + 1 << "\n";

	Character* character = 0;
	for (int p = 0; p < 2; p ++)
	{
		player = (player + p) % 2;
		for (int i = 0; i < world->players[player]->characters.size(); i ++)
		{
			character = world->players[player]->characters[i];
			file << parseElementToString(character->getElement()) << ",";
			file << character->getName() << ",";
			file << character->getShield() << ",";
			file << character->getLife() << ",";
			file << character->getMaxLife() << ",";
			file << character->getEnergy() << ",";
			file << character->getPos().y << ",";
			file << character->getPos().x << "\n";
		}
	}
}

Character* createNewCharacterFromStrings(std::string elementStr, std::string name, std::string maxLifeStr, std::string shieldStr)
{
    Character* character = 0;
    elements element = parseStringToElement(elementStr);
    switch (element)
    {
        case AIR:
            character = new AirCharacter(name, stof(maxLifeStr), stoi(shieldStr));
            break;
        case EARTH:
            character = new EarthCharacter(name, stof(maxLifeStr), stoi(shieldStr));
            break;
        case FIRE:
            character = new FireCharacter(name, stof(maxLifeStr), stoi(shieldStr));
            break;
        case WATER:
            character = new WaterCharacter(name, stof(maxLifeStr), stoi(shieldStr));
            break;
        default:
            break;                                                                
    }
    return character;
}