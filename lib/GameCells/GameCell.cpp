#include "../../src/main.h"

GameCell::GameCell(float xPos, float yPos, float ySize, float xSize, sf::Color color, terrains terrain)
	:Cell(xPos, yPos, ySize, xSize, color)
{
	setTerrain(terrain);
}

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
