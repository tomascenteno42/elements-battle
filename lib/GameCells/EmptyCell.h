#ifndef EMPTYCELL_H_
#define EMPTYCELL_H_

#include "../../src/main.h"

class EmptyCell : public GameCell {
public:
	EmptyCell(float xPos, float yPos, float ySize, float xSize);

	void setCost(elements element);
};

#endif
