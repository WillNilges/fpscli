#pragma once

#include "types.h"
#include <string>
#include <vector>

namespace BitBorn {

enum Action { MOVE_FORWARD, MOVE_BACK, MOVE_LEFT, MOVE_RIGHT, LOOK_LEFT, LOOK_RIGHT };

class Entity {
    public:
        Entity(bool controlled, fCoord25D position);
        Entity(bool controlled, fCoord25D position, int maxHP);
        
        // Movement functions
        void look(Action stagedAction, float fElapsedTime);
        fCoord25D stageMovement(Action stagedAction, float fElapsedTime);
        fCoord25D getPosition();
        void setPosition(fCoord25D newPosition);

        // Health functions
        int getCurrentHealth();
        int getMaxHealth();
        bool isDead();
        void heal(int amt);
        void harm(int amt);

    private:
        // Stuff that will change
        int nHealth{100};
        fCoord25D position{10.0f, 10.0f, 10.0f};
        bool bIsControlled{false};
        // std::vector<weapon> weapons; //TODO!

        // Stuff that will probably not change.
        const std::string sID;
        const int nMaxHealth{100};
        const float fSpeed{150.0f}; // Walking Speed
};
}; // namespace BitBorn
