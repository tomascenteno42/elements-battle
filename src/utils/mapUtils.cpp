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

sf::Vector2f askDestination()
{
    string x, y;
    cout << "Move to x (0-7): ";
    cin >> x;
    cout << "Move to y (0-7): ";
    cin >> y;
    return sf::Vector2f(stof(x), stof(y));
}

void validateDestination(GameWorld *world, Character *character, sf::Vector2f &destination)
{
    int energyRequired = world->distances
                             [static_cast<int>(character->getElement()) - 1]
                             [int(character->getPos().x + 8 * character->getPos().y)]
                             [int(destination.x + 8 * destination.y)];

    if (destination.x < 0 || destination.x > 7 || destination.y < 0 || destination.y > 7)
        std::cout << "Invalid destination" << std::endl;
    else if (world->tiles[destination.x + 8 * destination.y]->isOccupied())
        std::cout << "You can't move there, the cell is occupied" << std::endl;
    else if (energyRequired > character->getEnergy())
        std::cout << "You can't move there, you lack energy" << std::endl;
    else
        return;

    destination = askDestination();
    validateDestination(world, character, destination);
}

void drawScreen(GameWindow *win)
{
    for (size_t i = 0; i < win->world->tiles.size(); i++)
    {
        win->draw(win->world->tiles[i]->getCell());
    }
    for (int i = 0; i < 1; i++)
    {
        win->draw(win->world->player1Characters[i]->getCell());
        win->draw(win->world->player2Characters[i]->getCell());
    }

    win->draw(win->stats->getCell());
    win->draw(win->menu->getCell());
    win->menu->textbox->drawTo(*win);
}

void renderMap(sf::RenderWindow &win)
{
}

void processMoveChoice(Stack<sf::Vector2f> *movStack, GameWindow *win, Character *character)
{
    if (movStack->isEmpty())
    {
        sf::Vector2f characterPos = character->getPos();
        sf::Vector2f destination = askDestination();
        validateDestination(win->world, character, destination);
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
