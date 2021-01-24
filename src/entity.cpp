#include "entity.h"
#include <algorithm>
#include <cmath>

using namespace BitBorn;

Entity::Entity(bool controlled, fCoord25D position) : bIsControlled(controlled), position(position) {}

Entity::Entity(bool controlled, fCoord25D position, int maxHP) : bIsControlled(controlled), position(position), nMaxHealth(maxHP) {}

// MOVEMENT FUNCTIONS

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

fCoord25D Entity::getPosition() { return Entity::position; }
void Entity::setPosition(fCoord25D newPosition) { Entity::position = newPosition; }

// HEALTH FUNCTIONS

int Entity::getCurrentHealth() { return Entity::nHealth; }
int Entity::getMaxHealth() { return Entity::nMaxHealth; }

void Entity::heal(int amt) {
    Entity::nHealth += amt;
    if (nHealth > nMaxHealth)
        nHealth = nMaxHealth;
}

void Entity::harm(int amt) {
    Entity::nHealth -= amt;
    if (nHealth < 0)
        nHealth = 0;
}

bool Entity::isDead() {
    if (Entity::nHealth <= 0) 
        return true;
    return false;
}