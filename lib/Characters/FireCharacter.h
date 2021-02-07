#ifndef FUEGO_H_
#define FUEGO_H_

#include "../../src/main.h"

class FireCharacter : public Character
{
private:
    bool canBeFeeded();

public:
    FireCharacter(string n, int v, int es);

    elements getElement();

    void feed(GameWindow* window);
    void attack(GameWindow* window);
    void defend(GameWindow* window);
    void update();
};

#endif
