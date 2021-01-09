#include "main.hpp"

using namespace std;

// Player object
namespace BitBorn
{
    class Player {
        public:
            Player(float x, float y, float a)
                : fPlayerX(x), fPlayerY(y), fPlayerA(a){}

            bool move(int key, std::vector<int> mapDimensions, string map, float fElapsedTime);

            std::vector<float> getPos();

        private:

            // Stuff that will change
            int health{ 100 };
            float fPlayerX{ 10.0f };
            float fPlayerY{ 10.0f };
            float fPlayerA{ 10.0f };

            // Stuff that will probably not change.
            float fSpeed{ 150.0f };        // Walking Speed

    };
};