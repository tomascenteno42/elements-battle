#ifndef MOUNTAINCELL_H_
#define MOUNTAINCELL_H_

#include "../../src/main.h"

class MountainCell : public GameCell {
public:
	MountainCell(float xPos, float yPos, float ySize, float xSize);

	void setCost(elements element);
};

#endif
