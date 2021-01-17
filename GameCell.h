/*
 * GameCell.h
 *
 *  Created on: Jan 17, 2021
 *      Author: kurepa
 */

#ifndef GAMECELL_H_
#define GAMECELL_H_

#include <SFML/Graphics.hpp>

class GameCell {
public:
	// para mostrar personaje y para el ataque de personaje agua.
	bool occupied;
	sf::Vector2f pos;
	sf::RectangleShape cell;

	void setCell( float, float, sf::Color);

	GameCell(float, float, float, float, sf::Color);
	virtual ~GameCell();
};

#endif /* GAMECELL_H_ */
