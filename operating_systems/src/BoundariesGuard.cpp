#include "BoundariesGuard.h"
#include "ncurses/Drawer.h"

BoundariesGuard::BoundariesGuard(point2d hookPoint, std::pair<size_t, size_t> sizes)
{
    leftCornerX = hookPoint.first + 1;
    rightCornerX = leftCornerX + sizes.first - 1;
    topCornerY = hookPoint.second + 1;
    bottomCornerY = topCornerY + sizes.second - 1;
}


CrossResult BoundariesGuard::boundariesCrossed (point2d position) const
{
    CrossResult result(CrossResult::NOT_CROSSED);
    uint8_t crossCounter = 0;

    if(position.first <= leftCornerX or position.first >= rightCornerX)
    {
        result = CrossResult::CROSSED_HORIZONTALLY;
        crossCounter++;
    }

    if(position.second <= topCornerY or position.second >= bottomCornerY)
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
