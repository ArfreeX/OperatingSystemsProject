#include <algorithm>
#include <random>
#include "ExecutionManager.h"


ExecutionManager::ExecutionManager()
{

}


void ExecutionManager::execute()
{
    std::vector<std::unique_ptr<Ball>> basket;
    size_t balls = 0;
    BoundariesGuard const GUARD(PITCH_CORNER, PITCH_SIZES);
    while(basket.size() < 5)
    {
        float speed = drawInitialSpeed();
        Direction direction = drawInitialDirection();
        if(direction == Direction::TOP_LEFT or direction == Direction::TOP_RIGHT
                or direction == Direction::BOTTOM_LEFT or direction == Direction::BOTTOM_RIGHT)
        {
            adjustSpeed(speed);
        }


        std::unique_ptr<Ball> ballPtr = std::make_unique<Ball>(PITCH_CORNER, PITCH_SIZES, GUARD, speed);
        ballPtr->execute();
        basket.emplace_back(std::move(ballPtr));
        balls++;

        std::this_thread::sleep_for( std::chrono::milliseconds(static_cast<int>(1000.0 / BALL_SPAWN_RATIO)));
    }
}


float ExecutionManager::drawInitialSpeed()
{
    std::random_device randomGenerator;
    std::uniform_int_distribution<int> speed(12, 18);

    return static_cast<int>(speed(randomGenerator));
}


Direction ExecutionManager::drawInitialDirection()
{
    std::random_device randomGenerator;
    std::uniform_int_distribution<int> direction(0, (Direction::LAST_ELEMENT - 1));

    return Direction(direction(randomGenerator));
}


std::pair<size_t, size_t> drawInitialPosition()
{
    std::random_device randomGenerator;
    std::uniform_int_distribution<int> positionX(PITCH_CORNER.first + 2, PITCH_SIZES.first - 3);
    std::uniform_int_distribution<int> positionY(PITCH_CORNER.second + 2, PITCH_SIZES.second - 3);

    return std::move(std::pair<size_t, size_t>(positionX(randomGenerator), positionY(randomGenerator)));
}

void ExecutionManager::adjustSpeed(float &speed)
{
        speed *= sqrt(2);
}
