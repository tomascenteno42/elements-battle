#include "../../src/main.h"

PathCell::PathCell(float xPos, float yPos, float ySize, float xSize)
	:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(path), path)
{
}

void PathCell::adjustCost(int &cost, elements element)
{
}
