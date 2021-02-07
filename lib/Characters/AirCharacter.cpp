#include "../../src/main.h"

AirCharacter::AirCharacter(string n, int v, int es)
	:Character(n, v, es)
{
	cell.setFillColor(sf::Color(225, 255, 255));
}

elements AirCharacter::getElement()
{
	return AIR;
}

bool AirCharacter::canBeFeeded()
{
    return false;
}

void AirCharacter::feed(GameWindow* window)
{
    if (!this->canBeFeeded())
        cout << "You can't feed an Air character.";
}

void AirCharacter::attack(GameWindow* window)
{
	vector<Character*> enemies = window->world->players[(window->world->currentPlayer + 1) % 2]->characters;

	if (energy < 8)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}
	energy -= 8;

	Character* enemy = 0;
	for (int i = 0; i < enemies.size(); i ++)
	{
		enemy = enemies[i];

		enemy->setLife(max(0,enemy->getLife() - 15));
		std::cout << getName() << " attacked " << enemy->getName() << " and inflicted 15 points of damage!" << std::endl;
	}
}

void AirCharacter::defend(GameWindow* window)
{
	window->menu->setRequest("Enter where you would like to move: (ex: 2,5)");
	bool validDest = false;
	sf::Vector2f destination;
	while (!validDest)
	{
		destination = getPositionFromUser(window->menu);
		if (positionIsEmpty(window->world, destination))
			validDest = true;
	}
	cout << destination.x << "," << destination.y << endl;
	move(window, destination, 0);
}

void AirCharacter::update()
{
	energy = min(20, 5 + energy);
}