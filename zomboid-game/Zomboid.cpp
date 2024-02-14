#include "Zomboid.h"

bool Zomboid::init()
{
    if(!initSystem("Zomboid", SCREEN_WIDTH, SCREEN_HEIGHT, false))
    {
        return false;
    }

    if(!mainMenuState.init(getGraphics(), getInput(), getAudio(), this, &runState))
    {
        return false;
    }

    setFPS(30);

    stateManager.addState(&mainMenuState);

    return true;
}

void Zomboid::free()
{
    mainMenuState.free();
    freeSystem();
}

void Zomboid::update()
{
    stateManager.update();
}

void Zomboid::draw(Graphics* g)
{
    stateManager.draw(g);
}
