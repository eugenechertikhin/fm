//
// Created by Eugene Chertikhin on 06.06.2020.
//

#pragma once

#include <string>
#include <ncurses.h>
#include "Keys.h"

class WindowCopy {
public:
    WindowCopy(int y, int x, int r, int c);
    ~WindowCopy();

    bool draw(int colour);

    void showCursor(Keys *k);
    void hideCursor(Keys *k);

private:
    WINDOW *win;
    int colour;
    int startx, starty;
    int rows, cols;
};
