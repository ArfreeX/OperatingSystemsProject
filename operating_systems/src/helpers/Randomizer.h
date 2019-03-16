#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>
#include "../assets/Ball.h"

namespace helpers
{

class Randomizer
{
public:
    Randomizer();

    static double drawSpeed();
    static Direction drawDirection();
    static point2d drawPointInside(point2d hookPoint, std::pair<size_t, size_t> boundaries);
    static std::pair<size_t, size_t> drawPercentOfArea(std::pair<size_t, size_t> areaEdges, double percentOfArea);
private:
    static std::random_device randomGenerator;
};

} // namespace helpers
#endif // RANDOMIZER_H
