#include "MainMenuState.h"

bool MainMenuState::init(Graphics* g, Input* i, Audio* a, Game* ga, RunState* r)
{
    graphics = g;
    audio = a;
    input = i;
    game = ga;
    runState = r;

    if(!background.load("graphics/menus/main/MainMenuFinal.bmp", g))
    {
        return false;
    }

    if(!startButtonImage.load("graphics/menus/main/play.bmp", g))
    {
        return false;
    }

    if(!creditsButtonImage.load("graphics/menus/main/Help.bmp", g))
    {
        return false;
    }

    if(!exitButtonImage.load("graphics/menus/main/Exit.bmp", g))
    {
        return false;
    }

    if(!song.load("audio/music/dark.ogg"))
    {
        return false;
    }

    startButton.setImage(&startButtonImage);
    creditsButton.setImage(&creditsButtonImage);
    exitButton.setImage(&exitButtonImage);

    startButton.setPos(650, 250);
    creditsButton.setPos(650, 400);
    exitButton.setPos(650, 600);


    screenWidth = game->getGraphics()->getWidth();
    screenHeight = game->getGraphics()->getHeight();

    return true;
}

void MainMenuState::free()
{
    audio->stopMusic();
    song.free();
    startButtonImage.free();
    creditsButtonImage.free();
    exitButtonImage.free();
    background.free();
    creditsState.free();
}

void MainMenuState::update()
{
    startButton.update(input);
    creditsButton.update(input);
    exitButton.update(input);

    if(!audio->musicPlaying())
    {
        song.play(-1);
    }

    if(startButton.fired())
    {
        if(!runState->init(graphics, input, audio, screenWidth, screenHeight))
        {
            runState->free();
            game->end();
        }

        getManager()->addState(runState);
    }

    if(creditsButton.fired())
    {
        if(!creditsState.init(graphics, input))
        {
            return;
        }
        getManager()->addState(&creditsState);
    }

    if(exitButton.fired())
    {
        game->end();
    }
}

void MainMenuState::draw(Graphics* g)
{
    background.draw(0,0,g);
    startButton.draw(g);
    creditsButton.draw(g);
    exitButton.draw(g);
}
