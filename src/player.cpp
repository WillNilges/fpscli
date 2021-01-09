#include "player.h"
#include <algorithm>
#include <cmath>

using namespace BitBorn;

bool Player::move(int key, std::vector<int> mapDimensions, std::string map, std::vector<char> validWalls, float fElapsedTime) {   
    // Increments of movement, depending on the player's actions.
    float fMovementX = 0.0f;
    float fMovementY = 0.0f;

    switch (key) {
    case 'k':
        // CCW Rotation
        Player::fPlayerA -= (fSpeed * 0.75f) * fElapsedTime;
        break;
    case 'l':
        // CW Rotation
        Player::fPlayerA += (fSpeed * 0.75f) * fElapsedTime;
        break;
    case 'a':
        // Left movement
        fMovementX += sinf(Player::fPlayerA - (0.5 * 3.14159)) * fSpeed * fElapsedTime;
        fMovementY += cosf(Player::fPlayerA - (0.5 * 3.14159)) * fSpeed * fElapsedTime;
        break;
    case 'd':
        // Right movement
        fMovementX += sinf(Player::fPlayerA + (0.5 * 3.14159)) * fSpeed * fElapsedTime;
        fMovementY += cosf(Player::fPlayerA + (0.5 * 3.14159)) * fSpeed * fElapsedTime;
        break;
    case 'w':
        // Forward movement
        fMovementX += sinf(Player::fPlayerA) * fSpeed * fElapsedTime;
        fMovementY += cosf(Player::fPlayerA) * fSpeed * fElapsedTime;
        break;
    case 's':
        // Backward movement
        fMovementX -= sinf(Player::fPlayerA) * fSpeed * fElapsedTime;
        fMovementY -= cosf(Player::fPlayerA) * fSpeed * fElapsedTime;
        break;
    default:
        break;
    }

    if (fMovementX != 0.0f || fMovementY != 0.0f) {
        // What block the player hits, acquired by checking their
        // rounded position with an index in the world array.
        char collisionBlock =
            map.c_str()[(int)(Player::fPlayerX + fMovementX) * mapDimensions[1] + (int)(Player::fPlayerY + fMovementY)];

        // If the block we're about to hit isn't a wall, then allow the player to move.
        if (std::find(validWalls.begin(), validWalls.end(), collisionBlock) != validWalls.end())
            return false;
        Player::fPlayerX += fMovementX;
        Player::fPlayerY += fMovementY;
    }
    return true;
}

std::vector<float> Player::getPos() { return {Player::fPlayerX, Player::fPlayerY, Player::fPlayerA}; }
