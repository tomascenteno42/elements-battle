#include "../../src/main.h"

EarthCharacter::EarthCharacter(string n, int v, int es)
    :Character(n, v, es)
{
	cell.setFillColor(sf::Color(133, 91, 78));
}

elements EarthCharacter::getElement()
{
	return EARTH;
}

bool EarthCharacter::canBeFeeded()
{
    return true;
}

void EarthCharacter::feed(GameWindow* window)
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

void EarthCharacter::attack(GameWindow* window)
{
	vector<Character*> enemies = window->world->players[(window->world->currentPlayer + 1) % 2]->characters;

	if (energy < 6)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}

	energy -= 6;
	Character* enemy = 0;
	for (int i = 0; i < enemies.size(); i ++)
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
	if (energy < 5)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}

	energy -= 5;
	shield += 2;
	isDefending = true;
	return;
}

void EarthCharacter::update()
{
	if (isDefending)
	{
		shield -= 2;
		isDefending = false;
	}
}