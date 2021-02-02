#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../../src/main.h"

class Character
{
protected:
    string name;
    elements element;

    int life;
    int shield;
    int energy;
    bool defense;

    sf::Vector2f pos;	// pos = (4,5) seria personaje en columna 4 y fila 5
    sf::RectangleShape cell;

public:
    Character(string n, elements e, int l, int s);

    string getName();
    int getLife();
    int getShield();
    int getEnergy();
    elements getElement();
    sf::Vector2f getPos();
    sf::RectangleShape getCell();
    bool getDefense();

    bool isDead();

    void setName(string n);
    void setLife(int l);
    void setShield(int s);
    void setEnergy(int e);
    void setElement(elements element);
    void setPos(sf::Vector2f pos);
    void setCell();
    void setDefense(bool def);

    virtual void feed() = 0;
    void move(sf::Vector2f pos);
    virtual void attack(Character* character) = 0;

    virtual ~Character();

protected:
    bool canBeFeeded();
};

#endif
