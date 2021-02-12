#include "../../src/main.h"

Player::Player()
{
}

void Player::addCharacter(Character* character)
{
    characters.push_back(character);
}

int Player::charactersAlive()
{
    int charactersAlive = 0;
    for (int i = 0; i < characters.size(); i ++)
    {
        if (!characters[i]->isDead())
            charactersAlive ++;
    }
    return charactersAlive;
}

// this function is called when a player's turn begins
void Player::updateCharacters()
{
	for (int i = 0; i < characters.size(); i ++)
	{
		if (!characters[i]->isDead())
			characters[i]->update();
	}
}

bool Player::lost()
{
    return (charactersAlive() == 0);
}

Player::~Player()
{
    for (int i = 0; i < characters.size(); i ++)
    {
        delete characters[i];
    }
}