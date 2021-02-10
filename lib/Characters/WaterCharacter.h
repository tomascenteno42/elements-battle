#ifndef AGUA_H_
#define AGUA_H_

#include "../../src/main.h"

class WaterCharacter : public Character
{
private:
    int timesFed = 0;
    bool canBeFed();

public:
    WaterCharacter(string name, float life, int shield);

    elements getElement();

    void feed(GameWindow* window);
    void attack(GameWindow* window);
    void defend(GameWindow* window);
    void adjustDamageTaken(float &damage, elements attackerElement);
    void update();
};

#endif
