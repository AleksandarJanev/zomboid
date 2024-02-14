#ifndef PLAYERNODE_H
#define PLAYERNODE_H

#include "Core/Rectangle.h"
#include "Core/MapNode.h"
#include "Core/Sprite.h"

#include "EntityDef.h"
#include "EntityFactory.h"

class EntityFactory;

class PlayerEntity : public MapNode
{
private:
    static const int ENTITY_WIDTH = 240;
    static const int ENTITY_HEIGHT = 240;
    static const int ACCEL = 3;
    static const int GUN_COOLDOWN_TIME = 30;
    static const int MAX_VEL = 3;
    static const int NUM_FRAMES = 12;

    bool playerJump = false;

    EntityFactory* factory;
    Sprite sprite;
    Rectangle* camera;

    bool right;

    unsigned int tick;
    unsigned int tick2;

    int counterR = 7;
    int counterL = 6;
    int xVel;
    int yVel;
    int oldY;
    int startX;
    int startY;
    int health;
    int gunCooldown;
public:
    PlayerEntity(Image* image, Map* m, Rectangle* c, int x, int y, EntityFactory* f);
    ~PlayerEntity();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void shoot();
    void respawn();
    void setSpawn(int x, int y);
    int getSpawnX();

    void damage(int d);
    int getHealth();

    void update();
    void draw(Rectangle* view, Graphics* g);
};

#endif
