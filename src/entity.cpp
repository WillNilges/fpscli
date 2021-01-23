#include "entity.h"
#include <algorithm>
#include <cmath>

using namespace BitBorn;

fCoord25D Entity::stageMovement(Action stagedAction, float fElapsedTime) {
    struct fCoord25D stagedPosition = Entity::position;
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

void Entity::look(Action stagedAction, float fElapsedTime) {
    switch (stagedAction) {
    case LOOK_LEFT:
        // CCW Rotation
        Entity::position.a -= (fSpeed * 0.75f) * fElapsedTime;
        break;
    case LOOK_RIGHT:
        // CW Rotation
        Entity::position.a += (fSpeed * 0.75f) * fElapsedTime;
        break;
    default:
        break;
    }
}

fCoord25D Entity::getPosition() { return Entity::position; }

void Entity::setPosition(fCoord25D newPosition) { Entity::position = newPosition; }
