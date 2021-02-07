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
    deleteDeadCharacters();
    Character *character = 0;

	for (int i = 0; i < characters.size(); i ++)        // maybe create a pute virtual method for character, which updates each character according to their element
	{
		character = characters[i];
		if (character->getElement() == AIR)
			character->setEnergy(min(20, 5 + character->getEnergy()));
		if (character->getElement() == EARTH && character->isDefending)
			character->setShield(character->getShield() - 2);
	}
}

Player::~Player()
{
    for (int i = 0; i < characters.size(); i ++)
    {
        delete characters[i];
    }
}