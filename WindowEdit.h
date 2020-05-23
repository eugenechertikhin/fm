//
// Created by Eugene Chertikhin on 16.05.2020.
//

#pragma once

#include <fstream>
#include <ncurses.h>
#include "Window.h"

class WindowEdit: public Window {
public:
    WindowEdit();
    ~WindowEdit();

    void draw(int y, int x, int rows, int cols, bool colour, std::string fileName) throw(std::string);

private:
};
