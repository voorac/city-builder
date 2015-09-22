#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>

#include "tile.hpp"

class Map
{
private:
    void _dfs(std::vector<TileType>& whiteList, sf::Vector2i pos, int label, int type);

public:
    unsigned int width;
    unsigned int height;
    std::vector<Tile> tiles;
    std::vector<int> resources;
    unsigned int tileSize;
    unsigned int numSelected;
    unsigned int numRegions[1];

    Map();
    Map(const std::string& filename, unsigned int width, unsigned int height,
        std::map<std::string, Tile>& tileAtlas);

    void load(const std::string& filename, unsigned int width,
        unsigned int height, std::map<std::string, Tile>& tileAtlas);
    void save(const std::string& filename);
    void draw(sf::RenderWindow& window, float dt);
    void findConnectedRegions(std::vector<TileType> whitelist, int type);
    void updateDirection(TileType tileType);
};

#endif // MAP_HPP