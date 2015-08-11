#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <memory>

#include "game.hpp"


class GameState {
public:
    std::weak_ptr<Game> game;

    virtual void draw(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void handleInput() = 0;
};

#endif // GAME_STATE_HPP
