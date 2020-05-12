//
// Created by Eugene Chertikhin on 13.05.2020.
//

#pragma once

#include <string>
#include <ncurses.h>

class WindowView {
public:
    WindowView();
    ~WindowView();

    void draw(int y, int x, int rows, int cols, bool colour, std::string fileName);

private:
    WINDOW *win;
};
