#include "RunState.h"

bool RunState::init(Graphics* g, Input* i, Audio* a, int width, int height)
{
    camera.set(0, 0, width, height);

    if(!loadFiles(g))
        return false;

    if(!gameEndingState.init(g, this, i))
        return false;

    if(!gameOverState.init(g, this,i))
        return false;

    if(!pauseState.init(g, this, i))
        return false;

    if(!player.init(g))
        return false;

    if(!factory.init(g))
        return false;

    factory.setCamera(&camera);
    player.setCamera(&camera);

    graphics = g;
    input = i;
    audio = a;

    if(!initLevel())
        return false;

    song.play(-1);

    return true;
}

void RunState::free()
{
    audio->stopMusic();
    freeFiles();
    gameEndingState.free();
    gameOverState.free();
    level.free();
    pauseState.free();
}

bool RunState::loadFiles(Graphics* g)
{
    if(!background1.load("graphics/backgrounds/stars1.bmp", g))
    {
        return false;
    }

    if(!background2.load("graphics/backgrounds/stars2.bmp", g))
    {
        return false;
    }

    if(!background3.load("graphics/backgrounds/Background900.bmp", g))
    {
        return false;
    }

    if(!song.load("audio/music/mystery.ogg"))
    {
        return false;
    }

    return true;
}

void RunState::freeFiles()
{
    background1.free();
    background2.free();
    background3.free();
    song.free();
}

void RunState::drawBackground(Graphics* g)
{
    background3.draw(0-(camera.getX()/2),0, g);

    //background3.draw(0,0,g);
    //background3.draw(0-(camera.getX()/8)%g->getWidth() + g->getWidth(), camera.getY(), g);

    //background2.draw(0-(camera.getX()/4)%g->getWidth(), camera.getY(), g);
    //background2.draw(0-(camera.getX()/4)%g->getWidth() + g->getWidth(), camera.getY(), g);

    //background1.draw(0-(camera.getX()/2)%g->getWidth(), camera.getY(), g);
    //background1.draw(0-(camera.getX()/2)%g->getWidth() + g->getWidth(), camera.getY(), g);
}

bool RunState::initLevel()
{
    if(!level.load("levels/level1.txt", graphics, &factory))
    {
        return false;
    }

    PlayerEntity* playerEntity = (PlayerEntity*)factory.makeEntity(ENTITY_PLAYER, level.getSpawnX(), level.getSpawnY());

    level.getScene()->addNode(playerEntity);
    player.setEntity(playerEntity);

    return true;
}

void RunState::update()
{
    if((player.getCenterX()-700) <0)
    {
        camera.setX(0);
        //camera.setX2(0);
    }
    else if((player.getCenterX()-700) > 8800)
    {
         camera.setX(8800);
         //camera.setX2(8800);
    }
    else
    {
        camera.setX(player.getCenterX()-700);
        //camera.setX2(player.getCenterX()-444);
    }

    //if(camera.getX2() >= level.getMap()->getTotalWidth())
        //camera.setX2(level.getMap()->getTotalWidth());
    //else
        //player.scroll(10);


    player.update(input, &level);
    level.update();


    //In SDL 2, we need to use SDL_SCANCODE_(KEY) instead of SDLK_(KEY)
    if(input->keyHit(SDL_SCANCODE_ESCAPE))
    {
        getManager()->addState(&pauseState);
    }

    if(player.getLives() <= 0)
    {
        getManager()->addState(&gameOverState);
    }

    if(input->keyHit(SDL_SCANCODE_P) || player.getCenterX() > 8500)
    {
        getManager()->addState(&gameEndingState);
    }
}

void RunState::draw(Graphics* g)
{
    g->clear(0, 0, 0);

    drawBackground(g);
    level.draw(&camera, g);
    player.draw(g);
}
