#ifndef PATHCELL_H_
#define PATHCELL_H_

#include "../../src/main.h"

class PathCell : public GameCell {
public:
	PathCell(float xPos, float yPos, float ySize, float xSize)
		:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(path), path)
		{};

	void setCost(elements element);
};

#endif
