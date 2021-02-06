#ifndef GAMESTATS_H_
#define GAMESTATS_H_

#include "../../src/main.h"

class GameStats : public Cell
{
public:
    GameStats(float xPos, float yPos, float ySize, float xSize, sf::Color color, GameWorld* world);

    void updateStats(GameWorld* world);
    void updateCharacterStats(Character* character, int player, int characterIndex);

    void setInfoText(std::string info);

    sf::Font font;

    sf::Text player1Text;
    sf::Text player2Text;

    sf::Text player1Stats [3][4];
    sf::Text player2Stats [3][4];

    sf::Text infoText; // Para escribir cosas como "Tal jugador ataco a tal otro"

    ~GameStats();
};

#endif
