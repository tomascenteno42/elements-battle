/*
 * GameCell.cpp
 *
 *  Created on: Jan 17, 2021
 *      Author: kurepa
 */

#include "GameCell.h"

void GameCell::setCell(float h, float w, sf::Color color){
	cell.setPosition(pos);
	cell.setSize(sf::Vector2f(w, h));
	cell.setFillColor(color);
	cell.setOutlineThickness(1);
	cell.setOutlineColor(sf::Color::Black);
}


GameCell::GameCell(float x, float y, float h, float w, sf::Color color) {

	pos = sf::Vector2f(x, y);
	setCell(h, w, color);
}

GameCell::~GameCell() {
	// TODO Auto-generated destructor stub
}

