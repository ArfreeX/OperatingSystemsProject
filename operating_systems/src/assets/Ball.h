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

    static void stopBalls();

    void execute();
    void lockThread();
    void unlockThread();

private:
    void movement();
    void drawBall(point2d oldPosition);
    void handleSwampTrespass();
    void positionChange();

    static std::mutex ballMutex;
    static std::atomic<bool> stopThread;
    static std::weak_ptr<Ball> lockedBall;
    static Ball* lockedBallPtr;

    std::thread thread;

    const BoundariesGuard GUARD;
    const assets::Swamp SWAMP;

    uint8_t swampTrespassCounter = 0;
    bool trespassingSwamp = false;
    bool threadLocked = false;
    point2d position;
    Direction direction;
    double speed;
};

} // namespace assets
#endif // BALL_H
