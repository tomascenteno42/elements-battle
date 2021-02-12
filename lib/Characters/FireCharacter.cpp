#include "../../src/main.h"

FireCharacter::FireCharacter(string name, float life, int shield)
    :Character(name, life, shield)
{
	cell.setFillColor(sf::Color(244, 65, 4));
}

elements FireCharacter::getElement()
{
	return FIRE;
}

bool FireCharacter::canBeFed()
{
    return true;
}

void FireCharacter::feed(GameWindow* window)
{
	float lifeHeal = min((float)VALOR_ALIMENTO_FUEGO, maxLife - life);
	int energyHeal = min(10, 20 - energy);
	life += lifeHeal;
	energy += energyHeal;
	std::ostringstream lifeHealStr;
	lifeHealStr << lifeHeal;

	window->stats->setInfoText(name + " was fed with wood,\nthey got " + lifeHealStr.str() + " HP and " + to_string(energyHeal) + " EN");
}

void FireCharacter::attack(GameWindow* window)
{
	if (energy < 5)
	{
		window->stats->setInfoText("Not enough EN");
		return;
	}

	vector<Character*> enemies = window->world->players[(window->world->currentPlayer + 1) % 2]->characters;
	std::string infoText = "";

	energy -= 5;

	Character* enemy = 0;
	float damage = 20;
	std::ostringstream damageStr;
	for (int i = 0; i < enemies.size(); i ++)
	{
		enemy = enemies[i];
		if (enemy->isDead())
			continue;
		sf::Vector2f enemyPos = enemy->getPos();
		if (abs(enemyPos.y - pos.y) <= 1)
		{
			enemy->adjustDamageTaken(damage, FIRE);
			damage = min(damage, enemy->getLife());
			enemy->setLife(enemy->getLife() - damage);
			damageStr << damage;
			infoText.append(name + " inflicted " + damageStr.str() + " points of damage on " + enemy->getName() + "\n");
			damageStr.str("");
		}
	}
	window->stats->setInfoText(infoText);
}

void FireCharacter::adjustDamageTaken(float &damage, elements attackerElement)
{
	switch (attackerElement)
	{
		case AIR:
			damage = 10;
			break;
		case WATER:
			damage = 30;
			break;
		default:
			break;
	}
	shieldDamage(damage);	
}

void FireCharacter::defend(GameWindow* window)
{
	if (energy < 10)
	{
		window->stats->setInfoText("Not enough EN");
		return;
	}

	energy -= 10;

	float heal = min(maxLife - life, (float)10);
	life += heal;
	std::ostringstream healStr;
	healStr << heal;
	window->stats->setInfoText(name + " healed " + healStr.str() + " HP\n");
	return;
}

void FireCharacter::update()
{
	if (energy == 0)
		life = max((float)0, life - 5);
}
