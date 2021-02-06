#ifndef TIERRA_H_
#define TIERRA_H_

#include "../../src/main.h"

class EarthCharacter : public Character
{
private:
    bool canBeFeeded();

public:
    EarthCharacter(string n, elements e, int v, int es)
        : Character(n, e, v, es){};

    void attack(GameWindow* window);
    void defend(GameWindow* window);

    void feed();
};

#endif
