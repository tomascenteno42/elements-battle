#include "../src/main.h"

GameWindow::GameWindow(sf::VideoMode window, string title, GameWorld *worldSegment, GameMenu *menuSegment, GameStats *statsSegment)
{
    gameWindow = new sf::RenderWindow(window, title);
    world = worldSegment;
    menu = menuSegment;
    stats = statsSegment;
};

GameWindow::~GameWindow()
{
    delete gameWindow;
    delete world;
    delete menu;
    delete stats;
}
