/*
 * GameWorld.h
 *
 *  Created on: Jan 17, 2021
 *      Author: kurepa
 */

#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include "../src/main.h"

class GameWorld
{
public:
	int gridLength = 8;
	vector<GameCell *> tiles;

	int distances [4][64][64];
	sf::Vector2f paths [4][64][64];
	vector<Character*> player1Characters;
	vector<Character*> player2Characters;

	void addCharacter(Character* character, int player);
	void setMap();
	void setFWMatrixes();

	GameWorld();
	virtual ~GameWorld();

private:
	bool emptyWorld();
};

#endif /* GAMEWORLD_H_ */
