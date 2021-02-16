#include "../../src/main.h"

GameWorld::GameWorld()
{
	Player* player1 = new Player();
	Player* player2 = new Player();
	players[0] = player1;
	players[1] = player2;

	tiles = new Graph<GameCell*>(64);
	movStack = new Stack<sf::Vector2f>();
	setMap();
}


void GameWorld::setMap()
{
	loadMapData(this);
	connectVertices();
	setFWMatrixes();
}


void GameWorld::connectVertices()
{
	for (int v = 1; v <= 64; v ++)
	{
		if (v - 8 > 0)			// Connects to cell above
			tiles->addEdge(v, v-8);
		if (v + 8 <= 64)		// Connects to cell below
			tiles->addEdge(v, v+8);
		if ((v-1) % 8)			// Connects to cell on the left
			tiles->addEdge(v, v-1);
		if (v % 8 || v == 0)	// Connects to cell on the right
			tiles->addEdge(v, v+1);
	}
}


void GameWorld::addCharacter(Character* character, int player)
{
	players[player - 1]->addCharacter(character);
	tiles->getData(1 + character->getPos().x + 8*character->getPos().y)->data->setOccupied(true);
}


bool GameWorld::characterIsInGame(std::string name)
{
	for (int p = 0; p < 2; p ++)
	{
		for (int i = 0; i < players[p]->characters.size(); i ++)
		{
			if (players[p]->characters[i]->getName() == name)
				return true;
		}
	}
	return false;
}


void GameWorld::setFWMatrixes()
{
	for (int i = 0; i < 4; i++)
		shortestPathsFW(this, distances[i], paths[i], static_cast<elements>(i + 1));
}


void GameWorld::advanceState()
{
    charactersPlayed ++;

    if (charactersPlayed == 3)
    {
		canSave = true;
        charactersPlayed = 0;
		if (!gameOver())
		{
        	currentPlayer = (currentPlayer + 1) % 2;
			players[currentPlayer]->updateCharacters();
		}
    }

    currentCharacter = players[currentPlayer]->characters[charactersPlayed];
	if (currentCharacter->isDead())
		advanceState();
}


void GameWorld::updateOccupiedStates() {
	for (int i = 0; i < 64; i ++)
		tiles->getData(i+1)->data->setOccupied(false);

	for (int p = 0; p < 2; p ++)
	{
		for (int i = 0; i < players[p]->characters.size(); i ++)
		{	
			if (!players[p]->characters[i]->isDead())
			{
				sf::Vector2f playerPos = players[p]->characters[i]->getPos();
				tiles->getData(1 + playerPos.x + 8*playerPos.y)->data->setOccupied(true);
			}
		}
	}
}


bool GameWorld::gameOver()
{
	return (players[0]->lost() || players[1]->lost());
}


GameWorld::~GameWorld()
{
	delete players[0];
	delete players[1];
	delete movStack;
	delete tiles;
}
