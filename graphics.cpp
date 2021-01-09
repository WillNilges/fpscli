#include "graphics.h"

using namespace std;
using namespace BitBorn;


// Rendering and graphics
void Graphics::renderFrame(std::vector<float> playerPos, std::vector<int> mapDimensions, string map, std::vector<char> validWalls)
{
    // Cursed but readable
    float fPlayerX = playerPos.at(0);
    float fPlayerY = playerPos.at(1);
    float fPlayerA = playerPos.at(2);

    int nMapHeight = mapDimensions.at(0);
    int nMapWidth = mapDimensions.at(1);

    for (int x = 0; x < Graphics::nScreenWidth; x++)
    {
        // For each column, calculate the projected ray angle into world space
        float fRayAngle = (fPlayerA - fFOV/2.0f) + ((float)x / (float)Graphics::nScreenWidth) * fFOV;

        // Find distance to wall
        float fStepSize = 0.1f;        // Increment size for ray casting, decrease to increase resolution
        float fDistanceToWall = 0.0f;

        bool bHitWall = false;         // Set when ray hits wall block
        bool bBoundary = false;        // Set when ray hits boundary between two wall blocks

        float fEyeX = sinf(fRayAngle); // Unit vector for ray in player space
        float fEyeY = cosf(fRayAngle);

        // Work out what kind of block it is
        char wallBlock;

        // Incrementally cast ray from player, along ray angle, testing for
        // intersection with a block
        while (!bHitWall && fDistanceToWall < fDepth)
        {
            fDistanceToWall += fStepSize;
            int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
            int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

            // Test if ray is out of bounds
            if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
            {
                bHitWall = true;            // Just set distance to maximum depth
                fDistanceToWall = fDepth;
            }
            else
            {
                // Ray is inbounds so test to see if the ray cell is a wall block.
                wallBlock = map.c_str()[nTestX * nMapWidth + nTestY];
                if (std::find(validWalls.begin(), validWalls.end(), wallBlock) != validWalls.end())
                {
                    // Ray has hit wall
                    bHitWall = true;

                    // To highlight tile boundaries, cast a ray from each corner
                    // of the tile, to the player. The more coincident this ray
                    // is to the rendering ray, the closer we are to a tile
                    // boundary, which we'll shade to add detail to the walls
                    vector<pair<float, float>> p;

                    // Test each corner of hit tile, storing the distance from
                    // the player, and the calculated dot product of the two rays
                    for (int tx = 0; tx < 2; tx++)
                        for (int ty = 0; ty < 2; ty++)
                        {
                            // Angle of corner to eye
                            float vy = (float)nTestY + ty - fPlayerY;
                            float vx = (float)nTestX + tx - fPlayerX;
                            float d = sqrt(vx*vx + vy*vy);
                            float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
                            p.push_back(make_pair(d, dot));
                        }

                    // Sort Pairs from closest to farthest
                    sort(p.begin(), p.end(), [](const pair<float, float> &left, const pair<float, float> &right) {return left.first < right.first; });

                    // First two/three are closest (we will never see all four)
                    float fBound = 0.005;
                    if (acos(p.at(0).second) < fBound) bBoundary = true;
                    if (acos(p.at(1).second) < fBound) bBoundary = true;
                    if (acos(p.at(2).second) < fBound) bBoundary = true;
                }
            }
        }

        // Calculate distance to ceiling and floor
        int nCeiling = (int)((float)(Graphics::nScreenHeight/2.0) - Graphics::nScreenHeight / ((float)fDistanceToWall));
        int nFloor = Graphics::nScreenHeight - nCeiling;

        // Shader walls based on distance and material
        // If you add a new block type, you must code in how you want it to be rendered.
        short nShade = ' ';
        if (fDistanceToWall <= fDepth / 4.0f)        nShade = 0x2588;    // Very close
        else if (fDistanceToWall < fDepth / 3.0f)    nShade = 0x2593;
        else if (fDistanceToWall < fDepth / 2.0f)    nShade = 0x2592;
        else if (fDistanceToWall < fDepth)           nShade = 0x2591;
        else                                         nShade = ' ';       // Too far away

        // Decide which color to use for the wall, should it exist.
        int color = 1;
        switch(wallBlock) {
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

        for (int y = 0; y < Graphics::nScreenHeight; y++)
        {
            // Each Section of the world
            if(y <= nCeiling) // Ceiling
            {
                mvaddch(y, x, ' ');
            }
            else if(y > nCeiling && y <= nFloor) // Walls
            {
                attron(COLOR_PAIR(color));
                wchar_t wstr[] = { nShade, L'\0' };
                mvaddwstr(y, x, wstr);
                attroff(COLOR_PAIR(color));
                
            }
            else // Floor
            {
                // Shade floor based on distance
                float b = 1.0f - (((float)y -Graphics::nScreenHeight/2.0f) / ((float)Graphics::nScreenHeight / 2.0f));
                if (b < 0.25)        nShade = '#';
                else if (b < 0.5)    nShade = 'x';
                else if (b < 0.75)   nShade = '.';
                else if (b < 0.9)    nShade = '-';
                else                 nShade = ' ';
                wchar_t wstr[] = { nShade, L'\0' };
                mvaddwstr(y, x, wstr);
            }
        }
    }
}

void Graphics::renderHUD(std::vector<float> playerPos, std::vector<int> mapDimensions, string map, float fElapsedTime)
{
    // Cursed but readable
    float fPlayerX = playerPos.at(0);
    float fPlayerY = playerPos.at(1);
    float fPlayerA = playerPos.at(2);

    int nMapHeight = mapDimensions.at(0);
    int nMapWidth = mapDimensions.at(1);

    // Display Stats
    wchar_t stats[40];
    swprintf(stats, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", fPlayerX, fPlayerY, fPlayerA, 1.0f/fElapsedTime);
    mvaddwstr(0, 0, stats);

    // Display Map
    for (int nx = 0; nx < nMapWidth; nx++)
    {
        for (int ny = 0; ny < nMapWidth; ny++)
        {
            mvaddch(ny+1, nx, (chtype)map[ny * nMapWidth + nx]);
        }
    }

    // Display Player
    mvaddch((int)fPlayerX+1, ((int)fPlayerY), 'P');
}

void Graphics::renderControls()
{
    // Display controls
    wchar_t instructions[40] = L"wsad=Move, kl=look, q=quit, h=HUD";
    attron(A_BOLD);
    mvaddwstr(Graphics::nScreenHeight-1,0, instructions);
    attroff(A_BOLD);
}

std::vector<int> Graphics::getScreenDimensions(){
    return { Graphics::nScreenHeight, Graphics::nScreenWidth };
}