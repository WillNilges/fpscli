namespace BitBorn{
#ifndef __TYPES_H_
#define __TYPES_H_
    struct fCoord25D {
        float x;
        float y;
        float a;
    };

    enum action {
        MOVE_FORWARD,
        MOVE_BACK,
        MOVE_LEFT,
        MOVE_RIGHT,
        LOOK_LEFT,
        LOOK_RIGHT
    };
#endif // __TYPES_H_
}