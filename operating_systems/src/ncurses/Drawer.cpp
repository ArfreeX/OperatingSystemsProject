#include "Drawer.h"
#include <ncurses.h>
#include <mutex>

namespace  ncurses
{

Drawer::Drawer()
{
    initscr();
    curs_set(0);
    cbreak();
}


Drawer::~Drawer()
{
    endwin();
}


void Drawer::controlInput(bool &stopProgram, point2d leftCorner, std::pair<size_t, size_t> sizes)
{
    while(getch() != 'q')
    {
        erase();
        Drawer::drawPitch(leftCorner, sizes);
    }
    stopProgram = true;
    assets::Ball::stopBalls();
}


void Drawer::drawPitch(point2d leftCorner, std::pair<size_t, size_t> sizes)
{
    for(size_t i = leftCorner.first + 1; i < leftCorner.first + sizes.first + 1; i++)
    {
        mvprintw(leftCorner.second, i, "_");
        mvprintw(leftCorner.second + sizes.second + 1, i, "_");
    }

    for(size_t i = leftCorner.second + 1; i < leftCorner.second + sizes.second + 2; i++)
    {
        mvprintw(i, leftCorner.first, "|");
        mvprintw(i, leftCorner.first + sizes.first + 1, "|");
    }
    refresh();
}


void Drawer::drawBall(point2d oldPosition, point2d newPosition)
{
    mvprintw(oldPosition.second, oldPosition.first, " ");
    mvprintw(newPosition.second, newPosition.first, "O");
    refresh();
}

}  // namespace ncurses
