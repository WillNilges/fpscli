#include "map.h"
#include "types.h"
#include <algorithm>
#include <curses.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace BitBorn;

Map::Map(std::string mapFilePath, int nMapWidth, int nMapHeight) : nMapWidth(nMapWidth), nMapHeight(nMapHeight) {
    std::ifstream mapFile{mapFilePath};
    if (!mapFile) {
        endwin();
        std::cerr << "Error. Cannot open map file. Does it actually exist?" << std::endl;
    }
    if (nMapWidth != nMapHeight) {
        endwin();
        std::cout << "The world gets a bit funky when nMapWidth != "
                     "nMapHeight. Correct that and try again."
                  << std::endl;
    }
    std::ostringstream sstr;
    sstr << mapFile.rdbuf();
    map = sstr.str();
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
