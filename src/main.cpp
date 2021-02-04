#include "graphics.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "types.h"

#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <ncurses.h>
#include <thread>
#include <time.h>
#include <vector>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

using namespace BitBorn;

const std::chrono::duration<int, std::milli> framePeriod = std::chrono::milliseconds(1000 / 30);

bool finished = false;
bool showHUD = false;

string serverIP = "localhost";
int serverPort = 5080;

int main() {
    std::string datadir = "./";

    char *cDatadir = std::getenv("BITBORN_DATADIR");
    if (cDatadir != nullptr) {
        datadir = std::string(cDatadir);
    }
    //Check with server to make sure map is current. If server not up, skip this step
    try {
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char *msg = "map\n";
        char buffer[1024] = {0};
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return -1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(serverPort);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("\nConnection Failed \n");
            return -1;
        }
        send(sock, msg, strlen(msg), 0);
        printf("Hello message sent\n");
        valread = read(sock, buffer, 1024);
        printf("%s\n", buffer);
        string stringmap = string(buffer, 1024);
        map = stringmap;
        //
    }
    catch (...) {

    }

    Map map(datadir + "/map"); // Get the map from a file and instantiate a map object

    // Seed the RNG
    srand(time(NULL));

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
