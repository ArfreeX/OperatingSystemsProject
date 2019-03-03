//#include <mutex>
#include "Ball.h"
#include "ncurses/Drawer.h"


Ball::Ball(std::pair<size_t, size_t> leftCorner, std::pair<size_t, size_t> sizes,
           BoundariesGuard bGuard, float startingSpeed)
    : bGuard(bGuard)
{
    position = drawStartingPosition(leftCorner, sizes);
    stopThread = false;
    speed = 1000.0 / startingSpeed;
}


Ball::~Ball()
{
    stopThread = true;
    thread.join();
}


void Ball::execute()
{
    thread = std::thread(&Ball::movement, this);
}

Ball::Direction Ball::drawDirection()
{
    return Direction(rand() % Direction::LAST_ELEMENT);
}


std::pair<size_t, size_t> Ball::drawStartingPosition(std::pair<size_t, size_t> leftCorner,
                                                     std::pair<size_t, size_t> sizes)
{
    return std::move(std::pair<size_t, size_t>(
                rand() % (sizes.first - 3) + leftCorner.first + 2,
                rand() % (sizes.second - 3) + leftCorner.second + 2));
}


void Ball::movement()
{
    Direction direction(drawDirection());

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

        //std::mutex mu;
        //std::cout << "[" << std::this_thread::get_id() << "] x: " << position.first  << ", y: " << position.second << "\n";
        //mu.lock();
        ncurses::Drawer::drawBall(oldPosition, position);
        //mu.unlock();
        std::this_thread::sleep_for( std::chrono::milliseconds(static_cast<unsigned>(speed)));
    }
}
