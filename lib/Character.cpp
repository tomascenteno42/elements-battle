#include "../src/main.h"

Character::Character(string n, elements e, int l, int s)
{
    energy = rand() % 20;
    name = n;
    element = e;
    life = l;
    shield = s;
    pos = sf::Vector2f(-1,-1);
    setCell();
}

/* GETTERS */

string Character::getName()
{
    return name;
}

int Character::getLife()
{
    return life;
}

int Character::getShield()
{
    return shield;
}

int Character::getEnergy()
{
    return energy;
}

elements Character::getElement()
{
    return element;
}

sf::Vector2f Character::getPos() {
	return pos;
}

sf::RectangleShape Character::getCell() {
	return cell;
}

/* SETTERS */

void Character::setName(string n)
{
    name = n;
}

void Character::setElement(elements e)
{
    element = e;
}

void Character::setLife(int l)
{
    life = l;
}

void Character::setShield(int s)
{
    shield = s;
}

void Character::setEnergy(int e)
{
    energy = e;
}

void Character::setPos(sf::Vector2f pos) {
	this -> pos = pos;
	cell.setPosition(pos);
}


void Character::setCell() {
	cell.setPosition(sf::Vector2f(50 * pos.x + 12.5, 50 * pos.y + 12.5));
	cell.setSize(sf::Vector2f(25,25));
	cell.setFillColor(sf::Color::Green); // Make it so it depends on character's element
	cell.setOutlineThickness(1);
	cell.setOutlineColor(sf::Color::Black);
}


Character::~Character() = default;
