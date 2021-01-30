#ifndef GAMECELL_H_
#define GAMECELL_H_

#include "../src/main.h"

class GameCell : public Cell
{
protected:
	terrains terrain;
	int cost = 0;
	bool occupied = false;

public:
	GameCell(float xPos, float yPos, float ySize, float xSize, sf::Color color, terrains terrain) : Cell(xPos, yPos, ySize, xSize, color)
	{
		setTerrain(terrain);
	};

	terrains getTerrain();

	int getCost();
	bool isOccupied();

	virtual void setCost(elements element) = 0;
	void setOccupied(bool occupied);
	void setTerrain(terrains t);

	virtual ~GameCell();
};

#endif /* GAMECELL_H_ */
