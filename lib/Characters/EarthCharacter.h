#ifndef TIERRA_H_
#define TIERRA_H_

#include "../../src/main.h"

class EarthCharacter : public Character
{
private:
    bool canBeFed();

public:
    EarthCharacter(string name, float life, int shield);

    elements getElement();

    void feed(GameWindow* window);
    void attack(GameWindow* window);
    void defend(GameWindow* window);
    void adjustDamageTaken(float &damage, elements attackerElement);
    void update();
};

#endif
