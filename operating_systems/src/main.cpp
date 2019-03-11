#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include "Ball.h"
#include "BoundariesGuard.h"
#include "ncurses/Drawer.h"


float drawInitialSpeed()
{
    std::random_device randomGenerator;
    std::uniform_int_distribution<int> speed(12, 18);

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
    ncurses::Drawer painter;

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
    std::pair<size_t, size_t> pitch_sizes(pitch_x, pitch_y);

    painter.drawPitch(PITCH_TOP_LEFT_CORNER, pitch_sizes);
    runBalls(PITCH_TOP_LEFT_CORNER, pitch_sizes, BALL_SPAWN_RATIO_PER_SEC);
    return 0;
}
