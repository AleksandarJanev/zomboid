#include "Player.h"

bool Player::init(Graphics* g)
{
    entity = NULL;
    camera = NULL;
    deathDelay = 0;
    lives = 3;

    if(!lifeCounterImage.load("graphics/sprites/health.bmp", g))
    {
        return false;
    }

    return true;
}

void Player::free()
{
    lifeCounterImage.free();
}

void Player::setEntity(PlayerEntity* n)
{
    entity = n;
}

void Player::setCamera(Rectangle* r)
{
    camera = r;
}

void Player::update(Input* i, Level* l)
{
    if(entity != NULL)
    {
        //In SDL 2, we need to use SDL_SCANCODE_(KEY) instead of SDLK_(KEY)
        if(i->keyDown(SDL_SCANCODE_W))
        {
            entity->moveUp();
        }

        if(i->keyDown(SDL_SCANCODE_S))
        {
            entity->moveDown();
        }

        if(i->keyDown(SDL_SCANCODE_A))
        {
            entity->moveLeft();
        }

        if(i->keyDown(SDL_SCANCODE_D))
        {
            entity->moveRight();
        }

        if(i->keyDown(SDL_SCANCODE_SPACE))
        {
            entity->shoot();
        }

        if(entity->getHealth() <= 0)
        {
            if(deathDelay == 0)
            {
                lives--;
            }

            deathDelay++;

            if(deathDelay >= 60)
            {
                deathDelay = 0;
                entity->respawn();
                camera->setCenterX(entity->getSpawnX());
                l->reset();
            }
        }
    }
}

void Player::draw(Graphics* g)
{
    int barWidth = entity->getHealth()*3;

    for(int i = 0; i < barWidth; i++)
    {
        int colorMod = ((float)i/LIFEBAR_WIDTH)*255;
        g->drawRect(LIFEBAR_X+i, LIFEBAR_Y, 1, LIFEBAR_HEIGHT, 255-colorMod, colorMod, 0);
    }

    g->drawRect(LIFEBAR_X, LIFEBAR_Y, LIFEBAR_WIDTH, LIFEBAR_HEIGHT, 255, 255, 255);
    g->drawRect(LIFEBAR_X-1,LIFEBAR_Y-1,LIFEBAR_WIDTH+2, LIFEBAR_HEIGHT+2, 0, 0, 0);

    for(int i = 0; i < lives; i++)
    {
        lifeCounterImage.draw(LIVES_PANEL_X+LIVES_SPACING*i, LIVES_PANEL_Y, g);
    }
}

void Player::scroll(int x)
{
    if(entity != NULL)
    {
        entity->setX(entity->getX() + x);
    }
}


int Player::getCenterX()
{
    return entity->getX();
}

int Player::getLives()
{
    return lives;
}
