//
// Created by Eugene Chertikhin on 23.05.2020.
//

#include "WindowHelp.h"

WindowHelp::WindowHelp(int y, int x, int r, int c) {
    Colors::initColors();
    startx = x;
    starty = y;
    rows = r;
    cols = c;
}

WindowHelp::~WindowHelp() {
}

void WindowHelp::draw(int colour) {
    this->colour = colour;
    WINDOW *w = newwin(rows, cols, starty, startx);
    box(w, 0, 0);
    if (colour != 0)
        wbkgd(w, COLOR_PAIR(colour));
    mvwprintw(w, 0, 2, " Help ");
    wrefresh(w);

    win = newwin(rows-2, cols-2, starty+1, startx+1);
    if (colour != 0)
        wbkgd(win, COLOR_PAIR(colour));
    mvwprintw(win, 1, 1, text.c_str());

    wrefresh(win);

    bool ex = false;
    while (!ex) {
        int c = mvgetch(0, 0);
        // debug
        mvwprintw(win, 0, 15, "%d=%s", c, keyname(c));

        switch (c) {
            case 'q':
            case 'Q':
            case KEY_F(10):
            case 27: // ESC
                ex = true;
                break;
        }
        wrefresh(win);
    }

    delwin(win);
    delwin(w);
    return;
}
