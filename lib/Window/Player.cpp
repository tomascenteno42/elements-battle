#include "../../src/main.h"

Player::Player()
{
}

void Player::addCharacter(Character* character)
{
    characters.push_back(character);
    charactersAlive ++;
}

void Player::deleteDeadCharacters()
{
	std::vector<int*>::size_type i = 0;
	while (i < characters.size())
	{
   		if (characters[i] -> isDead())
        {
		    delete characters[i];
    	    characters.erase(characters.begin() + i);
            charactersAlive --;
		}
   		else
    	    i++;
    }
}

// this function is called when a player's turn begins
void Player::updateCharacters()
{
	for (int i = 0; i < characters.size(); i ++)
		characters[i]->update();
}

Player::~Player()
{
    for (int i = 0; i < characters.size(); i ++)
    {
        delete characters[i];
    }
}