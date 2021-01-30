#ifndef LAKECELL_H_
#define LAKECELL_H_

#include "../src/main.h"

class LakeCell : public GameCell {
public:
	LakeCell(float xPos, float yPos, float ySize, float xSize)
		:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(lake), lake)
		{};

	void setCost(elements element);
};

#endif
