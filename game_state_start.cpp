#include "game_state_start.hpp"

#include <memory>
#include <SFML/Graphics.hpp>

#include "game_state_editor.hpp"
#include "game_state.hpp"


GameStateStart::GameStateStart(std::shared_ptr<Game> game)
{
    this->game = game;
    sf::Vector2f pos = static_cast<sf::Vector2f>(this->game->window.getSize());
    this->view.setSize(pos);
    pos = pos * 0.5f;
    this->view.setCenter(pos);
}



void GameStateStart::draw(const float dt)
{
    this->game->window.setView(this->view);
    this->game->window.clear(sf::Color::Black);
    //this->game->window.draw(this->game->background);
}

void GameStateStart::update(const float dt)
{
}

void GameStateStart::handleInput()
{
    sf::Event event;
    while(this->game->window.pollEvent(event)) {
        switch(event.type) {
        case sf::Event::Closed:
        {
            this->game->window.close();
            break;
        }
        case sf::Event::Resized:
        {
            this->view.setSize(event.size.width, event.size.height);
            break;
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
