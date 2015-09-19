#include <iostream>

#include "game.hpp"
#include "game_state_start.hpp"


int main(int argc, char** argv) {
    auto game = std::make_shared<Game>();
    game->pushState(std::make_unique<GameStateStart>(game));
    game->gameLoop();
    return 0;
}
