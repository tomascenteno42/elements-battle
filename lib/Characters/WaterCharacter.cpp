#include "../../src/main.h"

bool WaterCharacter::canBeFeeded()
{
    return this->timesFeeded < 3 && this->getEnergy() <= 10;
}


void WaterCharacter::attack(GameWindow* window)
{
	window->menu->setRequest("Attack at position (ex: 2,5): ");
	sf::Vector2f attackPos = getPositionFromUser(window->menu);

	vector<Character*> enemies = window->world->players[(window->world->currentPlayer + 1) % 2]->characters;

	if (energy < 5)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}

	energy -= 5;
	Character* enemy = 0;
	for (int i = 0; i < enemies.size(); i ++)
	{
		enemy = enemies[i];
		sf::Vector2f enemyPos = enemy->getPos();
		if (attackPos == enemyPos)
		{
			enemy->setLife(max(0,enemy->getLife() - 20));
			std::cout << getName() << " attacked " << enemy->getName() << " and inflicted 20 points of damage!" << std::endl;
		}
	}
}

void WaterCharacter::defend(GameWindow* window)
{
	return;
}

void WaterCharacter::feed()
{
    if (this->canBeFeeded())
    {
        energy = min(20, energy + VALOR_ALIMENTO_AGUA);

        cout << this->getName() <<
		" was fed with plancton. They got " << VALOR_ALIMENTO_AGUA << " energy points."
		<< endl;

        this->timesFeeded += 1;
    }
    else
    {
        cout << this->getName() << " was not fed." << endl;
    }
}
