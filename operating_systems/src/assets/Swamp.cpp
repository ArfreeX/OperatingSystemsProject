#include "../helpers/Randomizer.h"
#include "../ncurses/Drawer.h"
#include "Swamp.h"

namespace assets
{

Swamp::Swamp(point2d pitchCorner, std::pair<size_t, size_t> pitchEdges)
    : PITCH_CORNER(pitchCorner), PITCH_EDGES(pitchEdges)
{
    spawnSwamp();
}

// TODO: Swamp should be like 5-10% of whole area, not more
void Swamp::spawnSwamp()
{
    double percentOfSwampAreaInPitch = 10;
    swampEdges = helpers::Randomizer::drawPercentOfArea(PITCH_EDGES, percentOfSwampAreaInPitch);
    swampCorner = helpers::Randomizer::drawPointInside(PITCH_CORNER, std::make_pair<size_t, size_t>(
                                                           PITCH_EDGES.first - swampEdges.first,
                                                           PITCH_EDGES.second - swampEdges.second));
    ncurses::Drawer::drawPitch(swampCorner, swampEdges);
}


void Swamp::redrawSwamp() const
{
    ncurses::Drawer::drawSwamp(swampCorner, swampEdges);
}


bool Swamp::trespassingSwamp(point2d position) const
{
    size_t leftCornerX = swampCorner.first + 1;
    size_t rightCornerX = leftCornerX + swampEdges.first - 1;
    size_t topCornerY = swampCorner.second + 1;
    size_t bottomCornerY = topCornerY + swampEdges.second - 1;

    if((position.first >= leftCornerX and position.first <= rightCornerX)
            and (position.second >= topCornerY && position.second <= bottomCornerY))
    {
        return true;
    }
    return false;
}

} // namespace assets
