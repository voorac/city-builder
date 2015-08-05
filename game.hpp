#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
#include <SFML/Graphics.hpp>

class GameState;

class Game {
public:
    std::stack<GameState*> states;
    sf::RenderWindow window;

    Game();
    ~Game();

    void pushState(GameState* state);
    void popState();
    void changeState(GameState* state);
    GameState* peekState();

    void gameLoop();
};

#endif // GAME_HPP
