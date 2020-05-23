//
// Created by Eugene Chertikhin on 23.05.2020.
//

#pragma once

#include <string>
#include <ncurses.h>
#include "Colors.h"

class WindowHelp {
public:
    WindowHelp(int y, int x, int r, int c);
    ~WindowHelp();

    void draw(int colour);

private:
    WINDOW *win;
    int colour;
    int startx, starty;
    int rows, cols;

    std::string text = "a "
            " +---              |\\  /|\n"
            " |      |          | \\/ |\n"
            "|--  . |   +---   |    |\n"
            "|   |  |  +-      |    |\n"
            "|   |  |  +---    |    | a n a g e r\n";
};
