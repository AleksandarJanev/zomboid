#include "CreditsState.h"

bool CreditsState::init(Graphics* g, Input* i)
{
    input = i;

    if(!backgroundImage.load("graphics/menus/credits/HelpScreenFinal.bmp", g))
        return false;

    return true;
}

void CreditsState::free()
{
    backgroundImage.free();
}

void CreditsState::update()
{
    //In SDL 2, we need to use SDL_SCANCODE_(KEY) instead of SDLK_(KEY)
    if(input->keyDown(SDL_SCANCODE_SPACE))
    {
        free();
        getManager()->popState();
    }
}

void CreditsState::draw(Graphics* g)
{
    backgroundImage.draw(0,0,g);
}


