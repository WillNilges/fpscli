#include "main.hpp"

using namespace std;
namespace BitBorn {
    class Map{
        // Map(std::vector<char> validWalls, string map):
        //     map(map), validWalls(validWalls) {}

        public:
            Map(string mapFilePath, int nMapWidth, int nMapHeight)
                : nMapWidth(nMapWidth), nMapHeight(nMapHeight)
            {
                std::ifstream mapFile{ mapFilePath };
                if (!mapFile) 
                {
                    endwin();
                    std::cerr << "Error. Cannot open map file. Does it actually exist?" << endl;
                }
                if (nMapWidth != nMapHeight) {
                    endwin();
                    std::cout << "The world gets a bit funky when nMapWidth != nMapHeight. Correct that and try again." << endl;
                }
                std::ostringstream sstr;
                sstr << mapFile.rdbuf();
                map = sstr.str();
                map.erase(std::remove(map.begin(), map.end(), '\n'), map.end());
            }

            // bool checkValidWall(char mapSpace);
            string getMap();
            std::vector<int> getDimensions();
            std::vector<char> getValidWalls();

        private:
            string map;
            int nMapWidth;
            int nMapHeight;

            std::vector<char> validWalls{ 'W', 'R', 'G', 'B', 'Y' };
    };
}