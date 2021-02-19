#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include "../../src/main.h"

class GameWorld
{
public:
	Graph<GameCell*>* tiles;
	Stack<sf::Vector2f>* movStack;
	int distances [4][64][64];
	sf::Vector2f paths [4][64][64];

	Player* players[2];
	int charactersSelected = 0;
	Character* currentCharacter = 0;
	int currentPlayer = 0;				// (0 = Player1; 1 = Player2)
	int charactersPlayed = 0;			// Amount of characters played on current turn
	bool canSave = true;

	GameWorld();

	/*
	 * Adds character to the chosen player's characters
	 */
	void addCharacter(Character* character, int player);

	/*
	 * Checks whether a character with a certain name is on any of the player's characters
	 */
	bool characterIsInGame(string name);

	/*
	 * Initializes tiles graph according to the map file and
	 * sets FW matrixes
	 */
	void setMap();

	/*
	 * This method is called once a player has finished commanding a character
	 * It sets the next current character and player
	 * If 3 characters already played, that means it is the other player's turn
	 * In case the next current character is dead, it jumps to the next one
	 */
	void advanceState();

	/*
	 * Updates occupied states of all cells according to alive characters' positions
	 */
	void updateOccupiedStates();

	/*
	 * Checks whether someone won
	 */
	bool gameOver();

	virtual ~GameWorld();

private:
	/*
	 * Adds edges between cells that are adjacent
	 */
	void connectVertices();

	/*
	 * Sets distances and paths matrixes for each of the four elements
	 */
	void setFWMatrixes();
};

#endif /* GAMEWORLD_H_ */
