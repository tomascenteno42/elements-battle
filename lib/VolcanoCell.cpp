#include "../src/main.h"

void VolcanoCell::setCost(elements element)
{
	switch (element)
	{
	case EARTH:
		cost = 1;
		break;
	case FIRE:
		cost = 0;
		break;
	case WATER:
		cost = 2;
		break;
	case AIR:
		cost = 1;
		break;
	}
}
