#ifndef BALL_H
#define BALL_H

#include <mutex>
#include <thread>


class Ball
{
public:
    Ball(std::pair<int, int> startingPosition, unsigned startingSpeed);

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

    void movement(Direction direction);
    Direction drawDirection();

    std::pair<int, int> position;
    unsigned speed;
};

#endif // BALL_H
