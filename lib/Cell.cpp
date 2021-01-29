#include "../src/main.h"

Cell::Cell(float x, float y, float h, float w, sf::Color color)
{
    setPos(x, y);
    setCell(h, w, color);
}

void Cell::setPos(float x, float y)
{
    pos = sf::Vector2f(x, y);
}

void Cell::setCell(float h, float w, sf::Color color)
{
    cell.setPosition(pos);
    cell.setSize(sf::Vector2f(w, h));
    cell.setFillColor(color);
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::Black);
}

sf::Vector2f Cell::getPos()
{
    return pos;
}

sf::RectangleShape Cell::getCell()
{
    return cell;
}