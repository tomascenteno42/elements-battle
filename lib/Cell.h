#ifndef CELL_H_
#define CELL_H_

#include "../src/main.h"

class Cell
{
private:
    sf::Vector2f pos;
    sf::RectangleShape cell;

public:
    Cell(float x, float y, float h, float w, sf::Color color);

    void setPos(float x, float y);
    void setCell(float h, float w, sf::Color);

    sf::RectangleShape getCell();
    sf::Vector2f getPos();
};

#endif
