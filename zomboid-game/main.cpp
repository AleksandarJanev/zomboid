#include "Zomboid.h"

int main(int argc, char *argv[])
{
    Zomboid game;

    if(!game.init())
    {
        game.free();
        return 0;
    }

    game.run();

    return 0;
}
