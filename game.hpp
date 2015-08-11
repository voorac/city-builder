#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <stack>

#include <SFML/Graphics.hpp>

class GameState;

class Game {
public:
    std::stack<std::unique_ptr<GameState>> states;
    sf::RenderWindow window;

    Game();
    ~Game();

    void pushState(std::unique_ptr<GameState> & state);
    void popState();
    void changeState(std::unique_ptr<GameState> & state);
    std::unique_ptr<GameState> peekState();

    void gameLoop();
};

#endif // GAME_HPP
