#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../src/main.h"

class Character
{
protected:
    string name;
    Elements element;

    int life;
    int shield;
    int energy;

public:
    Character(string n, Elements e, int l, int s);

    string getName();
    int getLife();
    int getShield();
    int getEnergy();
    Elements getElement();

    void setName(string n);
    void setLife(int l);
    void setShield(int s);
    void setEnergy(int e);
    void setElement(Elements element);

    virtual void feed() = 0;

    virtual ~Character();

protected:
    bool canBeFeeded();
};

#endif