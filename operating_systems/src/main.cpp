#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include "ExecutionManager.h"
#include "ncurses/Drawer.h"
#include "helpers/Randomizer.h"
/*
 * Zmienne warunkowe, na planszy obszar prostokatny,
 * jak kulka wchodzi to wykonuje 2 ruchy ,
 * jak zdazy wyskoczyc to zasypia az inna kulka tam wpadnie,
 * zawsze ktoras kulka jest pierwsza
 * */

int main(int argc, char *argv[])
{
    const point2d PITCH_TOP_LEFT_CORNER(1, 1);
    const float BALL_SPAWN_RATIO_PER_SEC = 0.1;
    int pitch_x, pitch_y;
    if(argc == 3)
    {
        pitch_x = static_cast<int>(*argv[1]);
        pitch_y = static_cast<int>(*argv[1]);
    }
    else
    {
        pitch_x = 60;
        pitch_y = 30;
    }
    std::pair<size_t, size_t> pitch_sizes(pitch_x, pitch_y);
    ExecutionManager ballExecutionManager(PITCH_TOP_LEFT_CORNER, pitch_sizes, BALL_SPAWN_RATIO_PER_SEC);
    ncurses::Drawer painter;

    painter.drawPitch(PITCH_TOP_LEFT_CORNER, pitch_sizes);
    painter.drawPitch(std::make_pair<size_t, size_t>(10, 10), std::make_pair<size_t, size_t>(10, 10));
    ballExecutionManager.execute();

    return 0;
}
