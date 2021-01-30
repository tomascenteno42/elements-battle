#include "../src/main.h"

bool WaterCharacter::canBeFeeded()
{
    return this->timesFeeded < 3 && this->getEnergy() <= 10;
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
