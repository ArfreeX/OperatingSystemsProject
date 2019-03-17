#include "Randomizer.h"

namespace helpers
{


std::random_device Randomizer::randomGenerator;


Randomizer::Randomizer()
{
}


double Randomizer::drawSpeed() /*static*/
{
    const int MIN_MOVES_PER_SECOND = 3;
    const int MAX_MOVES_PER_SECOND = 5;
    std::uniform_int_distribution<int> speed(MIN_MOVES_PER_SECOND, MAX_MOVES_PER_SECOND);

    return static_cast<int>(speed(randomGenerator));
}


Direction Randomizer::drawDirection() /*static*/
{
    std::uniform_int_distribution<int> direction(0, (Direction::LAST_ELEMENT - 1));

    return Direction(direction(randomGenerator));
}


point2d Randomizer::drawPointInside(point2d hookPoint, std::pair<size_t, size_t> boundaries) /*static*/
{
    std::uniform_int_distribution<size_t> positionX(hookPoint.first + 2, boundaries.first - 3);
    std::uniform_int_distribution<size_t> positionY(hookPoint.second + 2, boundaries.second - 3);

    return point2d(positionX(randomGenerator), positionY(randomGenerator));
}


std::pair<size_t, size_t> Randomizer::drawPercentOfArea(std::pair<size_t, size_t> areaEdges, double percentOfArea) /*static*/
{
    size_t area = areaEdges.first * areaEdges.second;

    if(percentOfArea > 100)
    {
        percentOfArea = 100;
    }
    else if(percentOfArea <= 0)
    {
        percentOfArea = 1;
    }

    double newArea = round(area * (percentOfArea / 100.0));

    return std::make_pair<size_t, size_t>(static_cast<size_t>(round(sqrt(newArea))),
                                          static_cast<size_t>(round(sqrt(newArea))));
}


} // namespace helpers
