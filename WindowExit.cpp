//
// Created by Eugene Chertikhin on 05.05.2020.
//

#include "WindowExit.h"
#include "Colors.h"

WindowExit::WindowExit() {
    Colors::initColors();
}

WindowExit::~WindowExit() {
    delwin(win);
}

bool WindowExit::draw(int y, int x, int rows, int cols, int colour) {
    win = newwin(rows, cols, y, x);
    box(win, 0, 0);
    if (colour != 0)
        wbkgd(win, COLOR_PAIR(colour));

    wattron(win, COLOR_PAIR(colour));
    mvwprintw(win, rows / 2 - 2, cols / 2 - 10, " Exit. Are you sure ? ");
    mvwprintw(win, rows / 2, cols / 2 - 7, "Yes");
    mvwprintw(win, rows / 2, cols / 2 + 7, "No");
    wattroff(win, COLOR_PAIR(colour));

    wrefresh(win);

    bool ex = false, ret = false;
    while (!ex) {
        int c = mvgetch(rows / 2, cols / 2 - 5);
        switch (c) {
            case 'y':
            case 'Y':
                ret = true;
                ex = true;
                break;
            case 'n':
            case 'N':
                ret = false;
                ex =  true;
                break;
        }
        wrefresh(win);
    }

    return ret;
}

