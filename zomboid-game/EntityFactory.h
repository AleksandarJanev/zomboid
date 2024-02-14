#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H


#include "Core/Image.h"
#include "Core/Rectangle.h"
#include "Core/SceneNode.h"
#include "Core/Sound.h"

#include "EntityDef.h"

#include "ZombieWalker.h"
#include "BulletEntity.h"
#include "ExplosionEntity.h"
#include "PlayerEntity.h"

class ExplosionEntity;
class PlayerEntity;

class EntityFactory
{
private:
    Rectangle* camera;

    Image zombie1;
    Image zombie2;
    Image zombie3;
    Image zombie4;

    Image bulletImage;
    Image checkpointImage;
    Image explosionImage;
    Image explosionSmallImage;
    Image playerImage;
    Map* map;
    Sound explosionSound;
    Sound bulletSound;
public:
    EntityFactory();
    ~EntityFactory();
    bool init(Graphics* g);
    void free();
    Image* pickZombieSkin(int i);
    void setCamera(Rectangle* c);
    void setMap(Map* m);
    SceneNode* makeEntity(int e, int x, int y);
};

#endif
