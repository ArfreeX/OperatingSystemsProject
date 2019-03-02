#ifndef BOUNDARIESGUARD_H
#define BOUNDARIESGUARD_H

#include <iostream>

enum CrossResult
{
    CROSSED_HORIZONTALLY,
    CROSSED_VERTICALLY,
    NOT_CROSSED
};

class BoundariesGuard
{
public:
    BoundariesGuard(std::pair<size_t, size_t> leftCorner, std::pair<size_t, size_t> sizes);
    CrossResult boundariesCrossed(std::pair<size_t, size_t> position);

private:
    size_t tCornerY, bCornerY;
    size_t lCornerX, rCornerX;
};

#endif // BOUNDARIESGUARD_H
