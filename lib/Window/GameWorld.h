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
	vector<Character*> player1Characters;
	vector<Character*> player2Characters;

	Character* currentCharacter = 0;	// Sobre qué personaje aplicar los métodos que se llamen desde el menú
	int currentPlayer = 1;				// De qué jugador es el turno
	int charactersPlayed = 0;			// Cuántos personajes ya jugaron en el turno actual

	void addCharacter(Character* character, int player);
	void setMap();
	void setFWMatrixes();

	GameWorld();
	virtual ~GameWorld();

private:
	bool emptyWorld();
};

#endif /* GAMEWORLD_H_ */
