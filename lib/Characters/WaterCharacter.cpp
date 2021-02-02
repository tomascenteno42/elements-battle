#include "../../src/main.h"

bool WaterCharacter::canBeFeeded()
{
    return this->timesFeeded < 3 && this->getEnergy() <= 10;
}

void WaterCharacter::attack(Character* enemy)
{
	if (energy < 5)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}
	sf::Vector2f enemyPos = enemy->getPos();
	sf::Vector2f attackPos(enemyPos);	// esto se pide al usuario, el problema es que si lo paso por parametro a attack, deja de tener los mismos parametros que el resto de attacks
	if (attackPos == enemyPos)
	{
		enemy->setLife(max(0,enemy->getLife() - 20));
		std::cout << getName() << " attacked " << enemy->getName() << " and inflicted 20 points of damage!" << std::endl;
	}
}

void WaterCharacter::feed()
{
    if (this->canBeFeeded())
    {
        this->setEnergy(this->getEnergy() + VALOR_ALIMENTO_AGUA);
        cout << this->getName() << " was fed with plancton. They got " << VALOR_ALIMENTO_AGUA << " energy points." << endl;
        this->timesFeeded += 1;
    }
    else
    {
        cout << this->getName() << " was not fed." << endl;
    }
}
