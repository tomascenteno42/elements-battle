#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../src/main.h"

class Player
{
public:
    vector<Character*> characters;
    int charactersAlive = 0;

    Player();
    void deleteDeadCharacters();
    void updateCharacters();
    void addCharacter(Character* character);

    ~Player();
};

#endif