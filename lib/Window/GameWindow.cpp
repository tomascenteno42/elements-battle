#include "../../src/main.h"

GameWindow::GameWindow(sf::VideoMode window, string title)
    :sf::RenderWindow(window, title)
{
    world = new GameWorld();
    menu = new GameMenu(0, 400, 400, 800, sf::Color::Red);
    stats = new GameStats(400, 0, 400, 400, sf::Color::White);
    setKeyRepeatEnabled(true);
}

GameWindow::~GameWindow()
{
    delete world;
    delete menu;
    delete stats;
}
