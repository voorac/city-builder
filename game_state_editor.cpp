#include "game_state_editor.hpp"

#include <SFML/Graphics.hpp>

#include "game_state.hpp"


GameStateEditor::GameStateEditor(std::shared_ptr<Game> game)
{
    this->game = game;
    sf::Vector2f pos = static_cast<sf::Vector2f>(this->game->window.getSize());
    this->guiView.setSize(pos);
    this->gameView.setSize(pos);
    pos = pos * 0.5f;
    this->guiView.setCenter(pos);
    this->gameView.setCenter(pos);
}

void GameStateEditor::draw(const float dt)
{
    this->game->window.clear(sf::Color::Black);
//    this->game->window.draw(this->game->background);
}

void GameStateEditor::update(const float dt)
{
}

void GameStateEditor::handleInput()
{
    sf::Event event;

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
            this->gameView.setSize(event.size.width, event.size.height);
            this->guiView.setSize(event.size.width, event.size.height);
            
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

