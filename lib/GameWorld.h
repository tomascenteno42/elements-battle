/*
 * GameWorld.h
 *
 *  Created on: Jan 17, 2021
 *      Author: kurepa
 */

#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include "../src/main.h"

class GameWorld {
public:
	int gridLength = 8;
	std::vector<GameCell*> tiles;

	void setMap();

	GameWorld();
	virtual ~GameWorld();
};

#endif /* GAMEWORLD_H_ */

