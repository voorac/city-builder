#ifndef GAME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

#include "game_state.hpp"
#include "gui.hpp"


class GameStateStart : public GameState
{
private:
    sf::View view;

    std::map<std::string, Gui> guiSystem;

    void loadGame();

public:
    GameStateStart(std::shared_ptr<Game> game);

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
};


#endif // GAME_STATE_START_HPP
