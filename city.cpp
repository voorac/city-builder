#include "city.hpp"


City::City() : birthRate(0.00055), deathRate(0.00023), propCanWork(0.5),
               populationPool(0), population(0), employmentPool(0),
               employable(0), residentialTax (0.05), commercialTax(0.05),
               industrialTax(0.05), earnings(0), funds(0), currentTime(0.0),
               timePerDay(1.0), day(0)
{}

City::City(std::string cityName, int tileSize, std::map<std::string, Tile>& tileAtlas) : City()
{
    this->map.tileSize = tileSize;
    load(cityName, tileAtlas);
}

void City::load(std::string cityName, std::map<std::string, Tile>& tileAtlas)
{
    
}

void City::save(std::string cityName)
{
    
}

void update(float dt)
{
    
}    

void bulldoze(const Tile& tile)
{

}

void shuffleTiles()
{
    
}

void tileChange()
{
    
}

double City::getUnemployed()
{
    return this->employmentPool;
}

double City::getHomeless()
{
    return this->populationPool;
}
