#include "map.h"
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

std::vector<int> Map::getDimensions() { return {Map::nMapHeight, Map::nMapWidth}; }

std::vector<char> Map::getValidWalls() { return Map::validWalls; }
