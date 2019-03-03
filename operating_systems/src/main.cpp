#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include "Ball.h"
#include "BoundariesGuard.h"
#include "ncurses/Drawer.h"


int main /* [[ noreturn ]] */()
{
    srand(time(NULL));

    ncurses::Drawer painter;

    const std::pair<size_t, size_t> PITCH_TOP_LEFT_CORNER(0, 0);
    const std::pair<size_t, size_t> PITCH_SIZES(30, 15);
    const float BALL_SPEED_PER_SEC = 1;
    const float BALL_SPAWN_RATIO_PER_SEC = 0.25;

    painter.drawPitch(PITCH_TOP_LEFT_CORNER, PITCH_SIZES);

    std::vector<std::unique_ptr<Ball>> basket;
    size_t balls = 0;
    while(balls <= 20)
    {
        std::unique_ptr<Ball> ballPtr = std::make_unique<Ball>(PITCH_TOP_LEFT_CORNER, PITCH_SIZES,
                                                               BoundariesGuard(PITCH_TOP_LEFT_CORNER, PITCH_SIZES),
                                                               BALL_SPEED_PER_SEC);
        ballPtr->execute();
        basket.emplace_back(std::move(ballPtr));
        balls++;

        std::this_thread::sleep_for( std::chrono::milliseconds(static_cast<int>(1000.0 / BALL_SPAWN_RATIO_PER_SEC)));
    }
}
