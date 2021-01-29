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
    int costo;
    for (int i = 0; i < 64; i++)
    {
        costo = world->tiles[i]->getCost();
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
                distances[i][j] = costo;
            else
                distances[i][j] = 1000;
        }
    }
}

void printDistances(int distances[64][64])
{
    cout << "[" << endl;
    for (int i = 0; i < 16; i++)
    {
        cout << "[";
        for (int j = 0; j < 16; j++)
        {
            cout << distances[i][j] << ",";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
}

void printPaths(sf::Vector2f paths[64][64])
{
    cout << "[" << endl;
    for (int i = 0; i < 16; i++)
    {
        cout << "[";
        for (int j = 0; j < 16; j++)
        {
            cout << "[" << paths[i][j].x / 50 << "," << paths[i][j].y / 50 << "],";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
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

sf::Vector2f askDestination()
{
    string x, y;
    cout << "Move to x (0-7): ";
    cin >> x;
    cout << "Move to y (0-7): ";
    cin >> y;
    return sf::Vector2f(stof(x), stof(y));
}
