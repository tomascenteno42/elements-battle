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

    bool isDead();

    void setName(string n);
    void setLife(float l);
    void setShield(int s);
    void setEnergy(int e);
    void setPos(sf::Vector2f pos);
    void setCell();

    void move(GameWindow* window, sf::Vector2f destination, int energyRequired);

    void shieldDamage(float &damage);

    virtual void feed(GameWindow* window) = 0;
    virtual void attack(GameWindow* window) = 0;
    virtual void adjustDamageTaken(float &damage, elements attackerElement) = 0;
    virtual void defend(GameWindow* window) = 0;
    virtual void update() = 0;

    virtual ~Character();

protected:
    bool canBeFed();
};

#endif
