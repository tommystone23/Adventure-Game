#include "game.h"
#include "utils/logger.h"

int main()
{
    Game *game = new Game();
    if(!game->init()) {
        Logger() << "failed to initialize game";
        return -1;
    }
    game->run();
    return 0;
}