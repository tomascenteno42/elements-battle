#include "../main.h"

void setInitialMatrixes(Graph<GameCell*>* tilesGraph, int distances[64][64], sf::Vector2f paths[64][64], elements element)
{
    GraphData<GameCell*>* vertex = 0;
    GameCell* cell = 0;
    vector<int> adjList;
    int cost = 0;
    for (int i = 0; i < 64; i++)
    {
        vertex = tilesGraph->getData(i+1);
        cell = vertex->data;
        cost = vertex->cost;
        cell->adjustCost(cost, element);
        adjList = vertex->adjList;

        for (int j = 0; j < 64; j++)
        {
            if (i != j)
                paths[i][j] = tilesGraph->getData(j+1)->data->getPos();
            if (i == j)
            {
                distances[i][j] = 0;
                paths[i][j] = sf::Vector2f(-50, -50);
            }
            else if (dataIsInVector(adjList, j+1))
                distances[i][j] = cost;
            else
                distances[i][j] = 1000;
        }
    }
}


void shortestPathsFW(GameWorld* world, int distances[64][64], sf::Vector2f paths[64][64], elements element)
{
    setInitialMatrixes(world->tiles, distances, paths, element);
    GameCell* node;
    for (int k = 0; k < 64; k++)
    {
        node = world->tiles->getData(k+1)->data;
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

void loadFWMatrixes(GameWorld* world, int distances[4][64][64], sf::Vector2f paths[4][64][64])
{
    for (int i = 0; i < 4; i++)
    {
        elements element = static_cast<elements>(i + 1);
        int distances_aux[64][64];
        sf::Vector2f paths_aux[64][64];
        shortestPathsFW(world, distances_aux, paths_aux, element);
        for (int j = 0; j < 64; j++)
            for (int k = 0; k < 64; k++)
            {
                distances[i][j][k] = distances_aux[j][k];
                paths[i][j][k] = paths_aux[j][k];
            }
    }
}

void loadMovementsStack(Stack<sf::Vector2f>* movStack, sf::Vector2f startingPos, sf::Vector2f endingPos, sf::Vector2f paths[64][64])
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

void drawStats(GameWindow* window)
{
    window->draw(window->stats->getCell());

    for (int p = 0; p < 2; p ++)
    {
        window->draw(window->stats->playerText[p]);
        for (int i = 0; i < 3; i ++)
            for (int j = 0; j < 4; j ++)
                window->draw(window->stats->playerStats[p][i][j]);
    }

    window->draw(window->stats->infoText);
    if (!window->world->gameOver())
        window->draw(window->stats->currentCharacterMark);
}

void drawScreen(GameWindow* window)
{
    // Game board
    for (size_t i = 0; i < window->world->tiles->getVertices(); i++)
        window->draw(window->world->tiles->getData(i+1)->data->getCell());

    // Characters
    for (int p = 0; p < 2; p ++)
        for (int i = 0; i < window->world->players[p]->characters.size(); i++)
            if (!window->world->players[p]->characters[i]->isDead())
                window->draw(window->world->players[p]->characters[i]->getCell());

    // Game stats & info
    window->draw(window->stats->getCell());
    
    if (window->stats->showCharacterList)
        for (size_t i = 0; i < 13; i++)
            window->draw(window->stats->characterList[i]);

    if (window->stats->showCharacterDetails)
        for (size_t i = 0; i < 5; i++)
            window->draw(window->stats->characterDetails[i]);

    if (window->stats->showChosenChar)
        for (size_t i = 0; i < 8; i++)
            window->draw(window->stats->chosenCharacters[i]);

    if (window->menu->getCurrentMenuIndex() == gameMenu1 || window->menu->getCurrentMenuIndex() == gameMenu2)
    {
        window->stats->updateStats(window->world);
        drawStats(window);
    }

    // Game menu & user interaction
    window->draw(window->menu->getCell());
    window->menu->drawCurrentMenu();
    window->menu->textbox->drawTextbox(window);
}
