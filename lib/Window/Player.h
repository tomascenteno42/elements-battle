#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../src/main.h"

class Player
{
public:
    vector<Character*> characters;

    Player();
    int charactersAlive();
    void updateCharacters();
    void addCharacter(Character* character);
    bool lost();

    ~Player();
};

#endif