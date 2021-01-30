#include "../src/main.h"

bool EarthCharacter::canBeFeeded()
{
    return this->getEnergy() <= 12;
}

void EarthCharacter::attack(Character* enemy)
{
	if (energy < 6)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}
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

void EarthCharacter::feed()
{
    if (this->canBeFeeded())
    {
        this->setEnergy(this->getEnergy() + VALOR_ALIMENTO_TIERRA);
        cout << this->getName() << " was fed with herbs. They got " << VALOR_ALIMENTO_TIERRA << " energy points" << endl;
    }
    else
    {
        cout << this->getName() << " was not fed." << endl;
    }
}
