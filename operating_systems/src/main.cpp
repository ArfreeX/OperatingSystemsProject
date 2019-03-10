#include <iostream>
#include <algorithm>
#include <random>
#include <memory>
#include <thread>
#include <vector>
#include "Ball.h"
#include "BoundariesGuard.h"
#include "ncurses/Drawer.h"


float drawSpeed()
{
    std::random_device randomGenerator;
    std::uniform_int_distribution<int> speed(10, 15);

    return static_cast<int>(speed(randomGenerator));
}

// Dodac konczenie programu
// Przerywanie programu z klawisza, sprawdzic tego mutexa, maly refactor
// Dodac endwina - konczenie watkow w jednym czasie

int main(int argc, char *argv[])
{
    const std::pair<size_t, size_t> PITCH_TOP_LEFT_CORNER(1, 1);
    const float BALL_SPAWN_RATIO_PER_SEC = 0.2;
    int pitch_x, pitch_y;

    if(argc == 3)
    {
        pitch_x = static_cast<int>(*argv[1]);
        pitch_y = static_cast<int>(*argv[1]);
    }
    else
    {
        pitch_x = 30;
        pitch_y = 15;
    }

    srand(time(NULL));
    bool stopProgramm = false;

    ncurses::Drawer painter;
    std::thread t1(&ncurses::Drawer::stop,&painter, stopProgramm);

    std::pair<size_t, size_t> pitch_sizes(pitch_x, pitch_y);


    painter.drawPitch(PITCH_TOP_LEFT_CORNER, pitch_sizes);
    {
        std::vector<std::unique_ptr<Ball>> basket;
        size_t balls = 0;
        while(true)
        {
            std::unique_ptr<Ball> ballPtr = std::make_unique<Ball>(PITCH_TOP_LEFT_CORNER, pitch_sizes,
                                                                   BoundariesGuard(PITCH_TOP_LEFT_CORNER, pitch_sizes),
                                                                   drawSpeed());
            ballPtr->execute();
            basket.emplace_back(std::move(ballPtr));
            balls++;

            std::this_thread::sleep_for( std::chrono::milliseconds(static_cast<int>(1000.0 / BALL_SPAWN_RATIO_PER_SEC)));
        }
    }
    t1.join();
    return 0;
}
