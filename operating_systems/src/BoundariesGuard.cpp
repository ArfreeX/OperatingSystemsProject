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
    CrossResult result(CrossResult::NOT_CROSSED);
    uint8_t crossCounter = 0;

    if(position.first <= lCornerX or position.first >= rCornerX)
    {
        result = CrossResult::CROSSED_HORIZONTALLY;
        crossCounter++;
    }

    if(position.second <= tCornerY or position.second >= bCornerY)
    {
        result = CrossResult::CROSSED_VERTICALLY;
        crossCounter++;
    }

    if(crossCounter == 2)
    {
        result = CrossResult::CROSSED_CORNER;
    }

    return result;
}
