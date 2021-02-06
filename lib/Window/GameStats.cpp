#include "../../src/main.h"

GameStats::GameStats(float xPos, float yPos, float ySize, float xSize, sf::Color color, GameWorld* world)
    :Cell(xPos, yPos, ySize, xSize, color)
{
    font.loadFromFile(FONT_FILE);
}

void GameStats::setInfoText(std::string info)
{
    infoText.setString(info);
}

void GameStats::updateStats(GameWorld* world)
{
    player1Text = sf::Text("PLAYER 1", font, 20);
    player1Text.setFillColor(sf::Color::White);
    player1Text.setPosition(sf::Vector2f(410,10));

    player2Text = sf::Text("PLAYER 2", font, 20);
    player2Text.setFillColor(sf::Color::White);
    player2Text.setPosition(sf::Vector2f(610,10));
    
    for (int i = 0; i < world->player1Characters.size(); i ++)
        updateCharacterStats(world->player1Characters[i], 1, i);
    for (int i = 0; i < world->player2Characters.size(); i ++)
        updateCharacterStats(world->player2Characters[i], 2, i);

    infoText = sf::Text("", font, 14);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(sf::Vector2f(410, 350));
    setInfoText("Info text goes here\nInfo text goes here\nInfo text goes here");
}

void GameStats::updateCharacterStats(Character* character, int player, int characterIndex)
{
    sf::Text* characterStats = 0;
    if (player == 1) characterStats = player1Stats[characterIndex];
    if (player == 2) characterStats = player2Stats[characterIndex];

    characterStats[0] = sf::Text(character->getName(), font, 18);
    characterStats[1] = sf::Text((std::string)"HP: " + to_string(character->getLife()), font, 16);
    characterStats[2] = sf::Text((std::string)"EN: " + to_string(character->getEnergy()), font, 16);
    characterStats[3] = sf::Text((std::string)"SH: " + to_string(character->getShield()), font, 16);

    float x;
    for (int i = 0; i < 4; i ++)
    {
        sf::Color color;
        if (i == 0)
        {
	        switch (character->getElement()) {
	            case EARTH:
		            color = sf::Color(133,91,78);
	            	break;
	            case FIRE:
	            	color = sf::Color(244,65,4);
	            	break;
	            case WATER:
	            	color = sf::Color(20,20,190);
	            	break;
	            case AIR:
	            	color = sf::Color(225,255,255);
	            	break;
	        }
        }
        else
            color = sf::Color::White;

        characterStats[i].setFillColor(color);
        if (player == 1) x = 410;
        if (player == 2) x = 610;
        if (i != 0) x += 20;
        characterStats[i].setPosition(sf::Vector2f(x, 50 + 100*characterIndex + 20*i));
    }
}

GameStats::~GameStats()
{
    /*
    for (int i = 0; i < 3; i ++)
    {
        delete [] player1Stats[i];
        delete [] player2Stats[i];
    }
    */
}



/*
        nameStat = new sf::Text("", font, 14);
        nameStat->setFillColor(sf::Color::Black);
        nameStat->setString(character->getName());
        nameStat->setPosition(sf::Vector2f(410, i*50 + 0));
        player1Stats[i][0] = nameStat;
*/