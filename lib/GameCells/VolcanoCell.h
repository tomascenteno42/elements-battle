#ifndef VOLCANOCELL_H_
#define VOLCANOCELL_H_

#include "../../src/main.h"

class VolcanoCell : public GameCell {
public:
	VolcanoCell(float xPos, float yPos, float ySize, float xSize);

	void setCost(elements element);
};

#endif
