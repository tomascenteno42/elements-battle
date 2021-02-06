#include "../../src/main.h"

bool FireCharacter::canBeFeeded()
{
    return this->getLife() <= 85;
}


void FireCharacter::attack(GameWindow* window)
{
	vector<Character*> enemies;
	if (window->world->currentPlayer == 1)
		enemies = window->world->player2Characters;
	else
		enemies = window->world->player1Characters;

	if (energy < 5)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}

	energy -= 5;
	Character* enemy = 0;
	for (int i = 0; i < 3; i ++)
	{
		enemy = enemies[i];
		sf::Vector2f enemyPos = enemy->getPos();
		if (abs(enemyPos.y - pos.y) <= 1)
		{
			enemy->setLife(max(0,enemy->getLife() - 20));
			std::cout << getName() << " attacked " << enemy->getName() << " and inflicted 20 points of damage!" << std::endl;
		}
	}
}

void FireCharacter::defend(GameWindow* window)
{
	return;
}

void FireCharacter::feed()
{
    if (this->canBeFeeded())
    {
        life = min(100, life + VALOR_ALIMENTO_FUEGO);
		energy = min(20, energy + 10);

        cout << this->getName() <<
		" was fed with wood. They got " << VALOR_ALIMENTO_FUEGO << " health points and 10 energy points"
		<< endl;
    }
    else
    {
        cout << this->getName() << " was not fed." << endl;
    }
}
