#ifndef BALL_H
#define BALL_H

#include <mutex>
#include <thread>
#include <future>
#include "BoundariesGuard.h"


class Ball
{
public:
    Ball(std::pair<size_t, size_t> leftCorner, std::pair<size_t, size_t> sizes,
         BoundariesGuard bGuard, float startingSpeed);
    Ball(const Ball &obj) = default;
    Ball(Ball&&) = default;
    ~Ball();

    void execute();

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

    void movement();
    Direction drawDirection();
    std::pair<size_t, size_t> drawStartingPosition(std::pair<size_t, size_t> leftCorner,
                                                   std::pair<size_t, size_t> sizes);
    static std::mutex movement_mutex;
    std::thread thread;
    BoundariesGuard bGuard;
    std::pair<int, int> position;
    bool stopThread;
    float speed;
};

#endif // BALL_H
