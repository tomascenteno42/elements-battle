#ifndef FUEGO_H_
#define FUEGO_H_

#include "../../src/main.h"

class FireCharacter : public Character
{
private:
    bool canBeFed();
    void adjustDamageTaken(float &damage, elements attackerElement);

public:
    FireCharacter(string name, float life, int shield);

    elements getElement();

    /*
     * Feeds the character and informs it on the screen
     */
    void feed(GameWindow* window);

    /*
     * If the character has enough energy, it attacks all enemies in range
     */
    void attack(GameWindow* window);

    /*
     * If the character has enough energy, it heals some Life and Energy
     */
    void defend(GameWindow* window);

    /*
     * If the character's energy reaches 0, it takes 5 points of damage
     */
    void update();
};

#endif
