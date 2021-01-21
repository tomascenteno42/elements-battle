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
			if (i == j) distances[i][j] = 0;
			else if (intersects(world.tiles[j], world.tiles[i]))
				distances[i][j] = costo;
			else distances[i][j] = 100;
		}
	}
}

void shortestPathsFW(GameWorld world, int distances[64][64], sf::Vector2f paths[64][64], elements element) {
	setInitialMatrixes(world, distances, paths, element);
	for (int i = 0; i < 64; i ++) {
		GameCell* node = world.tiles[i];
		for (int row = 0; row < 64; row ++) {
			for (int col = 0; col < 64; col ++) {
				int aux = distances[row][i] + distances[i][col];
				if (aux < distances[row][col]) {
					distances[row][col] = aux;
					paths[row][col] = node -> getPos();
				}
			}
		}
	}
}
