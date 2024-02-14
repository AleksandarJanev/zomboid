
#include "ZombieWalker.h"

ZombieWalker::ZombieWalker(Image* i,Map* m, Rectangle* c, EntityFactory* f, int x, int y) :
    SceneNode(ENTITY_ENEMY, x-ENTITY_WIDTH/2, y-ENTITY_HEIGHT/2, ENTITY_WIDTH, ENTITY_HEIGHT)
{
        sprite.setImage(i);
        image = i;

        camera = c;
        factory = f;
        //cycle = 0;

        yVel = 0;
        xVel =5 ;


        //unsigned tick = SDL_GetTicks();
        //unsigned tick2 = SDL_GetTicks();

        startY = y;
        startX = x;
        health = 5;
        map=m;
}

ZombieWalker::~ZombieWalker()
{

}

void ZombieWalker::update()
{

    if(health <= 0)
    {
        remove();
        return;
    }

        setY(660);

        //update();
        if(xVel > 0) //Moving Right
        {
            bool edge = !map->checkSolid((getX2()+1)/map->getTileWidth(), (getY2()+1)/map->getTileHeight());
            bool wall = map->checkSolid((getX2()+1)/map->getTileWidth(), (getY2())/map->getTileHeight());
            if(edge || wall)
            {
                xVel*=-1;
                sprite.setFrame(7);
            }
        }

        if(xVel < 0)
        {
            bool edge = !map->checkSolid((getX()-1)/map->getTileWidth(), (getY2()+1)/map->getTileHeight());
            bool wall = map->checkSolid((getX()-1)/map->getTileWidth(), (getY2())/map->getTileHeight());

            if(edge || wall)
            {
                xVel*=-1;
                sprite.setFrame(2);
            }
        }





    //setY(getY() + yVel);
    setX(getX()+xVel);

    std::list<SceneNode*>* nodes = getScene()->getNodes();

        for(list<SceneNode*>::iterator it = nodes->begin(); it != nodes->end(); it++)
        {
            if((*it)->getID() == ENTITY_PLAYER && overlaps(**it))
            {
                PlayerEntity* player = (PlayerEntity*)(*it);

                player->damage(50);
                getScene()->addNode(factory->makeEntity(ENTITY_EXPLOSION, getCenterX(), getCenterY()));
                remove();
            }
        }

}


void ZombieWalker::damage(int d)
{
    health -= d;
}

void ZombieWalker::draw(Rectangle* view, Graphics* g)
{
    if(image != NULL)
        {

            if(xVel > 0)
            {
                if(counterR > 12 && counterR < 23)
                {
                    image->draw(getCenterX() - getWidth()/2 - view->getX(), getCenterY() - getHeight()/2 - view->getY(), counterR, g);
                    ++counterR;
                }else
                {

                    image->draw(getCenterX() - getWidth()/2 - view->getX(), getCenterY() - getHeight()/2 - view->getY(), 12, g);
                    counterR = 13;
                }
            }
            else if(xVel < 0)
            {

               if(counterL < 11  && counterL >0)
                {
                    image->draw(getCenterX() - getWidth()/2 - view->getX(), getCenterY() - getHeight()/2 - view->getY(), counterL, g);
                    --counterL;
                }else
                {
                    counterL = 10;
                    image->draw(getCenterX() - getWidth()/2 - view->getX(), getCenterY() - getHeight()/2 - view->getY(), 11, g);
                }
            }

        }
    /*if(xVel > 0)
    {
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
    }*/

}
