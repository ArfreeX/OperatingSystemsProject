#include <ncurses.h>
#include "../ncurses/Drawer.h"
#include "Ball.h"
#include <unistd.h>

namespace assets
{

std::mutex Ball::ballMutex;
std::atomic<bool> Ball::stopThread;
Ball* Ball::lockedBallPtr = nullptr;
std::condition_variable Ball::cv;
bool ready = true;

Ball::Ball(point2d initialPosition, Direction initialDirection, double initialSpeed, BoundariesGuard bGuard, assets::Swamp swamp)
    : SWAMP(swamp), GUARD(bGuard), position(initialPosition), direction(initialDirection)
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


void Ball::stopBalls() /*static*/
{
    if(!stopThread)
    {
        stopThread = true;
    }
}

// Bring these back later on
//void Ball::lockThread()
//{
//    threadLocked = true;
//}


//void Ball::unlockThread()
//{
//    threadLocked = false;
//}


void Ball::movement()
{
    point2d oldPosition;
    bool ballInSwamp = false;

    while(!stopThread)
    {
        oldPosition = position;
        if(!threadLocked)
        {
            while(ballInSwamp && SWAMP.trespassingSwamp(position))
            {
                oldPosition = position;
                positionChange();
                drawBall(oldPosition);
            }
            ballInSwamp = false;

            oldPosition = position;
            positionChange();
            handleSwampTrespass();
        }
        else
        {
            usleep(1000);
            ballInSwamp = true;
            std::unique_lock<std::mutex> lk(ballMutex);
            while(threadLocked)
            {
                usleep(1000);
                cv.wait(lk);
            }
        }

    drawBall(oldPosition);
    }
}


void Ball::drawBall(point2d oldPosition)
{
    std::this_thread::sleep_for( std::chrono::milliseconds(static_cast<unsigned>(speed)));
    std::lock_guard<std::mutex> guard(ballMutex);
    SWAMP.redrawSwamp();
    ncurses::Drawer::drawBall(oldPosition, position);
}


void Ball::handleSwampTrespass()
{
    if(SWAMP.trespassingSwamp(position))
    {
        swampTrespassCounter++;

        if(swampTrespassCounter == 2)
        {
            std::lock_guard<std::mutex> guard(ballMutex);

            swampTrespassCounter = 0;
            this->threadLocked = true;


            if(lockedBallPtr != nullptr)
            {
                lockedBallPtr->threadLocked = false;
                cv.notify_all();
            }
            lockedBallPtr = this;
        }
    }
}


void Ball::positionChange()
{
    CrossResult crossResult (GUARD.boundariesCrossed(position));

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
}


} // namespace assets
