#ifndef EXECUTIONMANAGER_H
#define EXECUTIONMANAGER_H

#include "Ball.h"

class ExecutionManager
{
public:
    ExecutionManager(point2d pitch_corner, std::pair<size_t, size_t> pitch_sizes, double spawn_ratio);

    void execute();
private:
    void adjustSpeed(Direction direction, double &speed);
    void spawnSwamp();

    const point2d PITCH_CORNER;
    const double BALL_SPAWN_RATIO;
    const std::pair<size_t, size_t> PITCH_SIZES;

    point2d swampCorner;
    std::pair<size_t, size_t> swampSizes;
};

#endif // EXECUTIONMANAGER_H
