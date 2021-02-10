#include "../../src/main.h"

VolcanoCell::VolcanoCell(float xPos, float yPos, float ySize, float xSize)
	:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(volcano), volcano)
{
}

void VolcanoCell::setCost(elements element)
{
	switch (element)
	{
	case EARTH:
		cost = 1;
		break;
	case FIRE:
		cost = 0;
		break;
	case WATER:
		cost = 2;
		break;
	case AIR:
		cost = 1;
		break;
	}
}
