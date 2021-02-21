#ifndef AGUA_H_
#define AGUA_H_

#include "../../src/main.h"

class WaterCharacter : public Character
{
private:
    bool canBeFed();
    void adjustDamageTaken(float &damage, elements attackerElement);

public:    
    WaterCharacter(string name, float life, int shield);

    elements getElement();

    /*
     * If the character was fed less than 3 times, it feeds them and informs it on the screen
     */
    void feed(GameWindow* window);

    /*
     * If the character has enough energy, it requests a position from the user
     * and attacks at that position
     */
    void attack(GameWindow* window);

    /*
     * If the character has enough energy, they heal themselves and all the alive allies
     * by a certain amount
     */
    void defend(GameWindow* window);

    /*
     * -
     */
    void update();

    void reset();
};

#endif
