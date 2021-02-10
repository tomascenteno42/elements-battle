#ifndef PATHCELL_H_
#define PATHCELL_H_

#include "../../src/main.h"

class PathCell : public GameCell {
public:
	PathCell(float xPos, float yPos, float ySize, float xSize);

	void setCost(elements element);
};

#endif
