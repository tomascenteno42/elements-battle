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
		cell = new GameCell(x, y, HEIGHT, WIDTH, parseTerrainToSf(parseStringToColor(color)));
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
