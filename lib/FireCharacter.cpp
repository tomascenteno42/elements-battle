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
        cout << this->getName() << " was fed with wood. They got " << VALOR_ALIMENTO_FUEGO << " health points." << endl;
    }
    else
    {
        cout << this->getName() << " was not fed." << endl;
    }
}
