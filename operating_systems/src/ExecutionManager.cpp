#include <algorithm>
#include <random>
#include "helpers/Randomizer.h"
#include "ExecutionManager.h"


ExecutionManager::ExecutionManager(point2d pitch_corner, std::pair<size_t, size_t> pitch_edges, double spawn_ratio) :
     PITCH_CORNER(pitch_corner), BALL_SPAWN_RATIO(spawn_ratio), PITCH_EDGES(pitch_edges)
{
}


void ExecutionManager::execute()
{
    std::vector<std::unique_ptr<assets::Ball>> basket;
    bool stopProgram = false;
    const BoundariesGuard GUARD(PITCH_CORNER, PITCH_EDGES);
    const assets::Swamp SWAMP(PITCH_CORNER, PITCH_EDGES);

    std::thread(ncurses::Drawer::controlInput, std::ref(stopProgram), PITCH_CORNER, PITCH_EDGES).detach();
    ncurses::Drawer::drawPitch(PITCH_CORNER, PITCH_EDGES);

    while(not stopProgram)
    {
        double speed = helpers::Randomizer::drawSpeed();
        Direction direction = helpers::Randomizer::drawDirection();
        adjustSpeed(direction, speed);

        std::unique_ptr<assets::Ball> ballPtr = std::make_unique<assets::Ball>(helpers::Randomizer::drawPointInside(PITCH_CORNER, PITCH_EDGES),
                                                               direction, speed, GUARD, SWAMP);
        ballPtr->execute();
        basket.emplace_back(std::move(ballPtr));
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(round(1000.0 / BALL_SPAWN_RATIO))));
    }
}



void ExecutionManager::adjustSpeed(Direction direction, double &speed)
{
    if(direction == Direction::TOP_LEFT or direction == Direction::TOP_RIGHT
            or direction == Direction::BOTTOM_LEFT or direction == Direction::BOTTOM_RIGHT)
    {
        speed *= sqrt(2);
    }
}
