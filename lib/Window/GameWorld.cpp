#include "../../src/main.h"

const int HEIGHT = 50, WIDTH = 50;

GameWorld::GameWorld()
{
	setMap();
	movStack = new Stack<sf::Vector2f>();
}

void GameWorld::setMap()
{
	GameCell *cell;
	ifstream file;
	string color;

	int cellCounter = 0;
	int x = 0, y = 0;

	file.open(MAPSTATS_FILE);
	validateFile<ifstream &>(file, MAPSTATS_FILE);

	while (getline(file, color, ','))
	{
		cellCounter++;
		terrains terrain = parseStringToTerrain(color);
		switch (terrain)
		{
		case lake:
			cell = new LakeCell(x, y , HEIGHT, WIDTH);
			break;
		case volcano:
			cell = new VolcanoCell(x, y , HEIGHT, WIDTH);
			break;
		case mountain:
			cell = new MountainCell(x, y , HEIGHT, WIDTH);
			break;
		case cliff:
			cell = new CliffCell(x, y , HEIGHT, WIDTH);
			break;
		case path:
			cell = new PathCell(x, y , HEIGHT, WIDTH);
			break;
		case empty:
			cell = new EmptyCell(x, y , HEIGHT, WIDTH);
			break;
		default:
			break;
		}
		tiles.push_back(cell);

		if (cellCounter % gridLength == 0)
		{
			x = 0;
			y += 50;
		}
		else
			x += 50;
	}

	file.close();
	setFWMatrixes();
}

void GameWorld::addCharacter(Character *character, int player)
{
	if (player == 1)
		player1Characters.push_back(character);
	if (player == 2)
		player2Characters.push_back(character);
	tiles[character->getPos().x + 8 * character->getPos().y]->setOccupied(true);
}

void GameWorld::setFWMatrixes()
{
	for (int i = 0; i < 4; i++)
	{
		elements element = static_cast<elements>(i + 1);
		int distances_aux[64][64];
		sf::Vector2f paths_aux[64][64];
		shortestPathsFW(this, distances_aux, paths_aux, element);
		for (int j = 0; j < 64; j++)
		{
			for (int k = 0; k < 64; k++)
			{
				distances[i][j][k] = distances_aux[j][k];
				paths[i][j][k] = paths_aux[j][k];
			}
		}
	}
}

bool GameWorld::emptyWorld()
{
	return tiles.empty();
}

void GameWorld::advanceState()
{
    charactersPlayed ++; 

    if (charactersPlayed == 3)
    {
        charactersPlayed = 0;
        currentPlayer = currentPlayer % 2 + 1;
		if (currentPlayer == 1)
			updateCharacters();
    }

    if (currentPlayer == 1)
        currentCharacter = player1Characters[charactersPlayed];
    else
        currentCharacter = player2Characters[charactersPlayed];
}

void GameWorld::updateCharacters()
{
	Character* character = 0;
	for (int i = 0; i < player1Characters.size(); i ++)
	{
		character = player1Characters[i];
		if (character->getElement() == AIR)
			character->setEnergy(min(20, 5 + character->getEnergy()));
		if (character->getElement() == EARTH && character->isDefending)
			character->setShield(character->getShield() - 2);
	}

	for (int i = 0; i < player2Characters.size(); i ++)
	{
		character = player2Characters[i];
		if (character->getElement() == AIR)
			character->setEnergy(min(20, 5 + character->getEnergy()));
		if (character->getElement() == EARTH && character->isDefending)
			character->setShield(character->getShield() - 2);
	}
}

GameWorld::~GameWorld()
{
	while (!emptyWorld())
	{
		delete tiles.back();
		tiles.pop_back();
	}

	for (int i = 0; i < 3; i ++)

	{
		delete player1Characters[i];
		delete player2Characters[i];
	}

	delete movStack;
}
