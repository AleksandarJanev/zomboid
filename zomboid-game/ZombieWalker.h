#ifndef ZOMBIEWALKER_H
#define ZOMBIEWALKER_H

#include "Core/Rectangle.h"
#include "Core/MapNode.h"
#include "Core/SceneNode.h"
#include "Core/Image.h"
#include "Core/Sprite.h"

#include "EntityDef.h"
#include "EntityFactory.h"

class EntityFactory;

class ZombieWalker : public SceneNode
{
private:
    static const int ENTITY_WIDTH = 240;
    static const int ENTITY_HEIGHT = 240;
    static const int ACCEL = 2;
    static const int MAX_VEL = 2;
    static const int NUM_FRAMES = 24;

    int counterR = 13;
    int counterL = 12;

    EntityFactory* factory;
    Sprite sprite;
    Image* image;
    Rectangle* camera;
    Map* map;

    int yVel;
    int xVel;
    int oldY;
    int startX;
    int startY;
    int health;
public:
    ZombieWalker(Image* image,Map* m, Rectangle* c, EntityFactory* f, int x, int y);
    ~ZombieWalker();
    void update();
    void draw(Rectangle* view, Graphics* g);
    void damage(int d);
};

#endif // ZOMBIEWALKER_H

