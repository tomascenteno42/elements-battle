#include "../../src/main.h"

LakeCell::LakeCell(float xPos, float yPos, float ySize, float xSize)
	:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(lake), lake)
{
}

void LakeCell::adjustCost(int &cost ,elements element)
{
	switch (element)
	{
	case FIRE:
		cost ++;
		break;
	case WATER:
		cost --;
		break;
	default:
		break;
	}
}
