#include "../../src/main.h"

FireCharacter::FireCharacter(string n, int v, int es)
    :Character(n, v, es)
{
	cell.setFillColor(sf::Color(244, 65, 4));
}

elements FireCharacter::getElement()
{
	return FIRE;
}

bool FireCharacter::canBeFeeded()
{
    return true;
}

void FireCharacter::feed(GameWindow* window)
{
    if (canBeFeeded())
    {
        life = min(100, life + VALOR_ALIMENTO_FUEGO);
		energy = min(20, energy + 10);

        cout << name <<
		" was fed with wood. They got " << VALOR_ALIMENTO_FUEGO << " health points and 10 energy points"
		<< endl;
    }
    else
        cout << name << " was not fed." << endl;
}

void FireCharacter::attack(GameWindow* window)
{
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
		if (abs(enemyPos.y - pos.y) <= 1)
		{
			enemy->setLife(max(0,enemy->getLife() - 20));
			std::cout << getName() << " attacked " << enemy->getName() << " and inflicted 20 points of damage!" << std::endl;
		}
	}
}

void FireCharacter::defend(GameWindow* window)
{
	if (energy < 10)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}

	energy -= 10;
	life = min(100, life + 10);
	return;
}

void FireCharacter::update()
{
}
