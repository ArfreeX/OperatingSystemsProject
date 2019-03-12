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
    BoundariesGuard(point2d leftCorner, std::pair<size_t, size_t> sizes);
    BoundariesGuard(const BoundariesGuard&) = default;
    CrossResult boundariesCrossed(point2d position);

private:
    size_t tCornerY, bCornerY;
    size_t lCornerX, rCornerX;
};

#endif // BOUNDARIESGUARD_H
