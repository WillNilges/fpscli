#pragma once

#include "types.h"
#include <string>
#include <vector>

// Player object
namespace BitBorn {

enum Action { MOVE_FORWARD, MOVE_BACK, MOVE_LEFT, MOVE_RIGHT, LOOK_LEFT, LOOK_RIGHT };

class Player {
  public:
    Player(fCoord25D position) : position(position) {}

    fCoord25D stageMovement(Action stagedAction, float fElapsedTime);
    void look(Action stagedAction, float fElapsedTime);

    fCoord25D getPosition();
    void setPosition(fCoord25D newPosition);

  private:
    // Stuff that will change
    int health{100};
    fCoord25D position{10.0f, 10.0f, 10.0f};

    // Stuff that will probably not change.
    const float fSpeed{25.0f}; // Walking Speed
};
}; // namespace BitBorn
