#include "EntityFactory.h"

EntityFactory::EntityFactory()
{

}

EntityFactory::~EntityFactory()
{

}

bool EntityFactory::init(Graphics* g)
{

    if(!zombie1.load("graphics/sprites/Zombie1.1.bmp",240,240,g))
    {
        return false;
    }

     if(!zombie2.load("graphics/sprites/Zombie1.2.bmp",240,240,g))
    {
        return false;
    }

     if(!zombie3.load("graphics/sprites/Zombie1.3.bmp",240,240,g))
    {
        return false;
    }
      if(!zombie4.load("graphics/sprites/Zombie1.4.bmp",240,240,g))
    {
        return false;
    }


    if(!bulletImage.load("graphics/sprites/bullets.bmp", 25, 25, g))
    {
        return false;
    }



    if(!explosionImage.load("graphics/sprites/explosion.bmp", 50, 50, g))
    {
        return false;
    }

    if(!explosionSmallImage.load("graphics/sprites/explosion_small.bmp", 24, 24, g))
    {
        return false;
    }

    if(!playerImage.load("graphics/sprites/playerWalkingBig.bmp", 240, 240, g))
    {
        return false;
    }

    if(!explosionSound.load("audio/sfx/explosion.wav"))
    {
        return false;
    }

    if(!bulletSound.load("audio/sfx/gun.wav"))
    {
        return false;
    }

    return true;
}

Image* EntityFactory::pickZombieSkin(int i)
{
    switch(i)
    {
    case 0:
        return &zombie1;
        break;
    case 1:
        return &zombie2;
        break;
    case 2:
        return &zombie3;
        break;
    case 3:
        return &zombie4;
        break;
    default:
        break;
    }

}

void EntityFactory::free()
{
    zombie1.free();
    zombie2.free();
    zombie3.free();
    zombie4.free();

    bulletImage.free();
    explosionImage.free();
    explosionSmallImage.free();
    playerImage.free();
    explosionSound.free();
    bulletSound.free();
}

void EntityFactory::setCamera(Rectangle* c)
{
    camera = c;
}
void EntityFactory::setMap(Map* m)
{
    map = m;
}

SceneNode* EntityFactory::makeEntity(int e, int x, int y)
{
    switch(e)
    {
        case ENTITY_PLAYER:
            return new PlayerEntity(&playerImage, map, camera, x, y, this);
            break;
        case ENTITY_EXPLOSION:
            return new ExplosionEntity(&explosionImage, &explosionSound, x, y);
            break;
        case ENTITY_SILENT_EXPLOSION:
            return new ExplosionEntity(&explosionImage, NULL, x, y);
            break;
        case ENTITY_SMALL_EXPLOSION:
            return new ExplosionEntity(&explosionSmallImage, NULL, x, y);
            break;
        case ENTITY_PLAYER_BULLET:
            return new BulletEntity(&bulletImage, &bulletSound, map, camera, this, x, y, false);
            break;
        case ENTITY_ENEMY_BULLET:
            return new BulletEntity(&bulletImage, &bulletSound, map, camera, this, x, y, true);
            break;
        case ENTITY_ZOMBIE:
            return new ZombieWalker(pickZombieSkin(rand()%4),map, camera, this, x, y);

            break;
        default:
            return NULL;
    }
}
