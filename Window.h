//
// Created by Eugene Chertikhin on 05.05.2020.
//

#pragma once

#include <string>
#include <ncurses.h>

class Window {
public:
    Window();
    ~Window();

    void draw(int y, int x, int rows, int cols, int colour);
    WINDOW *get();

private:
    WINDOW *win;
};

