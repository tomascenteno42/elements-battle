#ifndef FUEGO_H_
#define FUEGO_H_

#include "../../src/main.h"

class FireCharacter : public Character
{
private:
    bool canBeFed();

public:
    FireCharacter(string name, float life, int shield);

    elements getElement();

    void feed(GameWindow* window);
    void attack(GameWindow* window);
    void defend(GameWindow* window);
    void adjustDamageTaken(float &damage, elements attackerElement);
    void update();
};

#endif
