#include "graphics.h"
#include "map.h"
#include "player.h"

#include <chrono>
#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <vector>

using namespace BitBorn;

bool finished = false;
bool showHUD = false;

int main() {
    Graphics graphics(120, 40, (3.14159f / 4.0f), 16.0f); // Initialize graphics
    Map map("Map.dat", 24,
            24);              // Get the map from a file and instantiate a map object
    Player player(10, 10, 0); // Set up the player object

    // Acquire map data. Yoink.
    std::vector<int> mapDimensions = map.getDimensions();
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

        // Measure terminal size
        int terminalWidth;
        int terminalHeight;
        bool cleared = false;
        getmaxyx(stdscr, terminalHeight, terminalWidth);

        std::vector<int> screenDimensions = graphics.getScreenDimensions();

        // Ensure terminal size is OK
        while (terminalHeight != screenDimensions[0] || terminalWidth != screenDimensions[1]) {
            if (!cleared) {
                clear();
                cleared = true;
            }

            std::ostringstream out;
            out << "Resize your terminal to (" << screenDimensions[1] << ", " << screenDimensions[0]
                << ") - current size is (" << terminalWidth << ", " << terminalHeight << ")";
            mvaddstr(0, 0, out.str().c_str());
            refresh();
            getmaxyx(stdscr, terminalHeight, terminalWidth);
        }

        // Player movement and world collision detection
        int key = getch();
        switch (key) {
        case 'q':
            // Quit
            finished = true;
            break;
        case 'h':
            // Toggle hud
            showHUD = !showHUD;
            break;
        default:
            // Do player movement
            player.move(key, mapDimensions, mapString, fElapsedTime);
            break;
        }

        std::vector<float> playerPos = player.getPos();

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
