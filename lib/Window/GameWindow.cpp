#include "../../src/main.h"

GameWindow::~GameWindow()
{
    delete world;
    delete menu;
    delete stats;
}
