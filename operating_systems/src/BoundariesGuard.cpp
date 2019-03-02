#include "BoundariesGuard.h"


BoundariesGuard::BoundariesGuard(std::pair<size_t, size_t> leftCorner, std::pair<size_t, size_t> sizes)
{
    lCornerX = leftCorner.first + 1;
    rCornerX = lCornerX + sizes.first - 1;

    tCornerY = leftCorner.second + 1;
    bCornerY = tCornerY + sizes.second - 1;
}


CrossResult BoundariesGuard::boundariesCrossed(std::pair<size_t, size_t> position)
{
    if(position.first <= lCornerX or position.first >= rCornerX)
    {
        return CrossResult::CROSSED_HORIZONTALLY;
    }
    else if(position.second <= tCornerY or position.second >= bCornerY)
    {
        return CrossResult::CROSSED_VERTICALLY;
    }
    else
    {
        return CrossResult::NOT_CROSSED;
    }
}
