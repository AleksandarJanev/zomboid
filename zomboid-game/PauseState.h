#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "Core/GameState.h"
#include "Core/Image.h"
#include "Core/Input.h"

#include "Button.h"

class PauseState : public GameState
{
private:
    static const int BUTTON_X = 650;
    static const int BUTTON_Y = 400;
    static const int BUTTON_SPACING = 200;

    Image overlayImage;
    Image continueButtonImage;
    Image exitButtonImage;
    Input* input;
    Button continueButton;
    Button exitButton;
    GameState* runState;
public:
    bool init(Graphics* g, GameState* r, Input* i);
    void free();
    void update();
    void draw(Graphics* g);
};

#endif
