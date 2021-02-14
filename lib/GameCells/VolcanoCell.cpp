#include "../../src/main.h"

VolcanoCell::VolcanoCell(float xPos, float yPos, float ySize, float xSize)
	:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(volcano), volcano)
{
}

void VolcanoCell::adjustCost(int &cost, elements element)
{
	switch (element)
	{
	case FIRE:
		cost --;
		break;
	case WATER:
		cost ++;
		break;
	default:
		break;
	}
}
