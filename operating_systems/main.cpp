#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <functional>
#include <chrono>
#include <mutex>

const int n = 80, m = 40;

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


bool boundariesCrossed(std::pair<int, int> position)
{
    return position.first <= 0 or position.first >= n or position.second <= 0 or position.second >= m;
}

void movement(std::pair<int, int> position, Direction direction)
{
    while(true)
    {
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
        std::cout << "[" << std::this_thread::get_id() << "] x: " << position.first  << ", y: " << position.second << "\n";
        mu.unlock();

        std::this_thread::sleep_for( std::chrono::milliseconds(300));
    }
}

Direction randomDirection()
{
    return Direction(rand() % Direction::LAST_ELEMENT);
}
int main()
{

    std::srand(123);

    while(true)
    {
        std::thread ballMovementThread(movement, std::pair<int, int>(10,20), randomDirection());
        ballMovementThread.detach();
        std::this_thread::sleep_for( std::chrono::seconds(10));
    }

    return 0;
}
