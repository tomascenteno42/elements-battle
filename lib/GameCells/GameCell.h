#ifndef GAMECELL_H_
#define GAMECELL_H_

#include "../../src/main.h"

class GameCell : public Cell
{
protected:
	terrains terrain;
	bool occupied = false;

public:
	GameCell(float xPos, float yPos, float ySize, float xSize, sf::Color color, terrains terrain);

	terrains getTerrain();
	bool isOccupied();

	void setOccupied(bool occupied);
	void setTerrain(terrains t);

	/*
	 * It modifies a cost value based on the GameCell's terrain and the element passed by parameter
	 */
	virtual void adjustCost(int &cost, elements element) = 0;

	virtual ~GameCell();
};

#endif /* GAMECELL_H_ */
