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

void moveCharacter(Character *character, Stack<sf::Vector2f> *movStack)
{
    sf::Vector2f playerPos = character->getPos();
    playerPos = movStack->peek();
    movStack->pop();
    character->move(playerPos);
}

void drawStats(GameWindow *win)
{
    win->draw(win->stats->getCell());

    for (int i = 0; i < 3; i ++)
    {
        for (int j = 0; j < 4; j ++)
        {
            win->draw(win->stats->player1Stats[i][j]);
            win->draw(win->stats->player2Stats[i][j]);
        }
    }

    win->draw(win->stats->player1Text);
    win->draw(win->stats->player2Text);
    win->draw(win->stats->infoText);
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
        for (int i = 0; i < win->world->players[p]->charactersAlive; i++)
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
    win->menu->textbox->drawTo(*win);
}

void processMoveChoice(GameWindow *win, Character *character, sf::Vector2f destination)
{
    Stack<sf::Vector2f> *movStack = win->world->movStack;

    if (movStack->isEmpty())
    {
    	int energyRequired = 0;
        sf::Vector2f characterPos = character->getPos();
        character->setEnergy(character->getEnergy() - energyRequired);
        std::cout << "Energy Consumed: " << energyRequired << std::endl; // test
        win->world->tiles[characterPos.x + 8 * characterPos.y]->setOccupied(false);
        win->world->tiles[destination.x + 8 * destination.y]->setOccupied(true);
        loadMovementsStack(movStack, characterPos, destination, win->world->paths[static_cast<int>(character->getElement()) - 1]);
        movStack->push(characterPos);
    }
    while (!movStack->isEmpty())
    {
        moveCharacter(character, movStack);
        this_thread::sleep_for(chrono::milliseconds(250));
        win->clear();
        drawScreen(win);
        win->display();
    }
}
