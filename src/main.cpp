#include "graphics.h"
#include "map.h"
#include "player.h"
#include "types.h"
#include "input.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <ncurses.h>
#include <array>
#include <vector>
#include <time.h>
#include <thread>

using namespace BitBorn;

const std::chrono::duration<int, std::milli> framePeriod = std::chrono::milliseconds(1000 / 30);

bool finished = false;
bool showHUD = false;

int main() {
    std::string datadir = "./";

    char *cDatadir = std::getenv("BITBORN_DATADIR");
    if (cDatadir != nullptr) {
        datadir = std::string(cDatadir);
    }
    Map map(datadir + "/map"); // Get the map from a file and instantiate a map object

    // Seed the RNG
    srand ( time(NULL) );

    fCoord25D currentSpawn = map.getRandomSpawn();
    fCoord25D nextSpawn = currentSpawn;

    Player player(currentSpawn); // Set up the player object

    Graphics graphics(120, 40, (3.14159f / 4.0f), 32.0f); // Initialize graphics

    // Acquire map data. Yoink.
    std::array<int, 2> mapDimensions = map.getDimensions();
    std::string mapString = map.getMap();

    auto lastFrameStart = std::chrono::steady_clock::now();

    while (!finished) {
        // We'll need time differential per frame to calculate modification
        // to movement speeds, to ensure consistant movement, as ray-tracing
        // is non-deterministic
        auto frameStart = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsedTime = frameStart - lastFrameStart;
        lastFrameStart = frameStart;
        float fElapsedTime = elapsedTime.count();

        // Player movement and world collision detection
        Key key = (Key)getch();
        struct fCoord25D proposedMovement = {NAN, NAN, NAN};
        switch (key) {
        case Key::QUIT:
            // Quit
            finished = true;
            break;
        case Key::SHOW_HUD:
            // Toggle hud
            showHUD = !showHUD;
            break;
        case Key::RESPAWN:
            // Don't want the player to re-spawn at their old location.
            while (nextSpawn.x == currentSpawn.x && nextSpawn.y == currentSpawn.y)
                nextSpawn = map.getRandomSpawn();
            player.setPosition(nextSpawn);
            currentSpawn = nextSpawn;
            break;
        case Key::MOVE_FORWARD:
            proposedMovement = player.stageMovement(MOVE_FORWARD, fElapsedTime);
            break;
        case Key::MOVE_BACK:
            proposedMovement = player.stageMovement(MOVE_BACK, fElapsedTime);
            break;
        case Key::MOVE_LEFT:
            proposedMovement = player.stageMovement(MOVE_LEFT, fElapsedTime);
            break;
        case Key::MOVE_RIGHT:
            proposedMovement = player.stageMovement(MOVE_RIGHT, fElapsedTime);
            break;
        case Key::LOOK_LEFT:
            player.look(LOOK_LEFT, fElapsedTime);
            break;
        case Key::LOOK_RIGHT:
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
        graphics.renderFrame(playerPos, mapDimensions, mapString, map.getValidWalls(), map.getValidIndoors());

        // HUD Drawing and ncurses refreshing
        if (showHUD)
            graphics.renderHUD(playerPos, mapDimensions, mapString, fElapsedTime);

        graphics.renderControls();

        // Draw screen
        refresh();

        auto frameTime = std::chrono::steady_clock::now() - frameStart;
        std::this_thread::sleep_for(framePeriod - frameTime);
    }

    endwin();
    return 0;
}
