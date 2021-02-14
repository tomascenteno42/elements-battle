#include "../../src/main.h"

CliffCell::CliffCell(float xPos, float yPos, float ySize, float xSize)
	:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(cliff), cliff)
{
}

void CliffCell::adjustCost(int &cost, elements element)
{
	switch (element)
	{
	case EARTH:
		cost ++;
		break;
	case AIR:
		cost --;
		break;
	default:
		break;
	}
}
