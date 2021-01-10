#include "player.h"
#include <algorithm>
#include <cmath>

using namespace BitBorn;

fCoord25D Player::stageMovement(Action stagedAction, float fElapsedTime) {
    struct fCoord25D stagedPosition = Player::position;
    switch (stagedAction) {
    case MOVE_FORWARD:
        stagedPosition.x += sinf(stagedPosition.a) * fSpeed * fElapsedTime;
        stagedPosition.y += cosf(stagedPosition.a) * fSpeed * fElapsedTime;
        break;
    case MOVE_BACK:
        stagedPosition.x -= sinf(stagedPosition.a) * fSpeed * fElapsedTime;
        stagedPosition.y -= cosf(stagedPosition.a) * fSpeed * fElapsedTime;
        break;
    case MOVE_LEFT:
        // Left movement
        stagedPosition.x += sinf(stagedPosition.a - (0.5 * 3.14159)) * fSpeed * fElapsedTime;
        stagedPosition.y += cosf(stagedPosition.a - (0.5 * 3.14159)) * fSpeed * fElapsedTime;
        break;
    case MOVE_RIGHT:
        // Right movement
        stagedPosition.x += sinf(stagedPosition.a + (0.5 * 3.14159)) * fSpeed * fElapsedTime;
        stagedPosition.y += cosf(stagedPosition.a + (0.5 * 3.14159)) * fSpeed * fElapsedTime;
        break;
    default:
        break;
    }
    return stagedPosition;
}

void Player::look(Action stagedAction, float fElapsedTime) {
    switch (stagedAction) {
    case LOOK_LEFT:
        // CCW Rotation
        Player::position.a -= (fSpeed * 0.75f) * fElapsedTime;
        break;
    case LOOK_RIGHT:
        // CW Rotation
        Player::position.a += (fSpeed * 0.75f) * fElapsedTime;
        break;
    default:
        break;
    }
}

fCoord25D Player::getPosition() { return Player::position; }

void Player::setPosition(fCoord25D newPosition) { Player::position = newPosition; }
