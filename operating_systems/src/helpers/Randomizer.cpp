#include "Randomizer.h"

namespace helpers
{

std::random_device Randomizer::randomGenerator;

Randomizer::Randomizer()
{
}


double Randomizer::drawSpeed()
{
    const int MIN_MOVES_PER_SECOND = 12;
    const int MAX_MOVES_PER_SECOND = 18;
    std::uniform_int_distribution<int> speed(MIN_MOVES_PER_SECOND, MAX_MOVES_PER_SECOND);

    return static_cast<int>(speed(randomGenerator));
}


Direction Randomizer::drawDirection()
{
    std::uniform_int_distribution<int> direction(0, (Direction::LAST_ELEMENT - 1));

    return Direction(direction(randomGenerator));
}


point2d Randomizer::drawPointInside(point2d hookPoint, std::pair<size_t, size_t> boundaries)
{
    std::uniform_int_distribution<int> positionX(hookPoint.first + 2, boundaries.first - 3);
    std::uniform_int_distribution<int> positionY(hookPoint.second + 2, boundaries.second - 3);

    return point2d(positionX(randomGenerator), positionY(randomGenerator));
}


} // namespace helpers
