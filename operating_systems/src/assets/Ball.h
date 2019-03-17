#ifndef BALL_H
#define BALL_H

#include <future>
#include <mutex>
#include <thread>
#include "../BoundariesGuard.h"
#include "Swamp.h"


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


namespace assets
{

class Ball
{
public:
    Ball(point2d initialPosition, Direction initialDirection, double initialSpeed, BoundariesGuard bGuard, assets::Swamp swamp);
    ~Ball();

    void execute();
    static void stopBalls();
private:
    void movement();

    static std::mutex movement_mutex;
    static bool stopThread;
    static bool switcher;

    std::thread thread;
    const BoundariesGuard GUARD;
    const assets::Swamp SWAMP;

    point2d position;
    Direction direction;
    double speed;
};

} // namespace assets
#endif // BALL_H
