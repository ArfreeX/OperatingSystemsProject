#ifndef EXECUTIONMANAGER_H
#define EXECUTIONMANAGER_H

#include "assets/Ball.h"
#include "ncurses/Drawer.h"

class ExecutionManager
{
public:
    ExecutionManager(point2d pitch_corner, std::pair<size_t, size_t> pitch_edges, double spawn_ratio);

    void execute();
private:
    void adjustSpeed(Direction direction, double &speed);

    const point2d PITCH_CORNER;
    const double BALL_SPAWN_RATIO;
    const std::pair<size_t, size_t> PITCH_EDGES;

    ncurses::Drawer painter;
};

#endif // EXECUTIONMANAGER_H
