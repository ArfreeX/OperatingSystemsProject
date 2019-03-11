#ifndef BALL_H
#define BALL_H

#include <future>
#include <mutex>
#include <thread>
#include "BoundariesGuard.h"


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

class Ball
{
public:
    Ball(std::pair<size_t, size_t> leftCorner, std::pair<size_t, size_t> sizes,
         BoundariesGuard bGuard, float startingSpeed);
    ~Ball();

    void execute();

private:


    void movement();
    Direction drawDirection();
    std::pair<size_t, size_t> drawStartingPosition(std::pair<size_t, size_t> leftCorner,
                                                   std::pair<size_t, size_t> sizes);
    static std::mutex movement_mutex;
    std::thread thread;
    bool stopThread;
    BoundariesGuard bGuard;

    std::pair<int, int> position;
    Direction direction;
    float speed;
};

#endif // BALL_H
