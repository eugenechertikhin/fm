//
// Created by Eugene Chertikhin on 16.05.2020.
//

#pragma once

#include <string>
#include <fstream>
#include <ncurses.h>

class WindowEdit {
public:
    WindowEdit();
    ~WindowEdit();

    void draw(int y, int x, int rows, int cols, bool colour, std::string fileName) throw(std::string);

private:
};
