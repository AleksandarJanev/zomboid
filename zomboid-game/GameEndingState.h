#ifndef GAMEENDINGSTATE_H
#define GAMEENDINGSTATE_H

#include "Core/GameState.h"
#include "Core/Image.h"
#include "Core/Input.h"

#include "Button.h"

class GameEndingState : public GameState
{
private:
    static const int BUTTON_X = 650;
    static const int BUTTON_Y = 700;

    Image backgroundImage;
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

