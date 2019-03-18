#ifndef BALL_H
#define BALL_H

#include <atomic>
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
    void drawBall(point2d oldPosition);
    void handleSwampTrespass();
    bool checkIfThreadIsLocked();
    void positionChange();

    static std::mutex ballMutex;
    static std::atomic<bool> stopThread;
    static std::thread::id lockedThreadID;

    std::thread thread;

    const BoundariesGuard GUARD;
    const assets::Swamp SWAMP;

    uint8_t swampTrespassCounter = 0;
    bool trespassingSwamp = false;
    point2d position;
    Direction direction;
    double speed;
};

} // namespace assets
#endif // BALL_H
