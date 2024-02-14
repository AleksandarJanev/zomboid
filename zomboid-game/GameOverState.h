#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "Core/GameState.h"
#include "Core/Image.h"
#include "Core/Input.h"

#include "Button.h"

class GameOverState : public GameState
{
private:
    static const int BUTTON_X = 300;
    static const int BUTTON_Y = 100;

    Image overlayImage;
    Image mainMenuButtonImage;
    Input* input;
    Button mainMenuButton;
    GameState* runState;
public:
    bool init(Graphics* g, GameState* r, Input* i);
    void free();
    void update();
    void draw(Graphics* g);
};

#endif
