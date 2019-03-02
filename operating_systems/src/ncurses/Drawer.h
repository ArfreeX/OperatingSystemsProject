#ifndef DRAWER_H
#define DRAWER_H

#include <iostream>


namespace ncurses
{

class Drawer
{
public:
    Drawer();
    ~Drawer();
    void drawPitch(std::pair<size_t, size_t> leftCorner, std::pair<size_t, size_t> sizes);
    static void drawBall(std::pair<size_t, size_t> oldPosition, std::pair<size_t, size_t> newPosition);
};

} // namespace ncurses
#endif // DRAWER_H
