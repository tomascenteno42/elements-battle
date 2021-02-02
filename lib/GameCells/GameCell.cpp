#include "../../src/main.h"

terrains GameCell::getTerrain()
{
	return terrain;
}

int GameCell::getCost()
{
	return cost;
}

bool GameCell::isOccupied()
{
	return occupied;
}

void GameCell::setOccupied(bool occupied)
{
	this->occupied = occupied;
}

void GameCell::setTerrain(terrains t)
{
	terrain = t;
}

GameCell::~GameCell()
{
}
