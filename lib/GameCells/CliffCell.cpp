#include "../../src/main.h"

CliffCell::CliffCell(float xPos, float yPos, float ySize, float xSize)
	:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(cliff), cliff)
{
}

void CliffCell::setCost(elements element)
{
	switch (element)
	{
	case EARTH:
		cost = 2;
		break;
	case FIRE:
		cost = 1;
		break;
	case WATER:
		cost = 1;
		break;
	case AIR:
		cost = 0;
		break;
	}
}
