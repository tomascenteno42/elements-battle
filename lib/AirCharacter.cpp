#include "../src/main.h"

bool AirCharacter::canBeFeeded()
{
    return false;
}

void AirCharacter::feed()
{
    if (!this->canBeFeeded())
    {
        cout << "No puedes alimentar a un personaje de aire.";
    }
}