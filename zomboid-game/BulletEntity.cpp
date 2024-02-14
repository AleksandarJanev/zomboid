#include "BulletEntity.h"

BulletEntity::BulletEntity(Image* i, Sound* s, Map* m, Rectangle* c, EntityFactory* f, int x, int y, bool enemy) :
    MapNode(ENTITY_BULLET, x - ENTITY_WIDTH/2,
            y - ENTITY_HEIGHT/2,
            ENTITY_WIDTH, ENTITY_HEIGHT, true, m)
{
    image = i;
    sound = s;
    enemyBullet = enemy;
    factory = f;
    camera = c;
    s->play();
}

BulletEntity::~BulletEntity()
{

}

void BulletEntity::update()
{
    int moveX = SPEED;

    if(enemyBullet)
    {
        moveX*=-1;
        moveX/=2;
    }

    setX(getX()+moveX);

    if(overlapsMap())
    {
        remove();
        getScene()->addNode(factory->makeEntity(ENTITY_EXPLOSION, getX(), getY()));
        return;
    }

    //if(!camera->overlaps(*this))
      //  remove();

     if(!enemyBullet)
    {
        std::list<SceneNode*>* nodes = getScene()->getNodes();

        for(list<SceneNode*>::iterator it = nodes->begin(); it != nodes->end(); it++)
        {
            if((*it)->getID() == ENTITY_ENEMY && overlaps(**it))
            {
                ZombieWalker* zombie = (ZombieWalker*)(*it);

                zombie->damage(5);

                getScene()->addNode(factory->makeEntity(ENTITY_EXPLOSION, getX(), getY()));
                remove();
            }


        }
    }
    else
    {
        std::list<SceneNode*>* nodes = getScene()->getNodes();

        /*for(list<SceneNode*>::iterator it = nodes->begin(); it != nodes->end(); it++)
        {
            if((*it)->getID() == ENTITY_PLAYER && overlaps(**it))
            {
                //PlayerEntity* player = (PlayerEntity*)(*it);

                //player->damage(5);
                remove();
            }
        }*/
        for(list<SceneNode*>::iterator it = nodes->begin(); it != nodes->end(); it++)
        {
            if((*it)->getID() == ENTITY_ENEMY && overlaps(**it))
            {
                ZombieWalker* zombie = (ZombieWalker*)(*it);

                zombie->damage(10);

                getScene()->addNode(factory->makeEntity(ENTITY_EXPLOSION, getX(), getY()));
                remove();
            }


        }
    }
}

void BulletEntity::draw(Rectangle* view, Graphics* g)
{
    int x = getCenterX() - image->getFrameWidth()/2;
    int y = getCenterY() - image->getFrameHeight()/2;
    int frame;

    if(enemyBullet)
        frame = ENEMY_BULLET_FRAME;
    else
        frame = PLAYER_BULLET_FRAME;

    image->draw(x-view->getX(), y-view->getY(), frame, g);
}
