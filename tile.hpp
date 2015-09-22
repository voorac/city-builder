#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "animation_handler.hpp"

enum class TileType
{
    VOID,
    GRASS,
    FOREST,
    WATER,
    RESIDENTIAL,
    COMMERCIAL,
    INDUSTRIAL,
    ROAD
};

std::string tileTypeToStr(TileType type);
std::string tileTypeToIdStr(TileType type);

class Tile
{
public:
    AnimationHandler animHandler;
    sf::Sprite sprite;
    TileType tileType;
    int tileVariant;
    unsigned int regions[1];
    unsigned int cost;
    double population;
    unsigned int maxPopPerLevel;
    unsigned int maxLevels;
    float production;
    float storedGoods;

    Tile ();
    Tile(const unsigned int tileSize, const unsigned int height,
         sf::Texture& texture, const std::vector<Animation>& animations,
         const TileType tileType, const unsigned int cost,
         const unsigned int maxPopPerLevel, const unsigned int maxLevels);

    void draw(sf::RenderWindow& window, float dt);
    void update();
    std::string getCost();
};
    
#endif // TILE_HPP
