#ifndef AIRCHARACTER_H_
#define AIRCHARACTER_H_

#include "../../src/main.h"

class AirCharacter : public Character
{
private:
    bool canBeFeeded();

public:
    AirCharacter(string n, int v, int es);

    elements getElement();

    void feed(GameWindow* window);
    void attack(GameWindow* window);
    void defend(GameWindow* window);
    void update();
};

#endif
