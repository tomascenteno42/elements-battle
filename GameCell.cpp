/*
 * GameCell.cpp
 *
 *  Created on: Jan 17, 2021
 *      Author: kurepa
 */

#include "src/main.h"

terrains GameCell::getTerrain() {
	return terrain;
}

int GameCell::getCost() {
	return cost;
}

bool GameCell::isOccupied() {
	return occupied;
}

sf::Vector2f GameCell::getPos() {
	return pos;
}

void GameCell::setCost(elements element) {
	switch (terrain) {
	case lake:
		switch (element) {
		case water:
			cost = 0;
			break;
		case fire:
			cost = 2;
			break;
		default:
			cost = 1;
			break;
		}
		break;
	case volcano:
		switch (element) {
		case fire:
			cost = 0;
			break;
		case water:
			cost = 2;
			break;
		default:
			cost = 1;
			break;
		}
		break;
	case cliff:
		switch (element) {
		case air:
			cost = 0;
			break;
		case earth:
			cost = 2;
			break;
		default:
			cost = 1;
			break;
		}
		break;
	case mountain:
		switch (element) {
		case air:
			cost = 2;
			break;
		case earth:
			cost = 1;
			break;
		default:
			cost = 1;
			break;
		}
		break;
	case path:
		cost = 1;
		break;
	case empty:
		cost = 15;
		break;
	default:
		cost = 100;
		break;
	}
}


void GameCell::setOccupied(bool occupied) {
	this -> occupied = occupied;
}

void GameCell::setCell(float h, float w, sf::Color color){
	cell.setPosition(pos);
	cell.setSize(sf::Vector2f(w, h));
	cell.setFillColor(color);
	cell.setOutlineThickness(1);
	cell.setOutlineColor(sf::Color::Black);
}

GameCell::GameCell(float x, float y, float h, float w, sf::Color color) {
	pos = sf::Vector2f(x, y);
	this -> terrain = none;
	setCell(h, w, color);
}

GameCell::GameCell(float x, float y, float h, float w, terrains terrain, sf::Color color) {
	pos = sf::Vector2f(x, y);
	this -> terrain = terrain;
	setCell(h, w, color);
}

GameCell::~GameCell() {
	// TODO Auto-generated destructor stub
}

