#include "game_state_start.hpp"

#include <memory>
#include <SFML/Graphics.hpp>
#include <utility>

#include "game_state_editor.hpp"
#include "game_state.hpp"


GameStateStart::GameStateStart(std::shared_ptr<Game> game)
{
    this->game = game;
    sf::Vector2f pos = static_cast<sf::Vector2f>(this->game->window.getSize());
    this->view.setSize(pos);
    pos = pos * 0.5f;
    this->view.setCenter(pos);

    this->guiSystem.emplace("menu", Gui(sf::Vector2f(192.0f, 32.0f), 
        4, false, game->stylesheets.at("button"), { std::make_pair("Load Game", "load_game") }));
    this->guiSystem.at("menu").setPosition(pos);
    this->guiSystem.at("menu").setOrigin(96, 32 * 1 / 2);
    this->guiSystem.at("menu").show();
}



void GameStateStart::draw(const float dt)
{
    this->game->window.setView(this->view);
    this->game->window.clear(sf::Color::Black);
    this->game->window.draw(this->game->background);
    for (auto gui : this->guiSystem) this->game->window.draw(gui.second);
}

void GameStateStart::update(const float dt)
{}

void GameStateStart::handleInput()
{
    sf::Event event;

    sf::Vector2f mousePos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->view);
    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                this->game->window.close();
                break;
            }
            case sf::Event::Resized:
            {
                this->view.setSize(event.size.width, event.size.height);
                this->game->background
                    .setPosition(this->game->window
                        .mapPixelToCoords(sf::Vector2i(0, 0),
                            this->view));

                sf::Vector2f pos = sf::Vector2f(event.size.width, event.size.height);
                pos *= 0.5f;
                pos = this->game->window.mapPixelToCoords(sf::Vector2i(pos), this->view);
                this->guiSystem.at("menu").setPosition(pos);
                float xFactor = event.size.width /
                    static_cast<float>(this->game->background
                        .getTexture()->getSize().x);
                float yFactor = event.size.height /
                    static_cast<float>(this->game->background
                        .getTexture()->getSize().y);

                this->game->background.setScale(xFactor, yFactor);
                break;
            }
            case sf::Event::MouseMoved:
            {
                this->guiSystem.at("menu").highlight(this->guiSystem.at("menu").getEntry(mousePos));
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::string msg = this->guiSystem.at("menu").activate(mousePos);
                    if (msg == "load_game")
                    {
                        this->loadGame();
                    }
                    break;
                }
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    this->game->window.close();
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    this->loadGame();
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
}


void GameStateStart::loadGame()
{
    this->game->pushState(std::make_unique<GameStateEditor>(this->game));
}
