#include "game.hpp"

#include <SFML/Window.hpp>

#include "game_state.hpp"


Game::Game() : window(sf::VideoMode(800, 600), "City Builder") {
    this->loadTextures();
    
    window.setFramerateLimit(60);

    this->background.setTexture(this->textureManager.getRef("background"));
}

Game::~Game() {}

void Game::pushState(std::unique_ptr<GameState> state) {
    states.push(std::move(state));
}

void Game::popState() {
    states.pop();
}

void Game::changeState(std::unique_ptr<GameState> & state) {
    if (!states.empty()) {
        popState();
    }
    pushState(std::move(state));
}

const std::unique_ptr<GameState> & Game::peekState() {
    if (states.empty()) {
        return nullptr;
    }
    return states.top();
}

void Game::gameLoop() {
    sf::Clock clock;

    while(window.isOpen()) {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        if (!peekState()) {
            continue;
        }

        peekState()->handleInput();
        peekState()->update(dt);
        window.clear(sf::Color::Black);
        peekState()->draw(dt);
        window.display();
    }
}


void Game::loadTextures()
{
    textureManager.loadTexture("background", "media/background.png");
}
