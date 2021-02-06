#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../../src/main.h"

class GameWindow;

class Character
{
protected:
    string name;
    elements element;

    int life;
    int shield;
    int energy;

    sf::Vector2f pos;	// pos = (4,5) seria personaje en columna 4 y fila 5
    sf::RectangleShape cell;

public:
    Character(string n, elements e, int l, int s);

    bool isDefending = false;

    string getName();
    int getLife();
    int getShield();
    int getEnergy();
    elements getElement();
    sf::Vector2f getPos();
    sf::RectangleShape getCell();

    bool isDead();

    void setName(string n);
    void setLife(int l);
    void setShield(int s);
    void setEnergy(int e);
    void setElement(elements element);
    void setPos(sf::Vector2f pos);
    void setCell();

    virtual void feed() = 0;
    void move(sf::Vector2f pos);

    virtual void attack(GameWindow* window) = 0;
    virtual void defend(GameWindow* window) = 0;

    virtual ~Character();

protected:
    bool canBeFeeded();
};

#endif
