#ifndef CITY_HPP
#define CITY_HPP

#include <map>
#include <vector>

#include "map.hpp"


class City
{
private:
    float currentTime;
    float timePerDay;

    std::vector<int> shuffledTiles;

    double populationPool;
    double employmentPool;
    float propCanWork;

    double birthRate;
    double deathRate;

    double distributePool(double& pool, Tile& tile, double rate);

public:
    Map map;
    double population;
    double employable;
    double residentialTax;
    double commercialTax;
    double industrialTax;

    double earnings;
    double funds;

    int day;

    City();
    City(std::string cityName, int tileSize, std::map<std::string, Tile>& tileAtlas);

    void load(std::string cityName, std::map<std::string, Tile>& tileAtlas);
    void save(std::string cityName);

    void update(float dt);
    void bulldoze(const Tile& tile);
    void shuffleTiles();
    void tileChanged();

    double getHomeless();
    double getUnemployed();
};

#endif // CITY_HPP
