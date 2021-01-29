#include "../src/main.h"

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

void GameCell::setCost(elements element)
{
	switch (terrain)
	{
	case lake:
		switch (element)
		{
		case WATER:
			cost = 0;
			break;
		case FIRE:
			cost = 2;
			break;
		default:
			cost = 1;
			break;
		}
		break;
	case volcano:
		switch (element)
		{
		case FIRE:
			cost = 0;
			break;
		case WATER:
			cost = 2;
			break;
		default:
			cost = 1;
			break;
		}
		break;
	case cliff:
		switch (element)
		{
		case AIR:
			cost = 0;
			break;
		case EARTH:
			cost = 2;
			break;
		default:
			cost = 1;
			break;
		}
		break;
	case mountain:
		switch (element)
		{
		case AIR:
			cost = 2;
			break;
		case EARTH:
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
