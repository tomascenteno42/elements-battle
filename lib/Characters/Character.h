#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../../src/main.h"

class GameWindow;

class Character
{
protected:
    string name;

    float life;
    int maxLife;
    int shield;
    int energy;

    sf::Vector2f pos;
    sf::RectangleShape cell;

public:
    Character(string n, float l, int s);

    bool isDefending = false;

    string getName();
    float getLife();
    int getMaxLife();
    int getShield();
    int getEnergy();
    virtual elements getElement() = 0;
    sf::Vector2f getPos();
    sf::RectangleShape getCell();

    void setName(string n);
    void setLife(float l);
    void setShield(int s);
    void setEnergy(int e);
    void setPos(sf::Vector2f pos);
    void setCell();

    /*
     * Returns true if character's life is 0
     */
    bool isDead();

    /*
     * Recieves a destination that has been validated, and the energy required to
     * move to that destination, both have been asked/calculated beforehand
     * Moves the character to the destination cell step by step, drawing on the
     * screen on every step
     */
    void move(GameWindow* window, sf::Vector2f destination, int energyRequired);

    virtual void feed(GameWindow* window) = 0;
    virtual void attack(GameWindow* window) = 0;
    virtual void defend(GameWindow* window) = 0;
    virtual void update() = 0;

    /*
     * Modifies a damage value based on the attacker character and the
     * attacked character's elements
     */
    virtual void adjustDamageTaken(float &damage, elements attackerElement) = 0;

    /*
     * Resets character's state so it is clean once a new game starts
     */
    virtual void reset() = 0;

    virtual ~Character();

protected:
    /*
     * Checks whether the character can be fed
     */
    bool canBeFed();

    /*
     * Modifies a damage value according to the character's shield value
     */
    void shieldDamage(float &damage);
};

#endif
