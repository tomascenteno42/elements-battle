#ifndef AIRCHARACTER_H_
#define AIRCHARACTER_H_

#include "../../src/main.h"

class AirCharacter : public Character
{
private:
    bool canBeFed();
    void adjustDamageTaken(float &damage, elements attackerElement);

public:
    AirCharacter(string name, float life, int shield);

    elements getElement();

    /*
     * Informs that air characters can't be fed
     */
    void feed(GameWindow* window);

    /*
     * If the character has enough energy, it attacks all enemies
     */
    void attack(GameWindow* window);

    /*
     * If the character has enough energy, it asks the user for a valid move
     * position and moves the character there with no energy cost
     */
    void defend(GameWindow* window);

    /*
     * Recovers 5 energy
     */
    void update();

    void reset();
};

#endif
