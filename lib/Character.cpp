#include "../src/main.h"

Character::Character(std::string n, Elements e, int l, int s)
{
    energy = rand() % 20;
    name = n;
    element = e;
    life = l;
    shield = s;
}

/* GETTERS */

std::string Character::getName()
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

Elements Character::getElement()
{
    return element;
}

/* SETTERS */

void Character::setName(std::string n)
{
    name = n;
}

void Character::setElement(Elements e)
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

Character::~Character() = default;