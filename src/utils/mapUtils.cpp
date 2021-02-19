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
    GameCell *node;
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
        {
            for (int k = 0; k < 64; k++)
            {
                distances[i][j][k] = distances_aux[j][k];
                paths[i][j][k] = paths_aux[j][k];
            }
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

void drawStats(GameWindow* win)
{
    win->draw(win->stats->getCell());
/*
    for (int i = 0; i < 20; i ++)
    {
        win->draw(win->stats->characterList[i]);
    }
*/
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
    for (size_t i = 0; i < win->world->tiles->getVertices(); i++)
    {
        win->draw(win->world->tiles->getData(i+1)->data->getCell());
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
    
    if(win->stats->showCharacterList){
        for (size_t i = 0; i < CHARACTERS_LIMIT; i++)
            win->draw(win->stats->characterList[i]);
    }

    if(win->stats->showCharacterDetails){
        for (size_t i = 0; i < 5; i++)
            win->draw(win->stats->characterDetails[i]);
    }

    if(win->stats->showChosenChar){
        for (size_t i = 0; i < 8; i++)
            win->draw(win->stats->chosenCharacters[i]);
    }

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
