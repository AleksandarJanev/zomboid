#ifndef ZOMBOID_H
#define ZOMBOID_H

#include "Core/Game.h"
#include "Core/StateManager.h"
#include "MainMenuState.h"
#include "RunState.h"

class Zomboid : public Game
{
private:
    const static int SCREEN_WIDTH = 1600;
    const static int SCREEN_HEIGHT = 900;

    StateManager stateManager;
    MainMenuState mainMenuState;
    RunState runState;
public:
    bool init();
    void free();
    void update();
    void draw(Graphics* g);
};

#endif
