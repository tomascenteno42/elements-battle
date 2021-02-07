#include "../../src/main.h"

WaterCharacter::WaterCharacter(string n, int v, int es)
	:Character(n, v, es)
{
	cell.setFillColor(sf::Color(20, 20, 190));
}

elements WaterCharacter::getElement()
{
	return WATER;
}

bool WaterCharacter::canBeFeeded()
{
    return this->timesFeeded < 3;
}

void WaterCharacter::feed(GameWindow* window)
{
    if (canBeFeeded())
    {
        energy = min(20, energy + VALOR_ALIMENTO_AGUA);

        cout << name <<
		" was fed with plancton. They got " << VALOR_ALIMENTO_AGUA << " energy points."
		<< endl;

        timesFeeded += 1;
    }
    else
        cout << this->getName() << " was not fed." << endl;
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
			std::cout << name << " attacked " << enemy->getName() << " and inflicted 20 points of damage!" << std::endl;
		}
	}
}

void WaterCharacter::defend(GameWindow* window)
{
	vector<Character*> allies = window->world->players[window->world->currentPlayer % 2]->characters;

	if (energy < 12)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}

	energy -= 12;
	life = min(100, life + 50);
	Character* ally = 0;
	for (int i = 0; i < allies.size(); i ++)
	{
		ally = allies[i];
		if (ally != this)
		{
			ally->setLife(min(100, ally->getLife() + 10));
			std::cout << name << " healed " << ally->getName() << " 10 points of HP!" << std::endl;
		}
	}
}

void WaterCharacter::update()
{
}
