#include "game.hpp"

#include <SFML/Window.hpp>

#include "animation_handler.hpp"
#include "game_state.hpp"


Game::Game() : window(sf::VideoMode(800, 600), "City Builder") {
    this->loadTextures();
    this->loadTiles();

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

    while (window.isOpen()) {
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

void Game::loadTextures() {
    textureManager.loadTexture("background", "media/background.png");
    textureManager.loadTexture("grass", "media/grass.png");
    textureManager.loadTexture("forest", "media/forest.png");
    textureManager.loadTexture("water", "media/water.png");
    textureManager.loadTexture("residential", "media/residential.png");
    textureManager.loadTexture("commercial", "media/commercial.png");
    textureManager.loadTexture("industrial", "media/industrial.png");
    textureManager.loadTexture("road", "media/road.png");
}

void Game::loadTiles() {
    Animation staticAnim(0, 0, 1.0f);
    this->tileAtlas["grass"] =
        Tile(this->tileSize, 1, textureManager.getRef("grass"),
        { staticAnim }, TileType::GRASS, 50, 0, 1);

    tileAtlas["forest"] =
        Tile(this->tileSize, 1, textureManager.getRef("forest"),
        { staticAnim },
            TileType::FOREST, 100, 0, 1);

    tileAtlas["water"] =
        Tile(this->tileSize, 1, textureManager.getRef("water"),
        { Animation(0, 3, 0.5f),
                Animation(0, 3, 0.5f),
                Animation(0, 3, 0.5f) },
            TileType::WATER, 0, 0, 1);

    tileAtlas["residential"] =
        Tile(this->tileSize, 2, textureManager.getRef("residential"),
        { staticAnim, staticAnim, staticAnim,
                staticAnim, staticAnim, staticAnim },
            TileType::RESIDENTIAL, 300, 50, 6);

    tileAtlas["commercial"] =
        Tile(this->tileSize, 2, textureManager.getRef("commercial"),
        { staticAnim, staticAnim, staticAnim, staticAnim },
            TileType::COMMERCIAL, 300, 50, 4);

    tileAtlas["industrial"] =
        Tile(this->tileSize, 2, textureManager.getRef("industrial"),
        { staticAnim, staticAnim, staticAnim,
                staticAnim },
            TileType::INDUSTRIAL, 300, 50, 4);

    tileAtlas["road"] =
        Tile(this->tileSize, 1, textureManager.getRef("road"),
        { staticAnim, staticAnim, staticAnim,
                staticAnim, staticAnim, staticAnim,
                staticAnim, staticAnim, staticAnim,
                staticAnim, staticAnim },
            TileType::ROAD, 100, 0, 1);
}
