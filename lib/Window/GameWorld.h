#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include "../../src/main.h"

class GameWorld
{
public:
	int gridLength = 8;
	vector<GameCell *> tiles;

	Stack<sf::Vector2f> *movStack;

	int distances [4][64][64];
	sf::Vector2f paths [4][64][64];

	Player* players[2];

	Character* currentCharacter = 0;	// Sobre qué personaje aplicar los métodos que se llamen desde el menú
	int currentPlayer = 0;				// De qué jugador es el turno (0 = Jugador1; 1 = Jugador2)
	int charactersPlayed = 0;			// Cuántos personajes ya jugaron en el turno actual

	void addCharacter(Character* character, int player);
	void setMap();
	void setFWMatrixes();
	void advanceState();

	GameWorld();
	virtual ~GameWorld();

private:
	bool emptyWorld();
};

#endif /* GAMEWORLD_H_ */
