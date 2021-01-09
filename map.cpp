#include "map.h"

using namespace std;
using namespace BitBorn;

string Map::getMap()
{
    return Map::map;
}

std::vector<int> Map::getDimensions()
{
    return { Map::nMapHeight, Map::nMapWidth };
}

std::vector<char> Map::getValidWalls()
{
    return Map::validWalls;
}