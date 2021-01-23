#include "map.h"
#include "types.h"
#include <algorithm>
#include <curses.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <libconfig.h++>

using namespace BitBorn;

Map::Map(std::string mapDirPath) : nMapWidth(nMapWidth), nMapHeight(nMapHeight) {
    
    // Read the map config
    libconfig::Config cfg;

    std::string config = "walls.cfg";
    std::string walls = "walls.dat";
    

    const char* cfgPath   = (mapDirPath + "/" + config).c_str();
    const char* wallsPath = (mapDirPath + "/" + walls).c_str();

    try {
        std::cout << cfgPath << "\n";
        cfg.readFile(cfgPath);
    }
    catch(const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
    }
    catch(const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                << " - " << pex.getError() << std::endl;
    }

    // Grab tile data from the config files
    std::cout << "Looking up root";
    const libconfig::Setting& root = cfg.getRoot();
    std::cout << "Looking up valid walls";
    const libconfig::Setting &configValidWalls = root.lookup("valid_walls");
    for (int i = 0; i < configValidWalls.getLength(); ++i) {
        validWalls.push_back(configValidWalls[i].c_str()[0]);
    }
    
    std::cout << "Looking up valid indoors";
    const libconfig::Setting &configValidIndoors = root.lookup("valid_indoors");
    for (int i = 0; i < configValidIndoors.getLength(); ++i) {
        validIndoors.push_back(configValidIndoors[i].c_str()[0]);
    }

    // Read the map layout
    std::ifstream mapFile{wallsPath};
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
        int iterator = ((int) i)-nMapHeight;
        switch (map[i]) {
        case '\n':
            if (iterator % nMapWidth != 0)
                std::cout << "Map width is wrong. (" << iterator << ") vs (" << nMapWidth << ") \n";
            nMapHeight++; // Increment the map height for each row in the file
            break;
        case '*':
            // If, during our parsing, we encounter an asterisk, then we know that's a spawn point we should keep note of
            std::cout << "Spawn at (" << (iterator % nMapWidth) << ", " << nMapHeight << ") \n";
            spawnLocations.push_back({nMapHeight, (iterator % nMapWidth)}); // Remember that ncurses coords are reversed and so are the coords for this whole game™, so the height is first, and the width is second.
            break;
        }
    }
    map.erase(std::remove(map.begin(), map.end(), '\n'), map.end());
}

std::string Map::getMap()                      { return Map::map; }

std::array<int, 2> Map::getDimensions()        { return {Map::nMapHeight, Map::nMapWidth}; }

std::vector<char> Map::getValidWalls()         { return Map::validWalls; }

std::vector<char> Map::getValidIndoors()         { return Map::validIndoors; }

std::vector<nCoord2D> Map::getSpawnLocations() { return Map::spawnLocations; }

fCoord25D Map::getRandomSpawn() {
    int actualSpawn = rand() % Map::spawnLocations.size();
    float fSpawnX = (float) Map::spawnLocations.at(actualSpawn).x;
    float fSpawnY = (float) Map::spawnLocations.at(actualSpawn).y;
    return { fSpawnX, fSpawnY, 1.0f };
    
}

bool Map::getCollision(fCoord25D coordinates) {
    char collisionBlock = map.c_str()[(int)(coordinates.x) * Map::nMapWidth + (int)(coordinates.y)];

    // If the block we're about to hit isn't a wall, then allow the player to move.
    if (std::find(validWalls.begin(), validWalls.end(), collisionBlock) != validWalls.end())
        return false;
    return true;
}
