#include "game.h"

int main(int, char**)
{
    auto& game{ Game::instance() };
    game.init("Ghost Escape", 1280, 720);
    game.run();
    game.clean();

    return 0;
}
