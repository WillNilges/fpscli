#pragma once

#include "types.h"
#include <cmath>
#include <string>
#include <array>
#include <vector>

namespace BitBorn {
class Map {
  public:
    Map(std::string mapFilePath);

    // bool checkValidWall(char mapSpace);
    std::string getMap();
    std::array<int, 2> getDimensions();
    std::vector<char> getValidWalls();
    std::vector<char> getValidIndoors();
    std::vector<nCoord2D> getSpawnLocations();
    fCoord25D getRandomSpawn();

    bool getCollision(fCoord25D coordinates);

  private:
    std::string map;
    std::vector<nCoord2D> spawnLocations;
    int nMapWidth;
    int nMapHeight;

    std::vector<char> validWalls;   
    std::vector<char> validIndoors;
};
} // namespace BitBorn
