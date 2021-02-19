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

void GameStats::clearCharactersList(sf::Text texts[CHARACTERS_LIMIT])
{
    for (size_t i = 0; i < CHARACTERS_LIMIT; i++)
    {
        texts[i] = sf::Text("", font, 0);
    }   
}

void GameStats::setCharacterList(std::vector<std::string> names)
{
    clearCharactersList(characterList);
    characterList[0] = sf::Text("CHARACTERS LIST", font, 20);
    characterList[0].setFillColor(sf::Color::White);
    characterList[0].setPosition(sf::Vector2f(415, 50));
    for (int i = 1; i < names.size() + 1; i ++)
    {
        characterList[i] = sf::Text(names[i-1], font, 20);
        characterList[i].setFillColor(sf::Color::White);
        characterList[i].setPosition(sf::Vector2f(415, 60 + 30*i));
    }
}

void GameStats::setCharacterDetails(Character* character)
{
    characterDetails[0] = sf::Text(character->getName(), font, 50);
    characterDetails[1] = sf::Text("Element: " + parseElementToString(character->getElement()), font, 20);
    characterDetails[2] = sf::Text("Life: " + to_string(character->getLife()), font, 20);
    characterDetails[3] = sf::Text("Shield: " + to_string(character->getShield()), font, 20);
    characterDetails[4] = sf::Text("Energy: " + to_string(character->getEnergy()), font, 20);

    characterDetails[0].setFillColor(sf::Color::White);
    characterDetails[0].setPosition(sf::Vector2f(500, 70));

    for (int i = 1; i < 5; i++)
    {
        characterDetails[i].setFillColor(sf::Color::White);
        characterDetails[i].setPosition(sf::Vector2f(500, 130 + 30*i));
    }
}

void GameStats::setChosenCharacters(string character, int selectedPlayers)
{   
    int pos;
    switch (selectedPlayers)
    {
    case 0: pos = 1;
        break;
    case 1: pos = 5;
        break;
    case 2: pos = 2;
        break;
    case 3: pos = 6;
        break;
    case 4: pos = 3;
        break;    
    case 5: pos = 7;
        break;
    }

    chosenCharacters[0] = sf::Text("PLAYER 1", font, 20);
    chosenCharacters[4] = sf::Text("PLAYER 2", font, 20);
    chosenCharacters[pos] = sf::Text(character, font, 20);

    for (size_t i = 0; i < 8; i++)
    {
        chosenCharacters[i].setFillColor(sf::Color::White);
        chosenCharacters[i].setPosition(sf::Vector2f(650, 50 + 30*i));
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