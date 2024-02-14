#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "Core/Game.h"
#include "Core/GameState.h"
#include "Core/Graphics.h"
#include "Core/Image.h"
#include "Core/Input.h"
#include "Core/Music.h"

#include "Button.h"
#include "RunState.h"
#include "CreditsState.h"

class MainMenuState : public GameState
{
private:
    const static int BUTTON_X = 100;
    const static int BUTTON_Y = 400;
    const static int BUTTON_SPACING = 75;

    int screenWidth;
    int screenHeight;

    Button startButton;
    Button creditsButton;
    Button exitButton;
    Game* game;
    Image background;
    Image startButtonImage;
    Image creditsButtonImage;
    Image exitButtonImage;
    Music song;
    Graphics* graphics;
    Audio* audio;
    Input* input;
    RunState* runState;
    CreditsState creditsState;
public:
    bool init(Graphics* g, Input* i, Audio* a, Game* ga, RunState* r);
    void free();
    void update();
    void draw(Graphics* g);
};

#endif
