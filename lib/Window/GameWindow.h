#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include "../../src/main.h"

class GameWindow : public sf::RenderWindow
{
public:
    GameWorld *world;
    GameStats *stats;
    GameWindow(sf::VideoMode window, string title, GameWorld *worldSegment, GameStats *statsSegment) : sf::RenderWindow(window, title)
    {
        world = worldSegment;
        stats = statsSegment;
        setKeyRepeatEnabled(true);
    };
    ~GameWindow();
};

#endif
