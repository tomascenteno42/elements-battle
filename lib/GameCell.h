/*
 * GameCell.h
 *
 *  Created on: Jan 17, 2021
 *      Author: kurepa
 */

#ifndef GAMECELL_H_
#define GAMECELL_H_

#include "../src/main.h"

class GameCell
{

private:
	terrains terrain;
	int cost = 0;
	bool occupied = false;
	sf::Vector2f pos;

public:
	sf::RectangleShape cell;

	terrains getTerrain();
	int getCost();
	bool isOccupied();
	sf::Vector2f getPos();

	void setCost(elements element);
	void setOccupied(bool occupied);
	void setCell(float h, float w, sf::Color color);

	GameCell(float x, float y, float h, float w, sf::Color color);
	GameCell(float x, float y, float h, float w, terrains terrain, sf::Color color);
	virtual ~GameCell();
};

#endif /* GAMECELL_H_ */
