#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(Image* image, Map* m, Rectangle* c, int x, int y, EntityFactory* f) :
    MapNode(ENTITY_PLAYER, x - ENTITY_WIDTH/2,
            y - ENTITY_HEIGHT/2,
            ENTITY_WIDTH, ENTITY_HEIGHT, true, m)
{
    sprite.setImage(image);

    camera = c;
    factory = f;
    xVel = yVel = 0;
    gunCooldown = 0;
    health = 100;
    startX = x;
    startY = y;
    right = true;
    playerJump = false;

    unsigned tick = SDL_GetTicks();
    unsigned tick2 = SDL_GetTicks();
    oldY = getY();
}

PlayerEntity::~PlayerEntity()
{

}

void PlayerEntity::moveUp()
{
    if(tick2+1100 < SDL_GetTicks())
    {

          playerJump = true;

        tick2 = SDL_GetTicks();
    }
}

void PlayerEntity::moveDown()
{
    //move(0,yVel+=ACCEL);
}

void PlayerEntity::moveLeft()
{
    move(xVel-=ACCEL,0);
}

void PlayerEntity::moveRight()
{
   move(xVel+=ACCEL,0);
}

void PlayerEntity::respawn()
{
    setX(startX);
    setY(startY);
    xVel = 0;
    yVel = 0;
    sprite.setFrame(7);
    health = 100;
}

void PlayerEntity::setSpawn(int x, int y)
{
    startX = x;
    startY = y;
}

int PlayerEntity::getSpawnX()
{
    return startX;
}

void PlayerEntity::update()
{
    gunCooldown--;

    if(playerJump)
    {
        yVel = -200;


        //oldY = getY();
        move(xVel,yVel);
        playerJump = false;
    }else if(getY() == oldY)
    {
        yVel = 1;
        sprite.update();


        oldY = getY();
        move(xVel,yVel);

    }
    else
    {
        yVel++;

        oldY = getY();
        move(1, yVel+4);
    }

    if(xVel > MAX_VEL)
        xVel = MAX_VEL;

    if(xVel < -MAX_VEL)
        xVel = -MAX_VEL;

    //if(yVel > MAX_VEL)
    //    yVel = MAX_VEL;

    if(yVel < -MAX_VEL)
        yVel = -MAX_VEL;

    if(yVel > 0)
        yVel--;

    if(yVel < 0)
        yVel++;

    if(xVel > 0)
        xVel--;

    if(xVel < 0)
        xVel++;

    int middleFrame = NUM_FRAMES/2;

    if(xVel == 0 && right)
    {
       sprite.setFrame(6);
       //sprite.update();
    }else if(xVel == 0 && !right)
    {
       sprite.setFrame(5);
       //sprite.update();
    }
    else if(xVel > 0)
    {
        right = true;
        //sprite.setFrame(middleFrame + 1 + middleFrame*((float)xVel/MAX_VEL));

        if( tick+150 < SDL_GetTicks())
        {

            if(counterR < 12)
            {
                sprite.setFrame(counterR);
                ++counterR;
            }
            else
            {
                sprite.setFrame(7);
                counterR = 8;
            }
            tick = SDL_GetTicks();
        }
    }
    else if(xVel < 0)
    {
        right = false;
        if( tick+150 < SDL_GetTicks())
        {

            if(counterL > 1 && counterL < 6)
            {
                sprite.setFrame(counterL);
                --counterL;
            }
            else
            {
                sprite.setFrame(5);
                counterL = 4;
            }
            tick = SDL_GetTicks();
        }
    }

    sprite.update();

    setY(getY() + yVel);
    setX(getX() + xVel);

    /*if(getY() <= camera->getY())
        setY(camera->getY());

    if(getX() <= camera->getX())
        setX(camera->getX());

    if(getY2() >= camera->getY2())
        setY2(camera->getY2());

    if(getX2() >= camera->getX2())
        setX2(camera->getX2());
    */

    /*if(overlapsMap())
    {
        //getScene()->addNode(factory->makeEntity(ENTITY_EXPLOSION, getX() + rand()%getWidth(), getY() + rand()%getHeight()));

        for(int i = 0; i < 10; i++)
            getScene()->addNode(factory->makeEntity(ENTITY_SILENT_EXPLOSION, getX() + rand()%getWidth(), getY() + rand()%getHeight()));

        //health = 0;
    }

    if(overlapsMap())
    {
       //health = 0;
    }*/

    if(health < 30)
        getScene()->addNode(factory->makeEntity(ENTITY_SMALL_EXPLOSION, getX() + rand()%getWidth(), getY() + rand()%getHeight()));
}

void PlayerEntity::damage(int d)
{
    health -= d;

    if(health < 0)
        health = 0;

    for(int i = 0; i < 5; i++)
        getScene()->addNode(factory->makeEntity(ENTITY_SMALL_EXPLOSION, getX() + rand()%getWidth(), getY() + rand()%getHeight()));
}

int PlayerEntity::getHealth()
{
    return health;
}

void PlayerEntity::shoot()
{
    if(gunCooldown <= 0 && right)
    {
        getScene()->addNode(factory->makeEntity(ENTITY_PLAYER_BULLET, getX2(), getCenterY()-40));
        gunCooldown = GUN_COOLDOWN_TIME;
    }else if(gunCooldown <= 0 && !right)
    {
        getScene()->addNode(factory->makeEntity(ENTITY_ENEMY_BULLET, getX2()-240, getCenterY()-40));
        gunCooldown = GUN_COOLDOWN_TIME;
    }
}

void PlayerEntity::draw(Rectangle* view, Graphics* g)
{
    if(health <= 0)
        return;

    sprite.draw(getCenterX() - sprite.getWidth()/2 - view->getX(), getCenterY() - sprite.getHeight()/2 - view->getY(), g);
}
