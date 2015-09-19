#ifndef GAME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include <SFML/Graphics.hpp>

#include "game_state.hpp"

class GameStateStart : public GameState
{
private:
    sf::View view;

    void loadGame();

public:
    GameStateStart(std::shared_ptr<Game> game);

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
};


#endif // GAME_STATE_START_HPP
