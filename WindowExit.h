//
// Created by Eugene Chertikhin on 05.05.2020.
//

#pragma once

#include <string>
#include <ncurses.h>

class WindowExit {
public:
    WindowExit();
    ~WindowExit();

    bool draw(int y, int x, int rows, int cols, int colour);

private:
    WINDOW *win;
};

