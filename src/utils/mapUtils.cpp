#include "../main.h"

bool intersects(GameCell *cell1, GameCell *cell2)
{
    float cell1x = (cell1->getPos()).x;
    float cell1y = (cell1->getPos()).y;
    float cell2x = (cell2->getPos()).x;
    float cell2y = (cell2->getPos()).y;
    return ((abs(cell1x - cell2x) + abs(cell1y - cell2y)) <= 50);
}

void setInitialMatrixes(GameWorld *world, int distances[64][64], sf::Vector2f paths[64][64], elements element)
{
    for (int i = 0; i < 64; i++)
    {
        world->tiles[i]->setCost(element);
    }
    int cost;
    for (int i = 0; i < 64; i++)
    {
        cost = world->tiles[i]->getCost();
        for (int j = 0; j < 64; j++)
        {
            if (i != j)
                paths[i][j] = world->tiles[j]->getPos();
            if (i == j)
            {
                distances[i][j] = 0;
                paths[i][j] = sf::Vector2f(-50, -50);
            }
            else if (intersects(world->tiles[j], world->tiles[i]))
                distances[i][j] = cost;
            else
                distances[i][j] = 1000;
        }
    }
}

void shortestPathsFW(GameWorld *world, int distances[64][64], sf::Vector2f paths[64][64], elements element)
{
    setInitialMatrixes(world, distances, paths, element);
    GameCell *node;
    for (int k = 0; k < 64; k++)
    {
        node = world->tiles[k];
        for (int i = 0; i < 64; i++)
        {
            for (int j = 0; j < 64; j++)
            {
                int aux = distances[i][k] + distances[k][j];
                if (distances[i][j] > aux)
                {
                    distances[i][j] = aux;
                    paths[i][j] = node->getPos();
                }
            }
        }
    }
}

void loadFWMatrixes(GameWorld *world, int distances[4][64][64], sf::Vector2f paths[4][64][64])
{
    for (int i = 0; i < 4; i++)
    {
        elements element = static_cast<elements>(i + 1);
        int distances_aux[64][64];
        sf::Vector2f paths_aux[64][64];
        shortestPathsFW(world, distances_aux, paths_aux, element);
        for (int j = 0; j < 64; j++)
        {
            for (int k = 0; k < 64; k++)
            {
                distances[i][j][k] = distances_aux[j][k];
                paths[i][j][k] = paths_aux[j][k];
            }
        }
    }
}

void loadMovementsStack(Stack<sf::Vector2f> *movStack, sf::Vector2f startingPos, sf::Vector2f endingPos, sf::Vector2f paths[64][64])
{
    if (movStack->isEmpty() || movStack->peek() != endingPos)
        movStack->push(endingPos);

    int row = int(startingPos.x + 8 * startingPos.y);
    int col = int(endingPos.x + 8 * endingPos.y);

    sf::Vector2f intPos = paths[row][col];

    intPos.x /= 50;
    intPos.y /= 50;

    if (movStack->peek() == intPos)
        return;

    loadMovementsStack(movStack, intPos, endingPos, paths);
    loadMovementsStack(movStack, startingPos, intPos, paths);
}

void drawStats(GameWindow *win)
{
    win->draw(win->stats->getCell());

    for (int p = 0; p < 2; p ++)
    {
        win->draw(win->stats->playerText[p]);
        for (int i = 0; i < 3; i ++)
        {
            for (int j = 0; j < 4; j ++)
            {
                win->draw(win->stats->playerStats[p][i][j]);
            }
        }
    }

    win->draw(win->stats->infoText);
    if (!win->world->gameOver())
        win->draw(win->stats->currentCharacterMark);
}

void drawScreen(GameWindow *win)
{
    // Game board
    for (size_t i = 0; i < win->world->tiles.size(); i++)
    {
        win->draw(win->world->tiles[i]->getCell());
    }

    // Characters
    for (int p = 0; p < 2; p ++)
    {
        for (int i = 0; i < win->world->players[p]->characters.size(); i++)
            if (!win->world->players[p]->characters[i]->isDead())
                win->draw(win->world->players[p]->characters[i]->getCell());
    }


    // Game stats & info
    win->draw(win->stats->getCell());

    if (win->menu->getCurrentMenuIndex() == gameMenu1 || win->menu->getCurrentMenuIndex() == gameMenu2)
    {
        win->stats->updateStats(win->world);
        drawStats(win);
    }
    

    // Game menu & user interaction
    win->draw(win->menu->getCell());
    win->menu->drawCurrentMenu();
    win->menu->textbox->drawTextbox(win);
}



void loadNewGame(GameWorld* world)
{
	Character *character1 = new WaterCharacter("WaterChr1", 50, 2);
	character1->setPos(sf::Vector2f(0, 0));
	world->addCharacter(character1, 1);

	Character *character2 = new AirCharacter("AirChr1", 75, 0);
	character2->setPos(sf::Vector2f(1, 0));
	world->addCharacter(character2, 1);

	Character *character3 = new FireCharacter("FireChr1", 90, 1);
	character3->setPos(sf::Vector2f(0, 1));
	world->addCharacter(character3, 1);

	Character *character4 = new WaterCharacter("WaterChr2", 100, 1);
	character4->setPos(sf::Vector2f(6, 7));
	world->addCharacter(character4, 2);

	Character *character5 = new FireCharacter("FireChr2", 70, 2);
	character5->setPos(sf::Vector2f(7, 6));
	world->addCharacter(character5, 2);

	Character *character6 = new EarthCharacter("EarthChr2", 85, 1);
	character6->setPos(sf::Vector2f(7, 7));
	world->addCharacter(character6, 2);

	world->currentCharacter = character1;
    world->charactersPlayed = 0;
    world->currentPlayer = 0;
}
