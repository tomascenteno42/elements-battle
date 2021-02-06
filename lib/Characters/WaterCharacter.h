#ifndef AGUA_H_
#define AGUA_H_

#include "../../src/main.h"

class WaterCharacter : public Character
{

private:
    int timesFeeded = 0;

public:
    WaterCharacter(string n, elements e, int v, int es) : Character(n, e, v, es){};

    void attack(vector<Character*> enemies, sf::Vector2f pos);

    void feed();

private:
    bool canBeFeeded();
};

#endif
