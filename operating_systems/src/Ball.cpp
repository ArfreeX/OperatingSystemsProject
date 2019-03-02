#include "Ball.h"
#include "ncurses/Drawer.h"


Ball::Ball(std::pair<size_t, size_t> startingPosition, BoundariesGuard bGuard, float startingSpeed)
    : bGuard(bGuard), position(startingPosition)
{
    speed = 1000.0 / startingSpeed;
    movement(Direction::LEFT);//drawDirection());
}


void Ball::movement(Direction direction)
{

    while(true)
    {
        std::pair<int, int> oldPosition(position);
        CrossResult crossResult(bGuard.boundariesCrossed(position));

        switch(direction)
        {
        case Direction::LEFT:
            if(crossResult != CrossResult::NOT_CROSSED)
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
            if(crossResult != CrossResult::NOT_CROSSED)
            {
                if(crossResult == CrossResult::CROSSED_VERTICALLY)
                {
                    direction = Direction::BOTTOM_RIGHT;
                    position.first--;
                    position.second--;
                }
                else
                {
                    direction = Direction::TOP_RIGHT;
                    position.first++;
                    position.second++;
                }
            }
            else
            {
                position.first--;
                position.second++;
            }
            break;

        case Direction::TOP:
            if(crossResult != CrossResult::NOT_CROSSED)
            {
                direction = Direction::BOTTOM;
                position.second++;
            }
            else
            {
                position.second--;
            }
            break;

        case Direction::TOP_RIGHT:
            if(crossResult != CrossResult::NOT_CROSSED)
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
            if(crossResult != CrossResult::NOT_CROSSED)
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
            if(crossResult != CrossResult::NOT_CROSSED)
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
            if(crossResult != CrossResult::NOT_CROSSED)
            {
                direction = Direction::TOP;
                position.second--;
            }
            else
            {
                position.second++;
            }
            break;

        case Direction::BOTTOM_LEFT:
            if(crossResult != CrossResult::NOT_CROSSED)
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
        ncurses::Drawer::drawBall(oldPosition, position);
        mu.unlock();

        std::this_thread::sleep_for( std::chrono::milliseconds(static_cast<unsigned>(speed)));
    }
}


Ball::Direction Ball::drawDirection()
{
    return Direction(rand() % Direction::LAST_ELEMENT);
}
