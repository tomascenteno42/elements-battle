#include "../../src/main.h"

WaterCharacter::WaterCharacter(string name, float life, int shield)
	:Character(name, life, shield)
{
	cell.setFillColor(sf::Color(20, 20, 190));
}

elements WaterCharacter::getElement()
{
	return WATER;
}

bool WaterCharacter::canBeFed()
{
    return this->timesFed < 3;
}

void WaterCharacter::feed(GameWindow* window)
{
    if (canBeFed())
    {
		int heal = min(VALOR_ALIMENTO_AGUA, 20 - energy);
        energy += heal;
        window->stats->setInfoText(name + " was fed with plancton,\nthey got " + to_string(heal) + " EN");
        timesFed += 1;
    }
    else
        window->stats->setInfoText("You can't feed " + name + " again");
}

void WaterCharacter::attack(GameWindow* window)
{
	if (energy < 5)
	{
		window->stats->setInfoText("Not enough EN");
		return;
	}

	window->menu->setRequest("Attack at position (ex: 2,5): ");
	sf::Vector2f attackPos = getPositionFromUser(window->menu);
	vector<Character*> enemies = window->world->players[(window->world->currentPlayer + 1) % 2]->characters;

	energy -= 5;

	Character* enemy = 0;
	float damage = 20;
	std::ostringstream damageStr;
	for (int i = 0; i < enemies.size(); i ++)
	{
		enemy = enemies[i];
		sf::Vector2f enemyPos = enemy->getPos();
		if (attackPos == enemyPos)
		{
			enemy->adjustDamageTaken(damage, WATER);
			damage = min(damage, enemy->getLife());
			enemy->setLife(enemy->getLife() - damage);
			damageStr << damage;
			window->stats->setInfoText(name + " attacked " + enemy->getName() + "\nand inflicted " + damageStr.str() + " points of damage\n");
			damageStr.str("");
		}
	}
}

void WaterCharacter::adjustDamageTaken(float &damage, elements attackerElement)
{
	switch (attackerElement)
	{
		case FIRE:
			damage = 10;
			break;
		case EARTH:
			damage += 20;
			break;
		default:
			break;
	}
	shieldDamage(damage);	
}

void WaterCharacter::defend(GameWindow* window)
{
	if (energy < 12)
	{
		window->stats->setInfoText("Not enough EN");
		return;
	}

	vector<Character*> allies = window->world->players[window->world->currentPlayer % 2]->characters;
	std::string infoText = "";

	energy -= 12;

	float heal = min((float)50, maxLife - life);
	life += heal;
	std::ostringstream healStr;
	healStr << heal;
	infoText.append(name + " healed " + healStr.str() + " HP\n");

	Character* ally = 0;
	healStr.str("");
	for (int i = 0; i < allies.size(); i ++)
	{
		ally = allies[i];
		if (ally != this)
		{
			heal = min((float)10, ally->getMaxLife() - ally->getLife());
			ally->setLife(ally->getLife() + heal);
			healStr << heal;
			infoText.append(name + " healed " + ally->getName() + " " + healStr.str() + " HP\n");
			healStr.str("");
		}
	}
	window->stats->setInfoText(infoText);
}

void WaterCharacter::update()
{
}
