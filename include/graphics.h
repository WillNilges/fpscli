#include <string>
#include <vector>
#include "types.h"

namespace BitBorn {
class Graphics {
  public:
    Graphics(int screenWidth, int screenHeight, float fieldOfView, float depth);

    void renderFrame(fCoord25D playerPos, std::vector<int> mapDimensions, std::string map,
                     std::vector<char> validWalls);
    void renderHUD(fCoord25D playerPos, std::vector<int> mapDimensions, std::string map, float fElapsedTime);
    void renderControls();

    ~Graphics();

  private:
    int terminalWidth;
    int terminalHeight;

    int nScreenWidth{120};
    int nScreenHeight{40};
    float fFOV{3.14159f / 4.0f};
    float fDepth{16.0f};

    bool showHUD{false};
};
} // namespace BitBorn
