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
        cout << this->getName() << " fue alimentado con plancton. Y recibio " << VALOR_ALIMENTO_AGUA << " puntos de energia." << endl;
        this->timesFeeded += 1;
    }
    else
    {
        cout << this->getName() << " no pudo ser alimentado." << endl;
    }
}