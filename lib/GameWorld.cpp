#include "../src/main.h"

const int HEIGHT = 50, WIDTH = 50;

GameWorld::GameWorld()
{
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
		cell = new GameCell(x, y, HEIGHT, WIDTH, parseTerrainToSf(parseStringToTerrain(color)), terrain);
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

GameWorld::~GameWorld()
{
	while (!emptyWorld())
	{
		delete tiles.back();
		tiles.pop_back();
	}
}
