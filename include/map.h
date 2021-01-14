#pragma once

#include "types.h"
#include <array>
#include <string>
#include <vector>

namespace BitBorn {
class Map {
  public:
    Map(std::string mapFilePath);

    // bool checkValidWall(char mapSpace);
    std::string getMap();
    std::array<int, 2> getDimensions();
    std::vector<char> getValidWalls();
    std::vector<nCoord2D> getSpawnLocations();

    bool getCollision(fCoord25D coordinates);

  private:
    std::string map;
    std::vector<nCoord2D> spawnLocations;
    int nMapWidth;
    int nMapHeight;

    std::vector<char> validWalls{'W', 'R', 'G', 'B', 'Y'};
};
} // namespace BitBorn
