#include <string>
#include <vector>

namespace BitBorn {
class Graphics {
  public:
    Graphics(int screenWidth, int screenHeight, float fieldOfView, float depth);

    void renderFrame(std::vector<float> playerPos, std::vector<int> mapDimensions, std::string map,
                     std::vector<char> validWalls);
    void renderHUD(std::vector<float> playerPos, std::vector<int> mapDimensions, std::string map, float fElapsedTime);
    void renderControls();

    std::vector<int> getScreenDimensions();

  private:
    int nScreenWidth{120};
    int nScreenHeight{40};
    float fFOV{3.14159f / 4.0f};
    float fDepth{16.0f};

    bool showHUD{false};
};
} // namespace BitBorn
