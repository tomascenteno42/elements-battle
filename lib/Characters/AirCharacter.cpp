#include "../../src/main.h"

bool AirCharacter::canBeFeeded()
{
    return false;
}


void AirCharacter::attack(GameWindow* window)
{
	vector<Character*> enemies = window->world->players[(window->world->currentPlayer + 1) % 2]->characters;

	if (energy < 8)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}
	energy -= 8;

	Character* enemy = 0;
	for (int i = 0; i < enemies.size(); i ++)
	{
		enemy = enemies[i];

		enemy->setLife(max(0,enemy->getLife() - 15));
		std::cout << getName() << " attacked " << enemy->getName() << " and inflicted 15 points of damage!" << std::endl;
	}
}

void AirCharacter::defend(GameWindow* window)
{
	window->menu->setRequest("Move to position (example: 2,5): ");
	sf::Vector2f destination = getPositionFromUser(window->menu);

	return;
}

void AirCharacter::feed()
{
    if (!this->canBeFeeded())
    {
        cout << "You can't feed an Air character.";
    }
}
