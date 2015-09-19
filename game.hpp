#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <stack>

#include <SFML/Graphics.hpp>

#include "texture_manager.hpp"


class GameState;

class Game {
private:
    void loadTextures();
    
public:
    std::stack<std::unique_ptr<GameState> > states;
    sf::RenderWindow window;
    TextureManager textureManager;
    sf::Sprite background;

    Game();
    ~Game();

    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> & state);
    const std::unique_ptr<GameState> & peekState();

    void gameLoop();
};

#endif // GAME_HPP
