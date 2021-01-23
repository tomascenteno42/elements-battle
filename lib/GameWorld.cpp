/*
 * GameWorld.cpp
 *
 *  Created on: Jan 17, 2021
 *      Author: kurepa
 */

#include "../src/main.h"

const int HEIGHT = 50, WIDTH = 50;

GameWorld::GameWorld() {
}

void GameWorld::setMap() {
	cout << "Entro a setMap" << endl;

	fstream file;
	file.open(MAPSTATS_FILE);

	int cellCounter = 0;
	int x = 0, y = 0;
	string color;

	while (!file.eof()) {
		cellCounter++;

		getline(file, color, ',');

		GameCell *cell = new GameCell(x, y, HEIGHT, WIDTH, parseColorToSf(parseStringToColor(color)));
		tiles.push_back(cell); 

		cout << cellCounter << endl;

		if (cellCounter % gridLength == 0){
			x = 0;
			y += 50;
		} else x += 50;
	}
	
	cout << "salio del while" << endl;
	file.close();
}

GameWorld::~GameWorld() {
}
