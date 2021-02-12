#include "../../src/main.h"

EarthCharacter::EarthCharacter(string name, float life, int shield)
    :Character(name, life, shield)
{
	cell.setFillColor(sf::Color(133, 91, 78));
}

elements EarthCharacter::getElement()
{
	return EARTH;
}

bool EarthCharacter::canBeFed()
{
    return true;
}

void EarthCharacter::feed(GameWindow* window)
{
	int heal = min(VALOR_ALIMENTO_TIERRA, 20 - energy);
	energy += heal;

    window->stats->setInfoText(name + " was fed with herbs,\nthey got " + to_string(heal) + " EN");
}

void EarthCharacter::attack(GameWindow* window)
{
	if (energy < 6)
	{
		window->stats->setInfoText("Not enough EN");
		return;
	}

	vector<Character*> enemies = window->world->players[(window->world->currentPlayer + 1) % 2]->characters;
	std::string infoText = "";

	energy -= 6;

	Character* enemy = 0;
	float damage = 0;
	int distance = 0;
	std::ostringstream damageStr;
	for (int i = 0; i < enemies.size(); i ++)
	{
		enemy = enemies[i];
		if (enemy->isDead())
			continue;
		sf::Vector2f enemyPos = enemy->getPos();
		distance = max(abs(pos.x - enemyPos.x), abs(pos.y - enemyPos.y));
		if (distance <= 2)
			damage = 30;
		else if (distance <= 4)
			damage = 20;
		else
			damage = 10;
		enemy->adjustDamageTaken(damage, EARTH);
		damage = min(damage, enemy->getLife());
		enemy->setLife(enemy->getLife() - damage);
		damageStr << damage;
		infoText.append(name + " inflicted " + damageStr.str() + " points of damage on " + enemy->getName() + "\n");
		damageStr.str("");
	}
	window->stats->setInfoText(infoText);
}

void EarthCharacter::adjustDamageTaken(float &damage, elements attackerElement)
{
	switch (attackerElement)
	{
		case WATER:
			damage = 10;
			break;
		case AIR:
			damage = 20;
			break;
		default:
			break;
	}
	shieldDamage(damage);	
}

void EarthCharacter::defend(GameWindow* window)
{
	if (energy < 5)
	{
		window->stats->setInfoText("Not enough EN");
		return;
	}

	energy -= 5;
	shield += 2;
	isDefending = true;
	window->stats->setInfoText(name + " is now defending");
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