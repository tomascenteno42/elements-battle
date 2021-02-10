#ifndef LAKECELL_H_
#define LAKECELL_H_

#include "../../src/main.h"

class LakeCell : public GameCell {
public:
	LakeCell(float xPos, float yPos, float ySize, float xSize);

	void setCost(elements element);
};

#endif
