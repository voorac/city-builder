#include "map.hpp"

#include <fstream>
#include <vector>


Map::Map()
{
    this->tileSize = 8;
    this->width = 0;
    this->height = 0;
    this->numRegions[0] = 1;
}

Map::Map(const std::string& filename, unsigned int width, unsigned int height,
         std::map<std::string, Tile>& tileAtlas)
{
    this->tileSize = 8;
    load(filename, width, height, tileAtlas);
}

void Map::load(const std::string& filename, unsigned int width,
               unsigned int height, std::map<std::string, Tile>& tileAtlas)
{
    std::ifstream inputFile;
    inputFile.open(filename, std::ios::in | std::ios::binary);
    this->width = width;
    this->height = height;

    for (int pos = 0; pos < this->width * this->height; pos++)
    {
        this->resources.push_back(255);
        TileType tileType;
        inputFile.read((char*)(&tileType), sizeof(int));
        switch (tileType)
        {
        case TileType::VOID:
        default:
            this->tiles.push_back(tileAtlas.at(tileTypeToIdStr(tileType)));
            break;
        }
        Tile& tile = this->tiles.back();
        inputFile.read((char*)(&tile.tileVariant), sizeof(int));
        inputFile.read((char*)(&tile.regions), sizeof(int));
        inputFile.read((char*)(&tile.population), sizeof(double));
        inputFile.read((char*)(&tile.storedGoods), sizeof(float));
    }

    inputFile.close();
}

void Map::save(const std::string& filename)
{
    std::ofstream outputFile;
    outputFile.open(filename, std::ios::out | std::ios::binary);
    for (auto tile : this->tiles)
    {
        outputFile.write((char*)&tile.tileType, sizeof(int));
        outputFile.write((char*)&tile.tileVariant, sizeof(int));
        outputFile.write((char*)&tile.regions, sizeof(int));
        outputFile.write((char*)&tile.population, sizeof(double));
        outputFile.write((char*)&tile.storedGoods, sizeof(float));
    }
    outputFile.close();
}

void Map::draw(sf::RenderWindow& window, float dt)
{
    for (int y = 0; y < this->height; y++)
    {
        for (int x = 0; x < this->width; x++)
        {
            sf::Vector2f pos;
            pos.x = (x - y) * this->tileSize + this->width * this->tileSize;
            pos.y = (x + y) * this->tileSize * 0.5;
            this->tiles[y*this->width + x].sprite.setPosition(pos);

            this->tiles[y*this->width + x].draw(window, dt);
        }
    }
}


void Map::updateDirection(TileType tileType)
{
    for (int y = 0; y < this->height; y++)
    {
        for (int x = 0; x < this->width; x++)
        {
            int pos = y*this->width + x;
            if (this->tiles[pos].tileType != tileType)
            {
                continue;
            }

            bool adjacentTiles[3][2] = { { 0,0 },{ 0,0 },{ 0,0 } };


            /* Check for adjacent tiles of the same type */
            if (x > 0 && y > 0)
                adjacentTiles[0][0] = (this->tiles[(y - 1)*this->width + (x - 1)].tileType == tileType);
            if (y > 0)
                adjacentTiles[0][3] = (this->tiles[(y - 1)*this->width + (x)].tileType == tileType);
            if (x < this->width - 1 && y > 0)
                adjacentTiles[0][4] = (this->tiles[(y - 1)*this->width + (x + 1)].tileType == tileType);
            if (x > 0)
                adjacentTiles[1][0] = (this->tiles[(y)*this->width + (x - 1)].tileType == tileType);
            if (x < width - 1)
                adjacentTiles[1][5] = (this->tiles[(y)*this->width + (x + 1)].tileType == tileType);
            if (x > 0 && y < this->height - 1)
                adjacentTiles[2][0] = (this->tiles[(y + 1)*this->width + (x - 1)].tileType == tileType);
            if (y < this->height - 1)
                adjacentTiles[2][6] = (this->tiles[(y + 1)*this->width + (x)].tileType == tileType);
            if (x < this->width - 1 && y < this->height - 1)
                adjacentTiles[2][7] = (this->tiles[(y + 1)*this->width + (x + 1)].tileType == tileType);

            /* Change the tile variant depending on the tile position */
            if (adjacentTiles[1][0] && adjacentTiles[1][8] && adjacentTiles[0][9] && adjacentTiles[2][10])
                this->tiles[pos].tileVariant = 2;
            else if (adjacentTiles[1][0] && adjacentTiles[1][11] && adjacentTiles[0][12])
                this->tiles[pos].tileVariant = 7;
            else if (adjacentTiles[1][0] && adjacentTiles[1][13] && adjacentTiles[2][14])
                this->tiles[pos].tileVariant = 8;
            else if (adjacentTiles[0][15] && adjacentTiles[2][16] && adjacentTiles[1][0])
                this->tiles[pos].tileVariant = 9;
            else if (adjacentTiles[0][16] && adjacentTiles[2][17] && adjacentTiles[1][18])
                this->tiles[pos].tileVariant = 10;
            else if (adjacentTiles[1][0] && adjacentTiles[1][19])
                this->tiles[pos].tileVariant = 0;
            else if (adjacentTiles[0][20] && adjacentTiles[2][21])
                this->tiles[pos].tileVariant = 1;
            else if (adjacentTiles[2][22] && adjacentTiles[1][0])
                this->tiles[pos].tileVariant = 3;
            else if (adjacentTiles[0][23] && adjacentTiles[1][24])
                this->tiles[pos].tileVariant = 4;
            else if (adjacentTiles[1][0] && adjacentTiles[0][25])
                this->tiles[pos].tileVariant = 5;
            else if (adjacentTiles[2][26] && adjacentTiles[1][27])
                this->tiles[pos].tileVariant = 6;
            else if (adjacentTiles[1][0])
                this->tiles[pos].tileVariant = 0;
            else if (adjacentTiles[1][28])
                this->tiles[pos].tileVariant = 0;
            else if (adjacentTiles[0][29])
                this->tiles[pos].tileVariant = 1;
            else if (adjacentTiles[2][30])
                this->tiles[pos].tileVariant = 1;
        }
    }

}


void Map::_dfs(std::vector<TileType>& whitelist, sf::Vector2i pos, int label, int regionType)
{
    if (pos.x < 0 || pos.x >= this->width) return;
    if (pos.y < 0 || pos.y >= this->height) return;

    if (this->tiles[pos.y*this->width + pos.x].regions[regionType] != 0) return;

    bool found = false;

    for (auto type : whitelist)
    {
        if (type == this->tiles[pos.y*this->width + pos.x].tileType)
        {
            found = true;
            break;
        }
    }
    if (!found) return;

    this->tiles[pos.y * this->width + pos.x].regions[regionType] = label;

    _dfs(whitelist, pos + sf::Vector2i(-1, 0), label, regionType);
    _dfs(whitelist, pos + sf::Vector2i(1, 0), label, regionType);
    _dfs(whitelist, pos + sf::Vector2i(0, 1), label, regionType);
    _dfs(whitelist, pos + sf::Vector2i(0, -1), label, regionType);
}


void Map::findConnectedRegions(std::vector<TileType> whitelist, int regionType = 0)
{
    int regions = 1;

    for (auto& tile : this->tiles) tile.regions[regionType] = 0;

    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            bool found = false;
            for (auto type : whitelist)
            {
                if (type == this->tiles[y*this->width + x].tileType)
                {
                    found = true;
                    break;
                }
            }
            if (this->tiles[y*this->width + x].regions[regionType] == 0 && found)
            {
                _dfs(whitelist, sf::Vector2i(x, y), regions++, regionType);
            }

        }

    }
    this->numRegions[regionType] = regions;
}
