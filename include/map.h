#include <string>
#include <vector>

namespace BitBorn {
class Map {
  public:
    Map(std::string mapFilePath, int nMapWidth, int nMapHeight);

    // bool checkValidWall(char mapSpace);
    std::string getMap();
    std::vector<int> getDimensions();
    std::vector<char> getValidWalls();

  private:
    std::string map;
    int nMapWidth;
    int nMapHeight;

    std::vector<char> validWalls{'W', 'R', 'G', 'B', 'Y'};
};
} // namespace BitBorn
