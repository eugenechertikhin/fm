//
// Created by Eugene Chertikhin on 13.05.2020.
//

#include "WindowView.h"
#include "Colors.h"
#include "KeyBar.h"

WindowView::WindowView() {
    Colors::initColors();
}

WindowView::~WindowView() {
    delwin(win);
}

void WindowView::draw(int y, int x, int rows, int cols, bool colour, std::string fileName) {
    win = newwin(rows, cols, y, x);
    box(win, 0, 0);
    if (colour != 0)
        wbkgd(win, COLOR_PAIR(colour));

    mvwprintw(win, 0, 2, " %s ", fileName.c_str());
    wrefresh(win);

    // read keypressed
    bool ret = false;
    while (!ret) {
        int c = mvgetch(0,cols-1);
        switch (c) {
            // functional
            case KEY_F(1):
                break;
            case KEY_F(3):
            case KEY_F(10):
                ret = true;
                break;
            case KEY_UP:
                break;
            case KEY_DOWN:
                break;
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
                break;
            default:
                break;
        }
        wrefresh(win);
    }
}
