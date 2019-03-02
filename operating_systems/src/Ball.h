#ifndef BALL_H
#define BALL_H

#include <mutex>
#include <thread>
#include "BoundariesGuard.h"


class Ball
{
public:
    Ball(std::pair<size_t, size_t> startingPosition, BoundariesGuard bGuard, float startingSpeed);

private:
    enum Direction
    {
        LEFT,
        TOP_LEFT,
        TOP,
        TOP_RIGHT,
        RIGHT,
        BOTTOM_RIGHT,
        BOTTOM,
        BOTTOM_LEFT,
        LAST_ELEMENT
    };

    void movement [[ noreturn ]] (Direction direction);
    Direction drawDirection();

    BoundariesGuard bGuard;
    std::pair<int, int> position;
    float speed;
};

#endif // BALL_H
