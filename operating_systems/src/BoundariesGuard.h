#ifndef BOUNDARIESGUARD_H
#define BOUNDARIESGUARD_H

#include <iostream>

typedef std::pair<size_t, size_t> point2d;

enum class CrossResult
{
    CROSSED_HORIZONTALLY,
    CROSSED_VERTICALLY,
    CROSSED_CORNER,
    NOT_CROSSED
};

class BoundariesGuard
{
public:
    BoundariesGuard(point2d hookPoint, std::pair<size_t, size_t> sizes,
                    point2d swampHookPoint, std::pair<size_t, size_t> swampSizes);
    CrossResult boundariesCrossed(point2d position);
    bool trespassingSwamp(point2d position);
private:
    size_t topCornerY, bottomCornerY;
    size_t leftCornerX, rightCornerX;

    size_t swampTopCornerY, swampBottomCornerY;
    size_t swampLeftCornerX, swampRightCornerX;
};

#endif // BOUNDARIESGUARD_H
