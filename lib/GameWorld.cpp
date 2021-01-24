/*
 * GameWorld.cpp
 *
 *  Created on: Jan 17, 2021
 *      Author: kurepa
 */

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
	if (!file)
	{
		cerr << "Unable to open file mapStats.csv";
		exit(1);
	}

	while (getline(file, color, ','))
	{
		cellCounter++;

		cell = new GameCell(x, y, HEIGHT, WIDTH, parseColorToSf(parseStringToColor(color)));
		tiles.push_back(cell);
		cout << cellCounter << endl;

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
