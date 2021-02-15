#include "../../src/main.h"

GameStats::GameStats(float xPos, float yPos, float ySize, float xSize, sf::Color color, GameWorld* world)
    :Cell(xPos, yPos, ySize, xSize, color)
{
    font.loadFromFile(FONT_FILE);

    for (int p = 0; p < 2; p ++)
    {
        playerText[p] = sf::Text("PLAYER " + to_string(p+1), font, 20);
        playerText[p].setFillColor(sf::Color::White);
        playerText[p].setPosition(sf::Vector2f(410 + 200*p, 10));
    }

    infoText = sf::Text("", font, 14);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(sf::Vector2f(410, 340));

    currentCharacterMark = sf::Text("<--", font, 14);
    currentCharacterMark.setFillColor(sf::Color::Yellow);

    showCharacterList = false;
    showCharacterDetails = false;
    showCharacterStats = false;
}

void GameStats::setCharacterList(std::vector<std::string> names)
{
    for (int i = 0; i < names.size(); i ++)
    {
        characterList[i] = sf::Text(names[i], font, 16);
        characterList[i].setFillColor(sf::Color::White);
        characterList[i].setPosition(sf::Vector2f(410, 10 + 20*i));
    }
}

void GameStats::setCharacterDetails(Character* character)
{
    characterDetails[0] = sf::Text(character->getName(), font, 16);
    characterDetails[1] = sf::Text("Element: " + to_string(character->getElement()), font, 16);
    characterDetails[2] = sf::Text("Life: " + to_string(character->getLife()), font, 16);
    characterDetails[3] = sf::Text("Shield: " + to_string(character->getShield()), font, 16);
    characterDetails[4] = sf::Text("Energy: " + to_string(character->getEnergy()), font, 16);
    for (int i = 0; i < 5; i++)
    {
        characterDetails[i].setFillColor(sf::Color::White);
        characterDetails[i].setPosition(sf::Vector2f(410, 10 + 20*i));
    }
}

void GameStats::setInfoText(std::string info)
{
    infoText.setString(info);
}

void GameStats::setCurrentCharacterMark(int player, int character)
{
    currentCharacterMark.setPosition(sf::Vector2f(550 + 200*(player-1), 52 + 100*character));
}

void GameStats::updateStats(GameWorld* world)
{
    for (int p = 0; p < 2; p ++)
    {
        for (int i = 0; i < world->players[p]->characters.size(); i ++) {
            if (world->players[p]->characters[i]->isDead())
                clearCharacterStats(world->players[p]->characters[i], p, i);
            else
                updateCharacterStats(world->players[p]->characters[i], p, i);
        }
    }

    setCurrentCharacterMark(world->currentPlayer + 1, world->charactersPlayed);
}

void GameStats::updateCharacterStats(Character* character, int player, int characterIndex)
{
    std::ostringstream life;
    life << character->getLife();

    playerStats[player][characterIndex][0] = sf::Text(character->getName(), font, 18);
    playerStats[player][characterIndex][1] = sf::Text((std::string)"HP: " + life.str() + "/" + to_string(character->getMaxLife()), font, 16);
    playerStats[player][characterIndex][2] = sf::Text((std::string)"EN: " + to_string(character->getEnergy()) + "/20", font, 16);
    playerStats[player][characterIndex][3] = sf::Text((std::string)"SH: " + to_string(character->getShield()), font, 16);

    float x;
    for (int i = 0; i < 4; i ++)
    {
        sf::Color color;
        if (i == 0)
            color = character->getCell().getFillColor();
        else
            color = sf::Color::White;

        playerStats[player][characterIndex][i].setFillColor(color);
        if (player == 0) x = 410;
        if (player == 1) x = 610;
        if (i != 0) x += 20;
        playerStats[player][characterIndex][i].setPosition(sf::Vector2f(x, 50 + 100*characterIndex + 20*i));
    }
}

void GameStats::clearCharacterStats(Character* character, int player, int characterIndex)
{
    sf::Text* characterStats = 0;

    for (int i = 0; i < 4; i ++)
        playerStats[player][characterIndex][i].setString("");
}

GameStats::~GameStats()
{
}