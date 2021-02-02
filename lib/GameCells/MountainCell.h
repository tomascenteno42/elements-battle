#ifndef MOUNTAINCELL_H_
#define MOUNTAINCELL_H_

#include "../../src/main.h"

class MountainCell : public GameCell {
public:
	MountainCell(float xPos, float yPos, float ySize, float xSize)
		:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(mountain), mountain)
		{};

	void setCost(elements element);
};

#endif
