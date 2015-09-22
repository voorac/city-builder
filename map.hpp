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
    unsigned int numSelected;
    std::vector<char> selected;
    unsigned int width;
    unsigned int height;
    std::vector<Tile> tiles;
    std::vector<int> resources;
    unsigned int tileSize;
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

    // Selection methods
    void select(sf::Vector2i start, sf::Vector2i end, std::vector<TileType> blacklist);
    void clearSelected();
};

#endif // MAP_HPP
