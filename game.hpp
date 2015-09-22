#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <memory>
#include <stack>
#include <string>

#include <SFML/Graphics.hpp>

#include "texture_manager.hpp"
#include "tile.hpp"
#include "gui.hpp"


class GameState;

class Game {
private:
    void loadTextures();
    void loadTiles();
    void loadStylesheets();
    void loadFonts();

public:
    const static int tileSize = 8;

    std::stack<std::unique_ptr<GameState> > states;
    sf::RenderWindow window;
    TextureManager textureManager;
    sf::Sprite background;
    std::map<std::string, Tile> tileAtlas;
    std::map<std::string, GuiStyle> stylesheets;
    std::map<std::string, sf::Font> fonts;

    Game();
    ~Game();

    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> & state);
    const std::unique_ptr<GameState> & peekState();

    void gameLoop();
};

#endif // GAME_HPP
