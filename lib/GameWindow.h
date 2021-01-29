#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include "../src/main.h"

class GameWindow : public sf::RenderWindow
{

public:
    sf::RenderWindow *gameWindow;
    GameWorld *world;
    GameMenu *menu;
    GameStats *stats;
    GameWindow(sf::VideoMode window, string title, GameWorld *worldSegment, GameMenu *menuSegment, GameStats *statsSegment);
    ~GameWindow();
};

#endif