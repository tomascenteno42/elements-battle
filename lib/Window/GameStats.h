#ifndef GAMESTATS_H_
#define GAMESTATS_H_

#include "../../src/main.h"

class GameStats : public Cell
{
public:
    GameStats(float xPos, float yPos, float ySize, float xSize, sf::Color color, GameWorld* world);

    void clearCharactersList(sf::Text list[CHARACTERS_LIMIT]);

    void updateStats(GameWorld* world);
    void updateCharacterStats(Character* character, int player, int characterIndex);
    void clearCharacterStats(Character* character, int player, int characterIndex);

    void setCharacterList(std::vector<std::string> names);
    void setCharacterDetails(Character* character);
    void setChosenCharacters(string character, int index);

    void setInfoText(std::string info);
    void setCurrentCharacterMark(int player, int character);

    sf::Font font;

    bool showCharacterList;
    sf::Text characterList [20]; 

    bool showCharacterDetails;
    sf::Text characterDetails [5];

    bool showChosenChar;
    sf::Text chosenCharacters[8];

    bool showCharacterStats;
    sf::Text playerText [2];
    sf::Text playerStats [2][3][4];     // 2 jugadores, cada uno con 3 pj, cada uno con 4 stats

    sf::Text infoText; // Para escribir cosas como "Tal jugador ataco a tal otro"
    sf::Text currentCharacterMark;

    ~GameStats();
};

#endif
