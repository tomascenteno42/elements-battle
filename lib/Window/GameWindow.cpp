#include "../../src/main.h"

GameWindow::GameWindow(sf::VideoMode window, string title)
    :sf::RenderWindow(window, title)
{
    world = new GameWorld();
    menu = new GameMenu(0, 400, 400, 800, sf::Color(31,34,45), this);
    stats = new GameStats(400, 0, 400, 400, sf::Color(64,68,75), world);
    setKeyRepeatEnabled(true);
}


void GameWindow::setWorld(GameWorld* world)
{
    delete this->world;
    this->world = world;
}


GameWindow::~GameWindow()
{
    delete world;
    delete menu;
    delete stats;
}
