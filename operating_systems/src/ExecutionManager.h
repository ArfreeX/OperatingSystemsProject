#ifndef EXECUTIONMANAGER_H
#define EXECUTIONMANAGER_H

#include "Ball.h"

class ExecutionManager
{
public:
    ExecutionManager();

    void execute();
private:
    float drawInitialSpeed();
    Direction drawInitialDirection();
    std::pair<size_t, size_t> drawInitialPosition(std::pair<size_t, size_t> pitch_corner,
                                                  std::pair<size_t, size_t> pitch_sizes);
    void adjustSpeed(float &speed);

    const std::pair<size_t, size_t> PITCH_CORNER;
    const float BALL_SPAWN_RATIO;
    const std::pair<size_t, size_t> PITCH_SIZES;
};

#endif // EXECUTIONMANAGER_H
