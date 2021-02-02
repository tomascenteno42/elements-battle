#include "../../src/main.h"

void MountainCell::setCost(elements element)
{
	switch (element)
	{
	case EARTH:
		cost = 0;
		break;
	case FIRE:
		cost = 1;
		break;
	case WATER:
		cost = 1;
		break;
	case AIR:
		cost = 2;
		break;
	}
}
