#include "Ball.h"
#include "ncurses/Drawer.h"
#include <ncurses.h>


std::mutex Ball::movement_mutex;
bool Ball::stopThread = false;

Ball::Ball(point2d initialPosition, Direction initialDirection, double initialSpeed, BoundariesGuard bGuard)
    : bGuard(bGuard), position(initialPosition), direction(initialDirection)
{
    speed = 1000.0 / initialSpeed;
}


Ball::~Ball()
{
    if(!stopThread)
    {
        stopThread = true;
    }
    thread.join();
}


void Ball::execute()
{
    thread = std::thread(&Ball::movement, this);
}


void Ball::stopBalls()
{
    if(!stopThread)
    {
        stopThread = true;
    }
}


void Ball::movement()
{
    while(!stopThread)
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

        case Direction::TOP_LEFT:
            if(crossResult != CrossResult::NOT_CROSSED)
            {
                if(crossResult == CrossResult::CROSSED_CORNER)
                {
                    direction = Direction::BOTTOM_RIGHT;
                    position.first++;
                    position.second++;
                }
                else if(crossResult == CrossResult::CROSSED_HORIZONTALLY)
                {
                    direction = Direction::TOP_RIGHT;
                    position.first++;
                    position.second--;
                }
                else
                {
                    direction = Direction::BOTTOM_LEFT;
                    position.first--;
                    position.second++;
                }
            }
            else
            {
                position.first--;
                position.second--;
            }
            break;

        case Direction::TOP_RIGHT:
            if(crossResult != CrossResult::NOT_CROSSED)
            {
                if(crossResult == CrossResult::CROSSED_CORNER)
                {
                    direction = Direction::BOTTOM_LEFT;
                    position.first--;
                    position.second++;
                }
                else if(crossResult == CrossResult::CROSSED_HORIZONTALLY)
                {
                    direction = Direction::TOP_LEFT;
                    position.first--;
                    position.second--;
                }
                else
                {
                    direction = Direction::BOTTOM_RIGHT;
                    position.first++;
                    position.second++;
                }
            }
            else
            {
                position.first++;
                position.second--;
            }
            break;

        case Direction::BOTTOM_LEFT:
            if(crossResult != CrossResult::NOT_CROSSED)
            {
                if(crossResult == CrossResult::CROSSED_CORNER)
                {
                    direction = Direction::TOP_RIGHT;
                    position.first++;
                    position.second--;
                }
                else if(crossResult == CrossResult::CROSSED_HORIZONTALLY)
                {
                    direction = Direction::BOTTOM_RIGHT;
                    position.first++;
                    position.second++;
                }
                else
                {
                    direction = Direction::TOP_LEFT;
                    position.first--;
                    position.second--;
                }
            }
            else
            {
                position.first--;
                position.second++;
            }
            break;

        case Direction::BOTTOM_RIGHT:
            if(crossResult != CrossResult::NOT_CROSSED)
            {
                if(crossResult == CrossResult::CROSSED_CORNER)
                {
                    direction = Direction::TOP_LEFT;
                    position.first--;
                    position.second--;
                }
                else if(crossResult == CrossResult::CROSSED_HORIZONTALLY)
                {
                    direction = Direction::BOTTOM_LEFT;
                    position.first--;
                    position.second++;
                }
                else
                {
                    direction = Direction::TOP_RIGHT;
                    position.first++;
                    position.second--;
                }
            }
            else
            {
                position.first++;
                position.second++;
            }
            break;
        }

        std::this_thread::sleep_for( std::chrono::milliseconds(static_cast<unsigned>(speed)));
        std::lock_guard<std::mutex> guard(movement_mutex);
        ncurses::Drawer::drawBall(oldPosition, position);
    }
}
