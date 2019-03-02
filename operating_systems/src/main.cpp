#include <iostream>
#include <thread>
#include "Ball.h"
#include "BoundariesGuard.h"
#include "ncurses/Drawer.h"

std::pair<size_t, size_t> drawStartingPosition(std::pair<size_t, size_t> leftCorner, std::pair<size_t, size_t> sizes)
{
    std::pair<size_t, size_t> point(
                rand() % (sizes.first + leftCorner.first - 1) + leftCorner.first - 1,
                rand() % (sizes.second + leftCorner.second - 1) + leftCorner.second - 1);
    return point;
}


int main()
{
    srand(time(NULL));
    std::pair<size_t, size_t> startingPoint(5, 5);
    std::pair<size_t, size_t> sizes(50, 15);
    ncurses::Drawer painter;
    double ballsPerSec = 2;
    size_t ballSpeed = 11000;
    painter.drawPitch(startingPoint, sizes);
    while(true)
    {
        Ball ball(drawStartingPosition(startingPoint, sizes), BoundariesGuard(startingPoint, sizes), ballSpeed);
        std::this_thread::sleep_for( std::chrono::milliseconds(static_cast<int>(1000.0 / ballsPerSec)));
    }
}
