#ifndef DRAWER_H
#define DRAWER_H

#include <iostream>
#include "../assets/Ball.h"


namespace ncurses
{

class Drawer
{
public:
    Drawer();
    ~Drawer();

    static void drawPitch(point2d leftCorner, std::pair<size_t, size_t> sizes);
    static void controlInput(bool &stopProgram, point2d leftCorner, std::pair<size_t, size_t> sizes);
    static void drawBall(point2d oldPosition, point2d newPosition);
};

} // namespace ncurses
#endif // DRAWER_H
