//
// Created by Eugene Chertikhin on 06.06.2020.
//

#pragma once

#include <string>
#include <ncurses.h>
#include "Keys.h"

class WindowMove {
public:
    WindowMove(int y, int x, int r, int c);
    ~WindowMove();

    bool draw(int colour);

    void showCursor(Keys *k);
    void hideCursor(Keys *k);

private:
    WINDOW *win;
    int colour;
    int startx, starty;
    int rows, cols;
};
