#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include "../../src/main.h"

class GameWorld
{
public:
	int gridLength = 8;
	Graph<GameCell*> *tiles;

	Stack<sf::Vector2f> *movStack;

	int distances [4][64][64];
	sf::Vector2f paths [4][64][64];

	Player* players[2];

	int charactersSelected = 0;

	Character* currentCharacter = 0;	// Sobre qué personaje aplicar los métodos que se llamen desde el menú
	int currentPlayer = 0;				// De qué jugador es el turno (0 = Jugador1; 1 = Jugador2)
	int charactersPlayed = 0;			// Cuántos personajes ya jugaron en el turno actual (para saber cuando le toca al otro jugador)

	void addCharacter(Character* character, int player);

	void setMap();
	void connectVertices();
	void setFWMatrixes();

	void advanceState();
	void updateOccupiedStates();
	void reset();

	bool gameOver();
	bool canSave = true;

	GameWorld();
	virtual ~GameWorld();
};

#endif /* GAMEWORLD_H_ */
