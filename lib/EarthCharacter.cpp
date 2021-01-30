#include "../src/main.h"

bool EarthCharacter::canBeFeeded()
{
    return this->getEnergy() <= 12;
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
