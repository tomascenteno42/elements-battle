#include "../../src/main.h"

MountainCell::MountainCell(float xPos, float yPos, float ySize, float xSize)
	:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(mountain), mountain)
{
}

void MountainCell::setCost(elements element)
{
	switch (element)
	{
	case EARTH:
		cost = 0;
		break;
	case FIRE:
		cost = 1;
		break;
	case WATER:
		cost = 1;
		break;
	case AIR:
		cost = 2;
		break;
	}
}
