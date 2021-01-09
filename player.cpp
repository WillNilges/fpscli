#include "player.h"

using namespace std;
using namespace BitBorn;

bool Player::move(int key, string map, float fElapsedTime) {   
    char validWalls[5] = { 'W', 'R', 'G', 'B', 'Y' }; // Valid, collidable walls.
   
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
            fMovementX += sinf(Player::fPlayerA-(0.5*3.14159)) * fSpeed * fElapsedTime;;
            fMovementY += cosf(Player::fPlayerA-(0.5*3.14159)) * fSpeed * fElapsedTime;;
            break;
        case 'd':
            // Right movement
            fMovementX += sinf(Player::fPlayerA+(0.5*3.14159)) * fSpeed * fElapsedTime;;
            fMovementY += cosf(Player::fPlayerA+(0.5*3.14159)) * fSpeed * fElapsedTime;;
            break;
        case 'w':
            // Forward movement
            fMovementX += sinf(Player::fPlayerA) * fSpeed * fElapsedTime;;
            fMovementY += cosf(Player::fPlayerA) * fSpeed * fElapsedTime;;
            break;
        case 's':
            // Backward movement
            fMovementX -= sinf(Player::fPlayerA) * fSpeed * fElapsedTime;;
            fMovementY -= cosf(Player::fPlayerA) * fSpeed * fElapsedTime;;
            break;
        default:
            break;
    }

    if (fMovementX != 0.0f || fMovementY != 0.0f)
    {
        // What block the player hits, acquired by checking their
        // rounded position with an index in the world array.
        char collisionBlock = map.c_str()[
            (int) (Player::fPlayerX+fMovementX) * nMapWidth + (int) (Player::fPlayerY+fMovementY)
        ];
        
        // The char in the world array that the player hit (could be empty)
        char *wallCollision = std::find(std::begin(validWalls), std::end(validWalls), collisionBlock); 
        
        // If the block we're about to hit isn't a wall, then allow the player to move.
        if (wallCollision == std::end(validWalls))
        {
            Player::fPlayerX += fMovementX;
            Player::fPlayerY += fMovementY;
        }
    }
}

std::vector<float> Player::getPos() {
    return { Player::fPlayerX, Player::fPlayerY, Player::fPlayerA };
}