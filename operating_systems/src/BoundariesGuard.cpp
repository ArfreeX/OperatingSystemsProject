#include "BoundariesGuard.h"

BoundariesGuard::BoundariesGuard(std::pair<size_t, size_t> leftCorner, std::pair<size_t, size_t> sizes)
    : cornerX(leftCorner.first), cornerY(leftCorner.second),
      width(sizes.first), height(sizes.second)
{

}
