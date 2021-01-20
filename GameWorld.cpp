/*
 * GameWorld.cpp
 *
 *  Created on: Jan 17, 2021
 *      Author: kurepa
 */

#include "src/main.h"

const int HEIGHT = 50, WIDTH = 50;

GameWorld::GameWorld() {
}

void GameWorld::setMap() {
	vector<GameCell*> row;

	fstream file;
	file.open("mapStats.csv");

	int cellCounter = 0;
	int x = 0, y = 0;
	string color;

	while (!file.eof()) {
		cellCounter++;

		getline(file, color, ',');

		terrains terrain = parseStringToTerrain(color);
		GameCell *cell = new GameCell(x, y, HEIGHT, WIDTH, terrain, parseTerrainToSf(terrain));
		tiles.push_back(cell);

		if (cellCounter % 8 == 0){
			x = 0;
			y += 50;
		} else x += 50;
	}
	
	file.close();
}

GameWorld::~GameWorld() {
}
