//
// Created by Eugene Chertikhin on 05.05.2020.
//

#pragma once

#include <string>
#include <ncurses.h>
#include "Keys.h"

class WindowExit {
public:
    WindowExit(int y, int x, int r, int c);
    ~WindowExit();

    bool draw(int colour);

    void showCursor(Keys *k);
    void hideCursor(Keys *k);

private:
    WINDOW *win;
    int colour;
    int startx, starty;
    int rows, cols;
};

