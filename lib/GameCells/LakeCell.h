#ifndef LAKECELL_H_
#define LAKECELL_H_

#include "../../src/main.h"

class LakeCell : public GameCell {
public:
	LakeCell(float xPos, float yPos, float ySize, float xSize);

	void adjustCost(int &cost, elements element);
};

#endif
