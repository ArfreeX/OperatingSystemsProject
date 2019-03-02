#include "Ball.h"

Ball::Ball(std::pair<int, int> startingPosition, unsigned startingSpeed)
    : position(startingPosition), speed(startingSpeed)
{
    movement(drawDirection());
}


void Ball::movement(Direction direction)
{
    while(true)
    {
        std::pair<int, int> oldPosition(position);

        switch(direction)
        {
        case Direction::LEFT:
            if(boundariesCrossed(position))
            {
                direction = Direction::RIGHT;
                position.first++;
            }
            else
            {
                position.first--;
            }
            break;

        case Direction::TOP_LEFT:
            if(boundariesCrossed(position))
            {
                direction = Direction::BOTTOM_RIGHT;
                position.first++;
                position.second--;
            }
            else
            {
                position.first--;
                position.second++;
            }
            break;

        case Direction::TOP:
            if(boundariesCrossed(position))
            {
                direction = Direction::BOTTOM;
                position.second--;
            }
            else
            {
                position.second++;
            }
            break;

        case Direction::TOP_RIGHT:
            if(boundariesCrossed(position))
            {
                direction = Direction::BOTTOM_LEFT;
                position.first--;
                position.second--;
            }
            else
            {
                position.first++;
                position.second++;
            }
            break;

        case Direction::RIGHT:
            if(boundariesCrossed(position))
            {
                direction = Direction::LEFT;
                position.first--;
            }
            else
            {
                position.first++;
            }
            break;

        case Direction::BOTTOM_RIGHT:
            if(boundariesCrossed(position))
            {
                direction = Direction::TOP_LEFT;
                position.first--;
                position.second++;
            }
            else
            {
                position.first++;
                position.second--;
            }
            break;

        case Direction::BOTTOM:
            if(boundariesCrossed(position))
            {
                direction = Direction::TOP;
                position.second++;
            }
            else
            {
                position.second--;
            }
            break;

        case Direction::BOTTOM_LEFT:
            if(boundariesCrossed(position))
            {
                direction = Direction::TOP_RIGHT;
                position.first++;
                position.second++;
            }
            else
            {
                position.first--;
                position.second--;
            }
            break;
        }
        std::mutex mu;
        mu.lock();
        //std::cout << "[" << std::this_thread::get_id() << "] x: " << position.first  << ", y: " << position.second << "\n";
        drawBall(oldPosition, position);
        mu.unlock();

        std::this_thread::sleep_for( std::chrono::milliseconds(300));
    }
}
