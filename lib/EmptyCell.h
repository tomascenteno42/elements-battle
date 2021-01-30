#ifndef EMPTYCELL_H_
#define EMPTYCELL_H_

#include "../src/main.h"

class EmptyCell : public GameCell {
public:
	EmptyCell(float xPos, float yPos, float ySize, float xSize)
		:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(empty), empty)
		{};

	void setCost(elements element);
};

#endif
