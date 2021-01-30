#include "../src/main.h"

void LakeCell::setCost(elements element)
{
	switch (element)
	{
	case EARTH:
		cost = 1;
		break;
	case FIRE:
		cost = 2;
		break;
	case WATER:
		cost = 0;
		break;
	case AIR:
		cost = 1;
		break;
	}
}
