#include "../../src/main.h"

AirCharacter::AirCharacter(string name, float life, int shield)
	:Character(name, life, shield)
{
	cell.setFillColor(sf::Color(225, 255, 255));
}

elements AirCharacter::getElement()
{
	return AIR;
}

bool AirCharacter::canBeFed()
{
    return false;
}

void AirCharacter::feed(GameWindow* window)
{
    window->stats->setInfoText("You can't feed an air character");
}

void AirCharacter::attack(GameWindow* window)
{
	if (energy < 8)
	{
		window->stats->setInfoText("Not enough EN");
		return;
	}

	vector<Character*> enemies = window->world->players[(window->world->currentPlayer + 1) % 2]->characters;
	std::string infoText = "";

	energy -= 8;

	Character* enemy = 0;
	float damage = 15;
	std::ostringstream damageStr;
	for (int i = 0; i < enemies.size(); i ++)
	{
		enemy = enemies[i];
		if (enemy->isDead())
			continue;
		enemy->adjustDamageTaken(damage, AIR);
		damage = min(damage, enemy->getLife());
		enemy->setLife(enemy->getLife() - damage);
		damageStr << damage;
		infoText.append(name + " inflicted " + damageStr.str() + " points of damage on " + enemy->getName() + "\n");
		damageStr.str("");
	}
	window->stats->setInfoText(infoText);
}

void AirCharacter::adjustDamageTaken(float &damage, elements attackerElement)
{
	switch (attackerElement)
	{
		case FIRE:
			damage = 30;
			break;
		case EARTH:
			damage = 10;
			break;
		default:
			break;
	}
	shieldDamage(damage);
}

void AirCharacter::defend(GameWindow* window)
{
	if (energy < 15)
	{
		window->stats->setInfoText("Not enough EN");
		return;
	}

	energy -= 15;

	window->menu->setRequest("Enter where you would like to move: (ex: 2,5)");
	bool validDest = false;
	sf::Vector2f destination;
	while (!validDest)
	{
		destination = getPositionFromUser(window->menu);
		if (positionIsEmpty(window->world, destination))
			validDest = true;
	}
	move(window, destination, 0);
}

void AirCharacter::update()
{
	energy = min(20, 5 + energy);
}