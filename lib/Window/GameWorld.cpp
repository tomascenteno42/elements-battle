#include "../../src/main.h"

const int HEIGHT = 50, WIDTH = 50;

GameWorld::GameWorld()
{
	Player* player1 = new Player();
	Player* player2 = new Player();
	players[0] = player1;
	players[1] = player2;

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
	players[player - 1] -> addCharacter(character);
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

    if (charactersPlayed == players[currentPlayer]->charactersAlive)	// Ya jugaron todos los personajes en el turno
    {
        charactersPlayed = 0;
        currentPlayer = (currentPlayer + 1) % 2;
		players[currentPlayer]->updateCharacters();
    }

    currentCharacter = players[currentPlayer]->characters[charactersPlayed];
}



GameWorld::~GameWorld()
{
	delete players[0];
	delete players[1];

	while (!emptyWorld())
	{
		delete tiles.back();
		tiles.pop_back();
	}

	delete movStack;
}
