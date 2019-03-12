#ifndef BALL_H
#define BALL_H

#include <future>
#include <mutex>
#include <thread>
#include "BoundariesGuard.h"


typedef std::pair<size_t, size_t> point2d;

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
    Ball(point2d initialPosition, Direction initialDirection, float initialSpeed, BoundariesGuard bGuard);
    ~Ball();

    void execute();
    static void stopBalls();
private:
    void movement();

    static std::mutex movement_mutex;
    static bool stopThread;
    std::thread thread;
    BoundariesGuard bGuard;

    point2d position;
    Direction direction;
    float speed;
};

#endif // BALL_H
