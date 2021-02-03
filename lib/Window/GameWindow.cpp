#include "../../src/main.h"

GameWindow::~GameWindow()
{
    delete world;
    delete stats;
}
