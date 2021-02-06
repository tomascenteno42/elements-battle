#include "../../src/main.h"

bool AirCharacter::canBeFeeded()
{
    return false;
}


void AirCharacter::attack(GameWindow* window)
{
	vector<Character*> enemies;
	if (window->world->currentPlayer == 1)
		enemies = window->world->player2Characters;
	else
		enemies = window->world->player1Characters;

	if (energy < 8)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}
	energy -= 8;
	Character* enemy = 0;
	for (int i = 0; i < 3; i ++)
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
