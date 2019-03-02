#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <functional>
#include <chrono>
#include <mutex>
#include <ncurses.h>
#include "Ball.h"

int n = 80, m = 40;




bool boundariesCrossed(std::pair<int, int> position)
{
    return position.first <= 5 or position.first >= n or position.second <= 5 or position.second >= m;
}

void drawBall(std::pair<int, int> oldPosition, std::pair<int, int> position)
{
    mvprintw(oldPosition.second, oldPosition.first, " ");
    mvprintw(position.second, position.first, "O");
    refresh();
}




void drawPitch(int width, int height)
{
    for(int i = 5; i < 5 + width - 1; i++)
    {
        mvprintw(5, i, "x");
        mvprintw(5 + height - 1, i, "x");
    }

    for(int i = 5; i < 5 + height - 1; i++)
    {
        mvprintw(i, 5, "x");
        mvprintw(i, 5 + width - 1, "x");
    }
    refresh();
}
Direction randomDirection()
{
    return Direction(rand() % Direction::LAST_ELEMENT);
}
int main()
{
    int width, height;

    std::srand(123);
    std::cout << "Wprowadz rozmiary boiska. \n[x] = ";
    std::cin >> width;
    n  = width;
    std::cout << "\n[y] = ";
    std::cin >> height;
    m = height;
    initscr();
    curs_set(0);
    cbreak();

    drawPitch(width, height);

    while(true)
    {
        std::thread ballMovementThread(movement, std::pair<int, int>(10,10), randomDirection());
        ballMovementThread.detach();
        std::this_thread::sleep_for( std::chrono::seconds(10));
        refresh();
    }
    endwin();
    return 0;
}
