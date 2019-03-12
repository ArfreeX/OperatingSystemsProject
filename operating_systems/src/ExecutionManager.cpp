#include <algorithm>
#include <random>
#include "ExecutionManager.h"
#include "ncurses/Drawer.h"


ExecutionManager::ExecutionManager(point2d pitch_corner, std::pair<size_t, size_t> pitch_sizes, float spawn_ratio) :
    BALL_SPAWN_RATIO(spawn_ratio), PITCH_SIZES(pitch_sizes), PITCH_CORNER(pitch_corner)
{
}


void ExecutionManager::execute()
{
    std::vector<std::unique_ptr<Ball>> basket;
    bool stopProgram = false;
    const BoundariesGuard GUARD(PITCH_CORNER, PITCH_SIZES);
    std::thread(ncurses::Drawer::controlInput, std::ref(stopProgram), PITCH_CORNER, PITCH_SIZES).detach();

    while(not stopProgram)
    {
        float speed = drawInitialSpeed();
        Direction direction = drawInitialDirection();
        adjustSpeed(direction, speed);

        std::unique_ptr<Ball> ballPtr = std::make_unique<Ball>(drawInitialPosition(), direction, speed, GUARD);
        ballPtr->execute();
        basket.emplace_back(std::move(ballPtr));
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


point2d ExecutionManager::drawInitialPosition()
{
    std::random_device randomGenerator;
    std::uniform_int_distribution<int> positionX(PITCH_CORNER.first + 2, PITCH_SIZES.first - 3);
    std::uniform_int_distribution<int> positionY(PITCH_CORNER.second + 2, PITCH_SIZES.second - 3);

    return point2d(positionX(randomGenerator), positionY(randomGenerator));
}


void ExecutionManager::adjustSpeed(Direction direction, float &speed)
{
    if(direction == Direction::TOP_LEFT or direction == Direction::TOP_RIGHT
            or direction == Direction::BOTTOM_LEFT or direction == Direction::BOTTOM_RIGHT)
    {
        speed *= sqrt(2);
    }
}
