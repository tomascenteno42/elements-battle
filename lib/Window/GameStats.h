#ifndef GAMESTATS_H_
#define GAMESTATS_H_

#include "../../src/main.h"

class GameStats : public Cell
{
public:
    GameStats(float xPos, float yPos, float ySize, float xSize, sf::Color color, GameWorld* world);

    void updateStats(GameWorld* world);
    void updateCharacterStats(Character* character, int player, int characterIndex);
    void clearCharacterStats(Character* character, int player, int characterIndex);

    void setCharacterList(std::vector<std::string> names);

    void setInfoText(std::string info);
    void setCurrentCharacterMark(int player, int character);

    sf::Font font;

    sf::Text characterList [20]; 
    sf::Text characterDetails [4];

    sf::Text playerText [2];
    sf::Text playerStats [2][3][4];     // 2 jugadores, cada uno con 3 pj, cada uno con 4 stats

    sf::Text infoText; // Para escribir cosas como "Tal jugador ataco a tal otro"
    sf::Text currentCharacterMark;

    ~GameStats();
};

#endif
