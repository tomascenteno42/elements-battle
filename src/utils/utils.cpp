#include "../main.h"

colors parseStringToColor(std::string colorToParse) {
	if (colorToParse == "lake") {
		return lake;
	} else if (colorToParse == "volcano") {
		return volcano;
	} else if (colorToParse == "cliff") {
		return cliff;
	} else if (colorToParse == "mountain") {
		return mountain;
	} else if (colorToParse == "path") {
		return path;
	} else {
		return empty;
	}
}

sf::Color parseColorToSf(colors color) {

	switch (color) {
	case lake:
		return sf::Color::Cyan;
		break;
	case volcano:
		return sf::Color::Red;
		break;
	case cliff:
		return sf::Color::White;
		break;
	case mountain:
		return sf::Color::Black;
		break;
	case path:
		return sf::Color::Yellow;
		break;
	case empty:
		return sf::Color::Magenta;
		break;
	default:
		return sf::Color::Blue;
		break;
	}
}

