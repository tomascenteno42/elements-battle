#include "../../src/main.h"

bool AirCharacter::canBeFeeded()
{
    return false;
}

void AirCharacter::attack(Character* enemy)
{
	if (energy < 8)
	{
		std::cout << "Not enough energy" << std::endl;
		return;
	}
	if (0 <= 1)
	{
		enemy->setLife(max(0,enemy->getLife() - 15));
		std::cout << getName() << " attacked " << enemy->getName() << " and inflicted 15 points of damage!" << std::endl;
	}
}

void AirCharacter::feed()
{
    if (!this->canBeFeeded())
    {
        cout << "You can't feed an Air character.";
    }
}
