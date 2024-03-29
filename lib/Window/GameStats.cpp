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

    characterList[0] = sf::Text("", font, 20);
    characterList[0].setFillColor(sf::Color::White);
    characterList[0].setPosition(sf::Vector2f(415, 10));
    for (int i = 1; i < 13; i ++)
    {
        characterList[i] = sf::Text("", font, 20);
        characterList[i].setFillColor(sf::Color::White);
        characterList[i].setPosition(sf::Vector2f(425, 10 + 30*i));     
    }

    characterDetails[0] = sf::Text("", font, 50);
    characterDetails[0].setFillColor(sf::Color::White);
    characterDetails[0].setPosition(sf::Vector2f(500, 70));
    for (int i = 1; i < 5; i ++)
    {
        characterDetails[i] = sf::Text("", font, 20);
        characterDetails[i].setFillColor(sf::Color::White);
        characterDetails[i].setPosition(sf::Vector2f(500, 130 + 30*i));
    }

    for (int i = 0; i < 8; i ++)
    {
        chosenCharacters[i] = sf::Text("", font, 20);
        chosenCharacters[i].setFillColor(sf::Color::White);
        if (i < 4)
            chosenCharacters[i].setPosition(sf::Vector2f(650, 50 + 30*i));
        else
            chosenCharacters[i].setPosition(sf::Vector2f(650, 70 + 30*i));
    }
}

void GameStats::clearCharactersList()
{
    for (size_t i = 1; i < 13; i++)
        characterList[i].setString("");
}

void GameStats::clearChosenChars()
{
    for (size_t i = 0; i < 8; i ++)
        chosenCharacters[i].setString("");
}

void GameStats::setCharacterList(std::vector<std::string> names)
{
    clearCharactersList();
    characterList[0].setString("CHARACTERS");
    for (int i = 1; i <= names.size(); i ++)
        characterList[i].setString(names[i-1]);
}

void GameStats::setCharacterDetails(Character* character)
{
    std::ostringstream life;
    life << character->getLife();

    characterDetails[0].setString(character->getName());
    characterDetails[1].setString("Element: " + parseElementToString(character->getElement()));
    characterDetails[2].setString("Max Life: " + life.str());
    characterDetails[3].setString("Shield: " + to_string(character->getShield()));
    characterDetails[4].setString("Energy: " + to_string(character->getEnergy()));
}

void GameStats::setChosenCharacters(string characterName, int charactersSelected)
{   
    int pos;
    switch (charactersSelected)
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
    chosenCharacters[0].setString("PLAYER 1");
    chosenCharacters[4].setString("PLAYER 2");
    chosenCharacters[pos].setString(characterName);
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
    for (int i = 0; i < 4; i ++)
        playerStats[player][characterIndex][i].setString("");
}

GameStats::~GameStats()
{
}