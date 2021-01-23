/*
 * GameCell.h
 *
 *  Created on: Jan 17, 2021
 *      Author: kurepa
 */

#ifndef GAMECELL_H_
#define GAMECELL_H_

#include "../src/main.h"
class GameCell {
public:
	// para mostrar personaje y para el ataque de personaje agua.
	bool occupied;
	sf::Vector2f pos;
	sf::RectangleShape cell;

	void setCell(float h, float w, sf::Color color);

	GameCell(float x, float y, float h, float w, sf::Color color);
	virtual ~GameCell();
};

#endif /* GAMECELL_H_ */
