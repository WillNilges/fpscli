#include "graphics.h"
#include <algorithm>
#include <cmath>
#include <ncurses.h>
#include <sstream>

using namespace BitBorn;

Graphics::Graphics(int screenWidth, int screenHeight, float fieldOfView, float depth)
    : nScreenWidth(screenWidth), nScreenHeight(screenHeight), fFOV(fieldOfView), fDepth(depth) {
    // NCurses setup
    setlocale(LC_ALL, ""); // Set locale for UTF-8 support
    initscr();             // Initialise NCurses screen
    noecho();              // Don't echo input to screen
    curs_set(0);           // Don't show terminal cursor
    nodelay(stdscr, true); // Don't halt program while waiting for input
    cbreak();              // Make input characters immediately available to the program

    getmaxyx(stdscr, terminalHeight, terminalWidth);
    resizeterm(40, 120);

    // Colors!
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);  // 'W'
    init_pair(2, COLOR_RED, COLOR_BLACK);    // 'R'
    init_pair(3, COLOR_GREEN, COLOR_BLACK);  // 'G'
    init_pair(4, COLOR_BLUE, COLOR_BLACK);   // 'B'
    init_pair(5, COLOR_YELLOW, COLOR_BLACK); // 'Y'
}

// Rendering and graphics
void Graphics::renderFrame(fCoord25D playerPos, std::array<int, 2> mapDimensions, std::string map,
                           std::vector<char> validWalls) {

    // Measure terminal size
    bool cleared = false;
    getmaxyx(stdscr, terminalHeight, terminalWidth);

    // Ensure terminal size is OK
    while (terminalHeight < nScreenHeight || terminalWidth < nScreenWidth) {
        if (!cleared) {
            clear();
            cleared = true;
        }

        std::ostringstream out;
        out << "Resize your terminal to at least (" << nScreenWidth << ", " << nScreenHeight
            << ") - current size is (" << terminalWidth << ", " << terminalHeight << ")";
        mvaddstr(0, 0, out.str().c_str());
        refresh();
        getmaxyx(stdscr, terminalHeight, terminalWidth);
    }

    int nMapHeight = mapDimensions.at(0);
    int nMapWidth = mapDimensions.at(1);

    for (int x = 0; x < Graphics::nScreenWidth; x++) {
        // For each column, calculate the projected ray angle into world space
        float fRayAngle = (playerPos.a - fFOV / 2.0f) + ((float)x / (float)Graphics::nScreenWidth) * fFOV;

        // Find distance to wall
        float fStepSize = 0.1f; // Increment size for ray casting, decrease to
                                // increase resolution
        float fDistanceToWall = 0.0f;

        bool bHitWall = false;  // Set when ray hits wall block
        bool bBoundary = false; // Set when ray hits boundary between two wall blocks

        float fEyeX = sinf(fRayAngle); // Unit vector for ray in player space
        float fEyeY = cosf(fRayAngle);

        // Work out what kind of block it is
        char wallBlock;

        // Incrementally cast ray from player, along ray angle, testing for
        // intersection with a block
        while (!bHitWall && fDistanceToWall < fDepth) {
            fDistanceToWall += fStepSize;
            int nTestX = (int)(playerPos.x + fEyeX * fDistanceToWall);
            int nTestY = (int)(playerPos.y + fEyeY * fDistanceToWall);

            // Test if ray is out of bounds
            if ((nTestX < 0 || nTestX >= nMapWidth) && (nTestY < 0 || nTestY >= nMapHeight)) {
                bHitWall = true; // Just set distance to maximum depth
                fDistanceToWall = fDepth;
            } else {
                // Ray is inbounds so test to see if the ray cell is a wall
                // block.
                wallBlock = map.c_str()[nTestX * nMapWidth + nTestY];
                if (std::find(validWalls.begin(), validWalls.end(), wallBlock) != validWalls.end()) {
                    // Ray has hit wall
                    bHitWall = true;

                    // To highlight tile boundaries, cast a ray from each corner
                    // of the tile, to the player. The more coincident this ray
                    // is to the rendering ray, the closer we are to a tile
                    // boundary, which we'll shade to add detail to the walls
                    std::vector<std::pair<float, float>> p;

                    // Test each corner of hit tile, storing the distance from
                    // the player, and the calculated dot product of the two
                    // rays
                    for (int tx = 0; tx < 2; tx++)
                        for (int ty = 0; ty < 2; ty++) {
                            // Angle of corner to eye
                            float vy = (float)nTestY + ty - playerPos.y;
                            float vx = (float)nTestX + tx - playerPos.x;
                            float d = std::sqrt(vx * vx + vy * vy);
                            float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
                            p.push_back(std::make_pair(d, dot));
                        }

                    // Sort Pairs from closest to farthest
                    std::sort(p.begin(), p.end(),
                              [](const std::pair<float, float> &left, const std::pair<float, float> &right) {
                                  return left.first < right.first;
                              });

                    // First two/three are closest (we will never see all four)
                    float fBound = 0.005;
                    if (std::acos(p.at(0).second) < fBound)
                        bBoundary = true;
                    if (std::acos(p.at(1).second) < fBound)
                        bBoundary = true;
                    if (std::acos(p.at(2).second) < fBound)
                        bBoundary = true;
                }
            }
        }

        // Calculate distance to ceiling and floor
        int nCeiling =
            (int)((float)(Graphics::nScreenHeight / 2.0) - Graphics::nScreenHeight / ((float)fDistanceToWall));
        int nFloor = Graphics::nScreenHeight - nCeiling;

        // Shader walls based on distance and material
        // If you add a new block type, you must code in how you want it to be
        // rendered.
        short nShade = ' ';
        if (fDistanceToWall <= fDepth / 4.0f)
            nShade = 0x2588; // Very close
        else if (fDistanceToWall < fDepth / 3.0f)
            nShade = 0x2593;
        else if (fDistanceToWall < fDepth / 2.0f)
            nShade = 0x2592;
        else if (fDistanceToWall < fDepth)
            nShade = 0x2591;
        else
            nShade = ' '; // Too far away

        // Decide which color to use for the wall, should it exist.
        int color = 1;
        switch (wallBlock) {
        case 'W':
            break;
        case 'R':
            color = 2;
            break;
        case 'G':
            color = 3;
            break;
        case 'B':
            color = 4;
            break;
        case 'Y':
            color = 5;
            break;
        default:
            color = 1;
            break;
        }

        if (bBoundary)
            nShade = ' '; // Draw a seam between wall blocks

        for (int y = 0; y < Graphics::nScreenHeight; y++) {
            // Each Section of the world
            if (y <= nCeiling) // Ceiling
            {
                mvaddch(y, x, ' ');
            } else if (y > nCeiling && y <= nFloor) // Walls
            {
                attron(COLOR_PAIR(color));
                wchar_t wstr[] = {nShade, L'\0'};
                mvaddwstr(y, x, wstr);
                attroff(COLOR_PAIR(color));

            } else // Floor
            {
                // Shade floor based on distance
                float b =
                    1.0f - (((float)y - Graphics::nScreenHeight / 2.0f) / ((float)Graphics::nScreenHeight / 2.0f));
                if (b < 0.25)
                    nShade = '#';
                else if (b < 0.5)
                    nShade = 'x';
                else if (b < 0.75)
                    nShade = '.';
                else if (b < 0.9)
                    nShade = '-';
                else
                    nShade = ' ';
                wchar_t wstr[] = {nShade, L'\0'};
                mvaddwstr(y, x, wstr);
            }
        }
    }
}

void Graphics::renderHUD(fCoord25D playerPos, std::array<int, 2> mapDimensions, std::string map, float fElapsedTime) {

    int nMapWidth = mapDimensions.at(0);
    int nMapHeight = mapDimensions.at(1);

    // Display Stats
    wchar_t stats[40];
    swprintf(stats, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", playerPos.x, playerPos.y, playerPos.a,
             1.0f / fElapsedTime);
    mvaddwstr(0, 0, stats);

    int minimapDimension = 21; // The minimap will be 21x21 characters
    int shift = minimapDimension/2;
    int xStart = floor(playerPos.y)-shift;
    int yStart = floor(playerPos.x)-shift;

    for (int nx = 0; nx < minimapDimension; nx++) {
        for (int ny = 0; ny < minimapDimension; ny++) {
            int formula = (yStart+ny) * nMapHeight + (xStart+nx);
            if ((formula) < 0 || (formula) > map.length() || (xStart+nx) < 0 || (xStart+nx) >= nMapHeight) {
                mvaddch(ny + 1, nx, ' ');
            } else {
                // This code sucks. TODO: Make it not suck as much.
                char mapBlock = (chtype)map[formula];
                int color = 1;
                short character = 0x2588;
                switch (mapBlock) {
                case 'W':
                    break;
                case 'R':
                    color = 2;
                    break;
                case 'G':
                    color = 3;
                    break;
                case 'B':
                    color = 4;
                    break;
                case 'Y':
                    color = 5;
                    break;
                default:
                    color = 1;
                    character = ' ';
                    break;
                }
                attron(COLOR_PAIR(color));
                wchar_t wstr[] = {character, L'\0'};
                mvaddwstr(ny+1, nx, wstr);
                attroff(COLOR_PAIR(color));
            }
        }
    }

    // Display Player
    attron(COLOR_PAIR(2));
    mvaddch((minimapDimension/2)+1, (minimapDimension/2), 'P');
    attroff(COLOR_PAIR(2));
}

void Graphics::renderControls() {
    // Display controls
    wchar_t instructions[40] = L"wsad=Move, kl=look, q=quit, h=HUD";
    attron(A_BOLD);
    mvaddwstr(Graphics::nScreenHeight - 1, 0, instructions);
    attroff(A_BOLD);
}

Graphics::~Graphics() {
    resizeterm(terminalHeight, terminalWidth);
}
