#include "GameOverState.h"

bool GameOverState::init(Graphics* g, GameState* r, Input* i)
{
    runState = r;
    input = i;

    if(!mainMenuButtonImage.load("graphics/menus/gameover/menu.bmp", g))
        return false;

    if(!overlayImage.load("graphics/menus/gameover/GameOver.bmp", g))
        return false;

    mainMenuButton.setPos(650, 600);
    mainMenuButton.setImage(&mainMenuButtonImage);

    return true;
}

void GameOverState::free()
{
    mainMenuButtonImage.free();
    overlayImage.free();
}

void GameOverState::update()
{
    mainMenuButton.update(input);

    if(mainMenuButton.fired())
    {
        runState->free();
        getManager()->popState();
        getManager()->popState();
    }
}

void GameOverState::draw(Graphics* g)
{
    runState->draw(g);
    overlayImage.draw(350,50,g);
    mainMenuButton.draw(g);
}

