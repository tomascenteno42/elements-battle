#include "../../src/main.h"

bool FireCharacter::canBeFeeded()
{
    return this->getLife() <= 85;
}

void FireCharacter::attack(Character* enemy)
{
	if (energy < 5)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}
	sf::Vector2f enemyPos = enemy->getPos();
	if (abs(enemyPos.y - pos.y) <= 1)
	{
		enemy->setLife(max(0,enemy->getLife() - 20));
		std::cout << getName() << " attacked " << enemy->getName() << " and inflicted 20 points of damage!" << std::endl;
	}
}

void FireCharacter::feed()
{
    if (this->canBeFeeded())
    {
        this->setLife(this->getLife() + VALOR_ALIMENTO_FUEGO);
        cout << this->getName() << " was fed with wood. They got " << VALOR_ALIMENTO_FUEGO << " health points." << endl;
    }
    else
    {
        cout << this->getName() << " was not fed." << endl;
    }
}
