#include "main.hpp"
#include "player.h"
#include "graphics.h"

using namespace std;
using namespace BitBorn;

// int nScreenWidth  = 120;       // Console Screen Size X (columns)
// int nScreenHeight = 40;       // Console Screen Size Y (rows)
int nMapWidth     = 24;           // World Dimensions
int nMapHeight    = 24;

// float fFOV        = 3.14159f / 4.0f; // Field of View
// float fDepth      = 16.0f;         // Maximum rendering distance

// char validWalls[5] = { 'W', 'R', 'G', 'B', 'Y' }; // Valid, collidable walls.

int main()
{
    Graphics graphics(120, 40, (3.14159f / 4.0f), 16.0f);

    // Get the map from a file
    string map = std::string{}; // THE WOLRD ARRAY
    std::ifstream mapFile{ "Map.dat" };
    if (!mapFile) 
    {
        endwin();
        std::cerr << "Error. Cannot open map file. Does it actually exist?" << endl;
        return 1;
    }
    std::ostringstream sstr;
    sstr << mapFile.rdbuf();
    map = sstr.str();
    map.erase(std::remove(map.begin(), map.end(), '\n'), map.end());

    Player player(10, 10, 0);

    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();

    if (nMapWidth != nMapHeight) {
        endwin();
        std::cout << "The world gets a bit funky when nMapWidth != nMapHeight. Correct that and try again." << endl;
        return 1;
    }

    bool finished = false;
    bool showHUD = false;
    while (!finished)
    {
        // We'll need time differential per frame to calculate modification
        // to movement speeds, to ensure consistant movement, as ray-tracing
        // is non-deterministic
        tp2 = chrono::system_clock::now();
        chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();

        // Measure terminal size
        int terminalWidth;
        int terminalHeight;
        bool cleared = false;
        getmaxyx(stdscr, terminalHeight, terminalWidth);

        vector<int> screenDimensions = graphics.getScreenDimensions();

        // Ensure terminal size is OK
        while (terminalHeight != screenDimensions[0] || terminalWidth != screenDimensions[1])
        {
            if (!cleared)
            {
                clear();
                cleared = true;
            }

            ostringstream out;
            out << "Resize your terminal to (" << screenDimensions[1] << ", " << screenDimensions[0] << ") - current size is (" << terminalWidth << ", " << terminalHeight << ")";
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
                showHUD = !showHUD;
                break;
            default:
                // Do player movement
                player.move(key, map, fElapsedTime);
                break;
        }

        std::vector<float> playerPos = player.getPos();

        // Render current frame
        graphics.renderFrame(playerPos, map);

        // HUD Drawing and ncurses refreshing
        if (showHUD) {
            graphics.renderHUD(playerPos, fElapsedTime, map);
        }

        graphics.renderControls();

        // Draw screen
        refresh();
    }

    endwin();
    return 0;
}

// That's It!! - Jx9
