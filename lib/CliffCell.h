#ifndef CLIFFCELL_H_
#define CLIFFCELL_H_

#include "../src/main.h"

class CliffCell : public GameCell {
public:
	CliffCell(float xPos, float yPos, float ySize, float xSize)
		:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(cliff), cliff)
		{};

	void setCost(elements element);
};

#endif
