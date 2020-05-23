//
// Created by Eugene Chertikhin on 13.05.2020.
//

#pragma once

#include <iostream>
#include <fstream>
#include <ncurses.h>
#include "Window.h"

// throw(std::string)
class WindowView: public Window {
public:
    WindowView(std::string fileName);
    ~WindowView();

    void draw(int y, int x, int rows, int cols, bool colour);
    void readFile();

private:
    std::string fileName;
    std::ifstream file;
    int rows,cols;
    int pos;
    std::ifstream::streampos e;
    std::vector<std::ifstream::streampos> lines;

    WINDOW *content;
};
