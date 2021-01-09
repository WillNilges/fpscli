# include "main.hpp"

using namespace std;

namespace BitBorn {
    class Graphics {
        public:
            Graphics(int screenWidth, int screenHeight, float fieldOfView, float depth)
                : nScreenWidth(screenWidth), nScreenHeight(screenHeight), fFOV(fieldOfView), fDepth(depth)
            {
                // NCurses setup
                setlocale(LC_ALL, "");    // Set locale for UTF-8 support
                initscr();                // Initialise NCurses screen
                noecho();                 // Don't echo input to screen
                curs_set(0);              // Don't show terminal cursor
                nodelay(stdscr, true);    // Don't halt program while waiting for input
                cbreak();                 // Make input characters immediately available to the program

                // Colors!
                start_color();
                init_pair(1, COLOR_WHITE, COLOR_BLACK);  // 'W'
                init_pair(2, COLOR_RED, COLOR_BLACK);    // 'R'
                init_pair(3, COLOR_GREEN, COLOR_BLACK);  // 'G'
                init_pair(4, COLOR_BLUE, COLOR_BLACK);   // 'B'
                init_pair(5, COLOR_YELLOW, COLOR_BLACK); // 'Y'
            }

            void renderFrame(std::vector<float> playerPos, string map);
            void renderHUD(std::vector<float> playerPos, float fElapsedTime, string map);
            void renderControls();

            std::vector<int> getScreenDimensions();

            private:
                int nScreenWidth{ 120 };
                int nScreenHeight{ 40 };
                float fFOV{ 3.14159f / 4.0f };
                float fDepth{ 16.0f };
    };
}