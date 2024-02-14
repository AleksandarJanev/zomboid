#ifndef BULLETENTITY_H
#define BULLETENTITY_H

#include "Core/Image.h"
#include "Core/MapNode.h"

#include "EntityDef.h"
#include "EntityFactory.h"

class EntityFactory;

class BulletEntity : public MapNode
{
private:
    static const int ENTITY_WIDTH = 20;
    static const int ENTITY_HEIGHT = 20;
    static const int PLAYER_BULLET_FRAME = 0;
    static const int ENEMY_BULLET_FRAME = 1;
    static const int SPEED = 30;

    bool enemyBullet;
    EntityFactory* factory;
    Image* image;
    Rectangle* camera;
    Sound* sound;
public:
    BulletEntity(Image* i, Sound* s, Map* m, Rectangle* c, EntityFactory* f, int x, int y, bool enemy);
    ~BulletEntity();
    void update();
    void draw(Rectangle* view, Graphics* g);
};

#endif

