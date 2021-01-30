#ifndef VOLCANOCELL_H_
#define VOLCANOCELL_H_

#include "../src/main.h"

class VolcanoCell : public GameCell {
public:
	VolcanoCell(float xPos, float yPos, float ySize, float xSize)
		:GameCell(xPos, yPos, ySize, xSize, parseTerrainToSf(volcano), volcano)
		{};

	void setCost(elements element);
};

#endif
