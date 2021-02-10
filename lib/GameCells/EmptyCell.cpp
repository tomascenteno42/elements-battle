#include "../../src/main.h"

EmptyCell::EmptyCell(float xPos, float yPos, float ySize, float xSize)
	:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(empty), empty)
{
}

void EmptyCell::setCost(elements element)
{
	cost = 15;
}
