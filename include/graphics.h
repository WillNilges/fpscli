#pragma once

#include "types.h"
#include <array>
#include <string>
#include <vector>

namespace BitBorn {
class Graphics {
  public:
    Graphics(int screenWidth, int screenHeight, float fieldOfView, float depth);

    void renderFrame(fCoord25D playerPos, std::array<int, 2> mapDimensions, std::string map,
                     std::vector<char> validWalls, std::vector<char> validIndoors);
    void renderHUD(fCoord25D playerPos, std::array<int, 2> mapDimensions, std::string map, float fElapsedTime);
    void renderControls();

    ~Graphics();

  private:
    const short BRIGHTEST = 0x2588;
    const short BRIGHTER = 0x2593;
    const short DIM = 0x2592;
    const short DARKER = 0x2591;
    const short DARKEST = 0x2591;

    enum ColorPallete {
        WHITE,
        RED,
        GREEN,
        BLUE,
        YELLOW,
        MAGENTA,
        CYAN,
        BLACK,
        SKY,
        TRUE_SKY,
        SPAWN
    };

    int terminalWidth;
    int terminalHeight;

    int nScreenWidth{120};
    int nScreenHeight{40};
    float fFOV{3.14159f / 4.0f};
    float fDepth{32.0f};

    bool showHUD{false};

    ColorPallete determineColor(char input, bool isWall);
    
};
} // namespace BitBorn
