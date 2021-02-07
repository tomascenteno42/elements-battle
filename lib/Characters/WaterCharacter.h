#ifndef AGUA_H_
#define AGUA_H_

#include "../../src/main.h"

class WaterCharacter : public Character
{
private:
    int timesFeeded = 0;
    bool canBeFeeded();

public:
    WaterCharacter(string n, int v, int es);

    elements getElement();

    void feed(GameWindow* window);
    void attack(GameWindow* window);
    void defend(GameWindow* window);
    void update();
};

#endif
