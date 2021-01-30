#ifndef FUEGO_H_
#define FUEGO_H_

#include "../src/main.h"

class FireCharacter : public Character
{
private:
    bool canBeFeeded();

public:
    FireCharacter(string n, elements e, int v, int es)
        : Character(n, e, v, es){};

    void attack(Character* enemy);
    void feed();
};
#endif
