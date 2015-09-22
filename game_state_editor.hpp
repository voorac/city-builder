#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>

#include "game_state.hpp"
#include "map.hpp"

enum class ActionState { NONE, PANNING, SELECTING };

class GameStateEditor : public GameState
{
private:
    sf::View gameView;
    sf::View guiView;
    ActionState actionState;
    Map map;

    float zoomLevel;
    sf::Vector2i panningAnchor;


    sf::Vector2i selectionStart;
    sf::Vector2i selectionEnd;
    Tile currentTile;

public:
    GameStateEditor(std::shared_ptr<Game> game);

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
};


#endif // GAME_STATE_EDITOR_HPP
