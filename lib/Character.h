#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../src/main.h"

class Character
{
protected:
    string name;
    elements element;

    int life;
    int shield;
    int energy;

public:
    Character(string n, elements e, int l, int s);

    string getName();
    int getLife();
    int getShield();
    int getEnergy();
    elements getElement();

    void setName(string n);
    void setLife(int l);
    void setShield(int s);
    void setEnergy(int e);
    void setElement(elements element);

    virtual void feed() = 0;

    virtual ~Character();

protected:
    bool canBeFeeded();
};

#endif