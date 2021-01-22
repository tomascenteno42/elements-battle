#include "../main.h"

terrains parseStringToTerrain(std::string colorToParse) {
	if (colorToParse == "l") {
		return lake;
	} else if (colorToParse == "v") {
		return volcano;
	} else if (colorToParse == "c") {
		return cliff;
	} else if (colorToParse == "m") {
		return mountain;
	} else if (colorToParse == "p") {
		return path;
	} else {
		return empty;
	}
}

sf::Color parseTerrainToSf(terrains terrain) {

	switch (terrain) {
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

bool intersects(GameCell* cell1, GameCell* cell2) {
	float cell1x = (cell1 -> getPos()).x;
	float cell1y = (cell1 -> getPos()).y;
	float cell2x = (cell2 -> getPos()).x;
	float cell2y = (cell2 -> getPos()).y;
	return ((abs(cell1x - cell2x) + abs(cell1y - cell2y)) <= 50);
}

void setInitialMatrixes(GameWorld world, int distances[64][64], sf::Vector2f paths[64][64], elements element) {
	for (int i = 0; i < 64; i ++) {
		world.tiles[i] -> setCost(element);
	}
	int costo;
	for (int i = 0; i < 64; i ++) {
		costo = world.tiles[i] -> getCost();
		for (int j = 0; j < 64; j ++) {
			if (i != j) paths[i][j] = world.tiles[j] -> getPos();
			if (i == j) {
				distances[i][j] = 0;
				paths[i][j] = sf::Vector2f(-50,-50);
			}
			else if (intersects(world.tiles[j], world.tiles[i]))
				distances[i][j] = costo;
			else distances[i][j] = 1000;
		}
	}
}

void printDistances(int distances[64][64]) {
	std::cout << "[" << std::endl;
	for (int i = 0; i < 16; i ++) {
		std::cout << "[";
		for (int j = 0; j < 16; j ++) {
			std::cout << distances[i][j] << ",";
		}
		std::cout << "]" << std::endl;
	}
	std::cout << "]" << std::endl;
}

void printPaths(sf::Vector2f paths[64][64]) {
	std::cout << "[" << std::endl;
	for (int i = 0; i < 16; i ++) {
		std::cout << "[";
		for (int j = 0; j < 16; j ++) {
			std::cout << "[" << paths[i][j].x / 50 << "," << paths[i][j].y / 50 << "],";
		}
		std::cout << "]" << std::endl;
	}
	std::cout << "]" << std::endl;
}

void shortestPathsFW(GameWorld world, int distances[64][64], sf::Vector2f paths[64][64], elements element) {
	setInitialMatrixes(world, distances, paths, element);
	for (int k = 0; k < 64; k ++) {
		GameCell* node = world.tiles[k];
		for (int i = 0; i < 64; i ++) {
			for (int j = 0; j < 64; j ++) {
				int aux = distances[i][k] + distances[k][j];
				if (distances[i][j] > aux) {
					distances[i][j] = aux;
					paths[i][j] = node -> getPos();
				}
			}
		}
	}
}


void loadMovementsStack(Stack* movStack, sf::Vector2f startingPos, sf::Vector2f endingPos, sf::Vector2f paths[64][64]) {
	if (movStack -> isEmpty() || movStack -> peek() != endingPos)
		movStack -> push(endingPos);
	int row = int(startingPos.x + 8 * startingPos.y);
	int col = int(endingPos.x + 8 * endingPos.y);
	sf::Vector2f intPos = paths[row][col];
	intPos.x /= 50;
	intPos.y /= 50;
	if (movStack -> peek() == intPos) return;
	loadMovementsStack(movStack, intPos, endingPos, paths);
	loadMovementsStack(movStack, startingPos, intPos, paths);
}

sf::Vector2f askDestination() {
	string x ,y;
	std::cout << "Move to x (0-7): ";
	std::cin >> x;
	std::cout << "Move to y (0-7): ";
	std::cin >> y;
	return sf::Vector2f(stof(x),stof(y));
}
