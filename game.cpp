#include "game.hpp"

#include <stack>

#include <SFML/Window.hpp>

#include "game_state.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "City Builder") {
    window.setFramerateLimit(60);
}

Game::~Game() {}

void Game::pushState(std::unique_ptr<GameState> & state) {
    states.push(std::move(state));
}

void Game::popState() {
    states.pop();
}

void Game::changeState(std::unique_ptr<GameState> & state) {
    if (!states.empty()) {
        popState();
    }
    pushState(state);
}

std::unique_ptr<GameState> Game::peekState() {
    if (states.empty()) {
        return NULL;
    }
    return std::move(states.top());
}

void Game::gameLoop() {
    sf::Clock clock;

    while(window.isOpen()) {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        if (peekState() == NULL) {
            continue;
        }

        peekState()->handleInput();
        peekState()->update(dt);
        window.clear(sf::Color::Black);
        peekState()->draw(dt);
        window.display();
    }
}