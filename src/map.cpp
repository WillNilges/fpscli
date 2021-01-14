#include "map.h"
#include "types.h"
#include <algorithm>
#include <curses.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace BitBorn;

Map::Map(std::string mapFilePath/*, int nMapWidth, int nMapHeight*/) : nMapWidth(nMapWidth), nMapHeight(nMapHeight) {
    std::ifstream mapFile{mapFilePath};
    if (!mapFile) {
        endwin();
        std::cerr << "Error. Cannot open map file. Does it actually exist?" << std::endl;
    }
    std::ostringstream sRawMap;
    sRawMap << mapFile.rdbuf();
    map = sRawMap.str();

    // Work out the width and height of the map
    nMapWidth = nMapHeight = 0;
    nMapWidth = map.find('\n'); // The value of i during the first '\n' we find tells us the width.
    for (std::string::size_type i = 0; i < map.size(); i++) {
        if (map[i] == '\n') {
            int iterator = ((int) i)-nMapHeight;
            if (iterator % nMapWidth != 0)
                std::cout << "Map width is wrong. (" << iterator << ") vs (" << nMapWidth << ") ";
            nMapHeight++; // Increment the map height for each row in the file
        }
    }

    map.erase(std::remove(map.begin(), map.end(), '\n'), map.end());
}

std::string Map::getMap() { return Map::map; }

std::array<int, 2> Map::getDimensions() { return {Map::nMapHeight, Map::nMapWidth}; }

std::vector<char> Map::getValidWalls() { return Map::validWalls; }

bool Map::getCollision(fCoord25D coordinates) {
    char collisionBlock = map.c_str()[(int)(coordinates.x) * Map::nMapWidth + (int)(coordinates.y)];

    // If the block we're about to hit isn't a wall, then allow the player to move.
    if (std::find(validWalls.begin(), validWalls.end(), collisionBlock) != validWalls.end())
        return false;
    return true;
}
