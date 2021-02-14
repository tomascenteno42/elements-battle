#include "../../src/main.h"

MountainCell::MountainCell(float xPos, float yPos, float ySize, float xSize)
	:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(mountain), mountain)
{
}

void MountainCell::adjustCost(int &cost, elements element)
{
	switch (element)
	{
	case EARTH:
		cost --;
		break;
	case AIR:
		cost ++;
		break;
	default:
		break;
	}
}
