#ifndef AIRCHARACTER_H_
#define AIRCHARACTER_H_

#include "../../src/main.h"

class AirCharacter : public Character
{
private:
    bool canBeFed();

public:
    AirCharacter(string name, float life, int shield);

    elements getElement();

    void feed(GameWindow* window);
    void attack(GameWindow* window);
    void defend(GameWindow* window);
    void adjustDamageTaken(float &damage, elements attackerElement);
    void update();
};

#endif
