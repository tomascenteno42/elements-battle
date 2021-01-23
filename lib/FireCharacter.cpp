#include "../src/main.h"

bool FireCharacter::canBeFeeded()
{
    return this->getLife() <= 85;
}

void FireCharacter::feed()
{
    if (this->canBeFeeded())
    {
        this->setLife(this->getLife() + VALOR_ALIMENTO_FUEGO);
        cout << this->getName() << " fue alimentado con madera. Y recibio " << VALOR_ALIMENTO_FUEGO << " de vida." << endl;
    }
    else
    {
        cout << this->getName() << " no pudo ser alimentado." << endl;
    }
}
