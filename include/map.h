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

// {'O', 'R', 'G', 'Y', 'B', 'M', 'C', 'W'}
// {'o', 'r', 'g', 'y', 'b', 'm', 'c', 'w'}

    std::vector<char> validWalls;   //{ 'O', 'R', 'G', 'Y', 'B', 'M', 'C', 'W' };
    std::vector<char> validIndoors; //{ 'o', 'r', 'b', 'm', 'c' };
    // std::vector<char> validOutdoors { 'g', 'w', 'y' };
};
} // namespace BitBorn
