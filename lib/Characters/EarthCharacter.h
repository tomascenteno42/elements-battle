#ifndef TIERRA_H_
#define TIERRA_H_

#include "../../src/main.h"

class EarthCharacter : public Character
{
private:
    bool canBeFed();
    void adjustDamageTaken(float &damage, elements attackerElement);

public:
    EarthCharacter(string name, float life, int shield);

    elements getElement();

    /*
     * Feeds the character and informs it on the screen
     */
    void feed(GameWindow* window);

    /*
     * If the character has enough energy, it attacks all enemies
     */
    void attack(GameWindow* window);

    /*
     * If the character has enough energy, its shield is increased by 2
     * Turns isDefending boolean to true
     */
    void defend(GameWindow* window);

    /*
     * Removes the extra shield points if the character was defending
     * and turns isDefending boolean to false
     */
    void update();
};

#endif
