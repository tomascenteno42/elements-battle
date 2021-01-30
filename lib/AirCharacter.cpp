#include "../src/main.h"

bool AirCharacter::canBeFeeded()
{
    return false;
}

void AirCharacter::feed()
{
    if (!this->canBeFeeded())
    {
        cout << "You can't feed an Air character.";
    }
}
