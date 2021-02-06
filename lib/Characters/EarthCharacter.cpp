#include "../../src/main.h"

bool EarthCharacter::canBeFeeded()
{
    return this->getEnergy() <= 12;
}

void EarthCharacter::attack(GameWindow* window)
{
	vector<Character*> enemies;
	if (window->world->currentPlayer == 1)
		enemies = window->world->player2Characters;
	else
		enemies = window->world->player1Characters;

	if (energy < 6)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}

	energy -= 6;
	Character* enemy = 0;
	for (int i = 0; i < 3; i ++)
	{
		enemy = enemies[i];
		sf::Vector2f enemyPos = enemy->getPos();
		int distance = max(abs(pos.x - enemyPos.x), abs(pos.y - enemyPos.y));
		int damage;
		if (distance <= 2)
			damage = 30;
		else if (distance <= 4)
			damage = 20;
		else
			damage = 10;
		enemy->setLife(max(0,enemy->getLife() - damage));
		std::cout << getName() << " attacked " << enemy->getName() << " and inflicted " << damage << " points of damage!" << std::endl;
	}
}

void EarthCharacter::defend(GameWindow* window)
{
	return;
}

void EarthCharacter::feed()
{
    if (this->canBeFeeded())
    {
        energy = min(20, energy + VALOR_ALIMENTO_TIERRA);
        cout << this->getName() <<
		" was fed with herbs. They got " << VALOR_ALIMENTO_TIERRA << " energy points"
		<< endl;
    }
    else
    {
        cout << this->getName() << " was not fed." << endl;
    }
}
