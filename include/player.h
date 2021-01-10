#include <string>
#include <vector>
#include "types.h"

// Player object
namespace BitBorn {
class Player {
  public:
    Player(fCoord25D position) : position(position){}

    fCoord25D stageMovement(action stagedAction, float fElapsedTime);
    void look(action stagedAction, float fElapsedTime);
    // bool move(int key, std::vector<int> mapDimensions, std::string map, std::vector<char> validWalls, float fElapsedTime);

    fCoord25D getPosition();
    void setPosition(fCoord25D newPosition);

  private:
    // Stuff that will change
    int health{100};
    fCoord25D position{10.0f, 10.0f, 10.0f};

    // Stuff that will probably not change.
    float fSpeed{150.0f}; // Walking Speed
};
}; // namespace BitBorn
