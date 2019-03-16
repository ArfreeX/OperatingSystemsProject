#ifndef SWAMP_H
#define SWAMP_H

typedef std::pair<size_t, size_t> point2d;

namespace assets
{

class Swamp
{
public:
    Swamp(point2d pitchCorner, std::pair<size_t, size_t> pitchEdges);
    bool trespassingSwamp(point2d position) const;
    void redrawSwamp() const;

private:
    void spawnSwamp();

    const point2d PITCH_CORNER;
    const std::pair<size_t, size_t> PITCH_EDGES;

    point2d swampCorner;
    std::pair<size_t, size_t> swampEdges;
};

} // namespace assets
#endif // SWAMP_H
