#include "player.h"
#include <algorithm>
#include <cmath>

using namespace BitBorn;

fCoord25D Player::stageMovement(action stagedAction, float fElapsedTime) {
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
        case LOOK_LEFT:
            // CCW Rotation
            stagedPosition.a -= (fSpeed * 0.75f) * fElapsedTime;
            break;
        case LOOK_RIGHT:
            // CW Rotation
            stagedPosition.a += (fSpeed * 0.75f) * fElapsedTime;
            break;
    }
    return stagedPosition;
}

void Player::look(action stagedAction, float fElapsedTime) {
    switch (stagedAction) {
        case LOOK_LEFT:
            // CCW Rotation
            Player::position.a -= (fSpeed * 0.75f) * fElapsedTime;
            break;
        case LOOK_RIGHT:
            // CW Rotation
            Player::position.a += (fSpeed * 0.75f) * fElapsedTime;
            break;
    }
}

// bool Player::move(int key, std::vector<int> mapDimensions, std::string map, std::vector<char> validWalls, float fElapsedTime) {   
//     // Increments of movement, depending on the player's actions.
//     float fMovementX = 0.0f;
//     float fMovementY = 0.0f;

//     switch (key) {
//     case 'k':
//         // CCW Rotation
//         Player::position.a -= (fSpeed * 0.75f) * fElapsedTime;
//         break;
//     case 'l':
//         // CW Rotation
//         Player::position.a += (fSpeed * 0.75f) * fElapsedTime;
//         break;
//     case 'a':
//         // Left movement
//         fMovementX += sinf(Player::position.a - (0.5 * 3.14159)) * fSpeed * fElapsedTime;
//         fMovementY += cosf(Player::position.a - (0.5 * 3.14159)) * fSpeed * fElapsedTime;
//         break;
//     case 'd':
//         // Right movement
//         fMovementX += sinf(Player::position.a + (0.5 * 3.14159)) * fSpeed * fElapsedTime;
//         fMovementY += cosf(Player::position.a + (0.5 * 3.14159)) * fSpeed * fElapsedTime;
//         break;
//     case 'w':
//         // Forward movement
//         fMovementX += sinf(Player::position.a) * fSpeed * fElapsedTime;
//         fMovementY += cosf(Player::position.a) * fSpeed * fElapsedTime;
//         break;
//     case 's':
//         // Backward movement
//         fMovementX -= sinf(Player::position.a) * fSpeed * fElapsedTime;
//         fMovementY -= cosf(Player::position.a) * fSpeed * fElapsedTime;
//         break;
//     default:
//         break;
//     }

//     if (fMovementX != 0.0f || fMovementY != 0.0f) {
//         // What block the player hits, acquired by checking their
//         // rounded position with an index in the world array.
//         char collisionBlock =
//             map.c_str()[(int)(Player::fPlayerX + fMovementX) * mapDimensions[1] + (int)(Player::fPlayerY + fMovementY)];

//         // If the block we're about to hit isn't a wall, then allow the player to move.
//         if (std::find(validWalls.begin(), validWalls.end(), collisionBlock) != validWalls.end())
//             return false;
//         Player::fPlayerX += fMovementX;
//         Player::fPlayerY += fMovementY;
//     }
//     return true;
// }

fCoord25D Player::getPosition() { return Player::position; }

void Player::setPosition(fCoord25D newPosition) { Player::position = newPosition; }
