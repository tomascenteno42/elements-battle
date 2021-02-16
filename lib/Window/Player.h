#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../src/main.h"

class Player
{
public:
    vector<Character*> characters;

    Player();

    /*
     * Returns amount of alive characters the player has
     */
    int charactersAlive();

    /*
     * Calls update method for every alive character the player has
     */
    void updateCharacters();

    /*
     * Adds character to player's characters
     */
    void addCharacter(Character* character);

    /*
     * Returns true if all characters are dead
     */
    bool lost();

    ~Player();
};

#endif