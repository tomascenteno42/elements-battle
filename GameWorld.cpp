/*
 * GameWorld.cpp
 *
 *  Created on: Jan 17, 2021
 *      Author: kurepa
 */

#include "src/main.h"

GameWorld::GameWorld() {
}



void GameWorld::setMap() {
	vector<GameCell*> row;

	fstream file;
	file.open("mapStats.csv");
	string line;

	int x, y, h, w;
	string color;
	while (!file.eof()) {
		getline(file, line);
		stringstream mapStats(line);
		string dato;
		for (int col = 0; getline(mapStats, dato, ','); col++) {
			switch (col) {
			case 0:
				x = stoi(dato);
				break;
			case 1:
				y = stoi(dato);
				break;
			case 2:
				h = stoi(dato);
				break;
			case 3:
				w = stoi(dato);
				break;
			case 4:
				color = dato;
				break;
			}
		}
		GameCell *cell = new GameCell(x, y, h, w, parseColorToSf(parseStringToColor(color)));
		tiles.push_back(cell);
	}
	file.close();
}
GameWorld::~GameWorld() {
}
