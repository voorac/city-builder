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

    this->map = Map("media/city_map.dat", 64, 64, game->tileAtlas);
    this->zoomLevel = 1.0f;

    sf::Vector2f centre(this->map.width, this->map.height*0.5);
    centre *= float(this->map.tileSize);
    gameView.setCenter(centre);
    this->actionState = ActionState::NONE;
}

void GameStateEditor::draw(const float dt)
{
    this->game->window.clear(sf::Color::Black);
    this->game->window.setView(this->guiView);
    this->game->window.draw(this->game->background);
    this->game->window.setView(this->gameView);
    this->map.draw(this->game->window, dt);
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
        case sf::Event::MouseMoved:
        {
            if (this->actionState == ActionState::PANNING)
            {
                sf::Vector2f pos(sf::Mouse::getPosition(this->game->window) - this->panningAnchor);
                gameView.move(-1.0f * pos * this->zoomLevel);
                panningAnchor = sf::Mouse::getPosition(this->game->window);
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (event.mouseButton.button == sf::Mouse::Middle)
            {
                if (this->actionState != ActionState::PANNING)
                {
                    this->actionState = ActionState::PANNING;
                    this->panningAnchor = sf::Mouse::getPosition(this->game->window);
                }
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if (event.mouseButton.button == sf::Mouse::Middle)
            {
                this->actionState = ActionState::NONE;
            }
            break;
        }
        case sf::Event::MouseWheelMoved:
        {
            if (event.mouseWheel.delta < 0)
            {
                gameView.zoom(2.0f);
                zoomLevel *= 2.0f;
            }
            else
            {
                gameView.zoom(0.5f);
                zoomLevel *= 0.5f;
            }
            break;
        }
        case sf::Event::Closed:
        {
            this->game->window.close();
            break;
        }
        case sf::Event::Resized:
        {
            this->gameView.setSize(event.size.width, event.size.height);
            this->gameView.zoom(zoomLevel);
            this->guiView.setSize(event.size.width, event.size.height);

            this->game->background
                .setPosition(this->game->window
                             .mapPixelToCoords(sf::Vector2i(0, 0),
                                               this->guiView));
            float xFactor = event.size.width /
                static_cast<float>(this->game->background
                                   .getTexture()->getSize().x);
            float yFactor = event.size.height /
                static_cast<float>(this->game->background
                                   .getTexture()->getSize().y);
            
            this->game->background.setScale(xFactor, yFactor);            
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

