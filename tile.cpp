#include "tile.hpp"

std::string tileTypeToStr(TileType type)
{
    switch (type)
    {
    default:
    case TileType::VOID: return "Void";
    case TileType::GRASS: return "Grass";
    case TileType::FOREST: return "Forest";
    case TileType::WATER: return "Water";
    case TileType::RESIDENTIAL: return "Residential zone";
    case TileType::COMMERCIAL: return "Commercial zone";
    case TileType::INDUSTRIAL: return "Industrial zone";
    }
}

Tile::Tile ()
{
}

Tile::Tile(const unsigned int tileSize, const unsigned int height,
           sf::Texture& texture, const std::vector<Animation>& animations,
           const TileType tileType, const unsigned int cost,
           const unsigned int maxPopPerLevel, const unsigned int maxLevels)
    : tileType(tileType), tileVariant(0), cost(cost), population(0.0),
      maxPopPerLevel(maxPopPerLevel), maxLevels(maxLevels),
      production(0.0f), storedGoods(0.0f)
{
    this->regions[0] = 0;
    this->sprite.setOrigin(sf::Vector2f(0.0f, tileSize*(height-1)));
    this->sprite.setTexture(texture);
    this->animHandler.frameSize = sf::IntRect(0, 0, tileSize*2, tileSize*height);
    for (auto animation: animations)
    {
        this->animHandler.addAnim(animation);
    }
    this->animHandler.update(0.0f);
}

void Tile::draw(sf::RenderWindow& window, float dt)
{
    this->animHandler.changeAnim(this->tileVariant);
    this->animHandler.update(dt);
    this->sprite.setTextureRect(this->animHandler.bounds);
    window.draw(this->sprite);
}

void Tile::update()
{    
    if ((tileType == TileType::RESIDENTIAL ||
         tileType == TileType::COMMERCIAL ||
         tileType == TileType::INDUSTRIAL) &&
        population == maxPopPerLevel * (tileVariant + 1) &&
        tileVariant < maxLevels)
    {
        if (rand() % int(1e4) < 1e2 / (tileVariant + 1))
        {
            this->tileVariant++;
        }
    }
}

std::string Tile::getCost()
{
    return std::to_string(this->cost);
}
