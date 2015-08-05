#include "game.hpp"

#include <stack>

#include <SFML/Window.hpp>

#include "game_state.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "City Builder") {
    window.setFramerateLimit(60);
}

Game::~Game() {}

void Game::pushState(GameState* state) {
    states.push(state);
}

void Game::popState() {
    states.pop();
}

void Game::changeState(GameState* state) {
    if (!states.empty()) {
        popState();
    }
    pushState(state);
}

GameState* Game::peekState() {
    if (states.empty()) {
        return NULL;
    }
    return states.top();
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
