#include "graphics.h"
#include "map.h"
#include "player.h"
#include "types.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <ncurses.h>
#include <vector>
#include <array>

using namespace BitBorn;

bool finished = false;
bool showHUD = false;

const char KEY_MOVE_FORWARD = 'w';
const char KEY_MOVE_BACK = 's';
const char KEY_MOVE_LEFT = 'a';
const char KEY_MOVE_RIGHT = 'd';
const char KEY_LOOK_LEFT = 'k';
const char KEY_LOOK_RIGHT = 'l';
const char KEY_QUIT = 'q';
const char KEY_SHOW_HUD = 'h';

int main() {
    Graphics graphics(120, 40, (3.14159f / 4.0f), 16.0f); // Initialize graphics
    Map map("Map.dat", 34, 25); // Get the map from a file and instantiate a map object
    Player player({ 2, 2, 0 }); // Set up the player object

    // Acquire map data. Yoink.
    std::array<int, 2> mapDimensions = map.getDimensions();
    std::string mapString = map.getMap();

    auto tp1 = std::chrono::system_clock::now();
    auto tp2 = std::chrono::system_clock::now();

    while (!finished) {
        // We'll need time differential per frame to calculate modification
        // to movement speeds, to ensure consistant movement, as ray-tracing
        // is non-deterministic
        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();

        // Player movement and world collision detection
        int key = getch();
        struct fCoord25D proposedMovement = {NAN, NAN, NAN};
        switch (key) {
        case KEY_QUIT:
            // Quit
            finished = true;
            break;
        case KEY_SHOW_HUD:
            // Toggle hud
            showHUD = !showHUD;
            break;
        case KEY_MOVE_FORWARD:
            proposedMovement = player.stageMovement(MOVE_FORWARD, fElapsedTime);
            break;
        case KEY_MOVE_BACK:
            proposedMovement = player.stageMovement(MOVE_BACK, fElapsedTime);
            break;
        case KEY_MOVE_LEFT:
            proposedMovement = player.stageMovement(MOVE_LEFT, fElapsedTime);
            break;
        case KEY_MOVE_RIGHT:
            proposedMovement = player.stageMovement(MOVE_RIGHT, fElapsedTime);
            break;
        case KEY_LOOK_LEFT:
            player.look(LOOK_LEFT, fElapsedTime);
            break;
        case KEY_LOOK_RIGHT:
            player.look(LOOK_RIGHT, fElapsedTime);
            break;
        }

        if (!std::isnan(proposedMovement.x) || !std::isnan(proposedMovement.y) || !std::isnan(proposedMovement.a)) {
            bool movementValid = map.getCollision(proposedMovement);
            if (movementValid)
                player.setPosition(proposedMovement);
        }

        fCoord25D playerPos = player.getPosition();

        // Render current frame
        graphics.renderFrame(playerPos, mapDimensions, mapString, map.getValidWalls());

        // HUD Drawing and ncurses refreshing
        if (showHUD)
            graphics.renderHUD(playerPos, mapDimensions, mapString, fElapsedTime);

        graphics.renderControls();

        // Draw screen
        refresh();
    }

    endwin();
    return 0;
}
