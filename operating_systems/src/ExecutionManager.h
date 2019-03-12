#ifndef EXECUTIONMANAGER_H
#define EXECUTIONMANAGER_H

#include "Ball.h"

class ExecutionManager
{
public:
    ExecutionManager(point2d pitch_corner, std::pair<size_t, size_t> pitch_sizes, float spawn_ratio);

    void execute();
private:
    float drawInitialSpeed();
    Direction drawInitialDirection();
    point2d drawInitialPosition();
    void adjustSpeed(Direction direction, float &speed);

    const std::pair<size_t, size_t> PITCH_CORNER;
    const float BALL_SPAWN_RATIO;
    const std::pair<size_t, size_t> PITCH_SIZES;
};

#endif // EXECUTIONMANAGER_H
