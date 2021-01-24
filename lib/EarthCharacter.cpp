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
        cout << this->getName() << " fue alimentado con hierbas. Y recibio " << VALOR_ALIMENTO_TIERRA << " puntos de energia" << endl;
    }
    else
    {
        cout << this->getName() << " no pudo ser alimentado." << endl;
    }
}
