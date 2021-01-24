#ifndef AIRCHARACTER_H_
#define AIRCHARACTER_H_

#include "../src/main.h"

class AirCharacter : public Character
{
private:
    bool canBeFeeded();

public:
    AirCharacter(string n, elements e, int v, int es) : Character(n, e, v, es){};

    void feed();
};

#endif