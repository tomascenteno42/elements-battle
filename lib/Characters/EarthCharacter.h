#ifndef TIERRA_H_
#define TIERRA_H_

#include "../../src/main.h"

class EarthCharacter : public Character
{
private:
    bool canBeFeeded();

public:
    EarthCharacter(string n, int v, int es);

    elements getElement();

    void feed(GameWindow* window);
    void attack(GameWindow* window);
    void defend(GameWindow* window);
    void update();
};

#endif
