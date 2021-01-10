#pragma once
namespace BitBorn{

    enum action {
        MOVE_FORWARD,
        MOVE_BACK,
        MOVE_LEFT,
        MOVE_RIGHT,
        LOOK_LEFT,
        LOOK_RIGHT
    };
struct fCoord25D {
    float x;
    float y;
    float a;
};
} // namespace BitBorn
