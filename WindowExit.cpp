//
// Created by Eugene Chertikhin on 05.05.2020.
//

#include "WindowExit.h"
#include "Colors.h"

WindowExit::WindowExit(int y, int x, int r, int c) {
    Colors::initColors();
    startx = x - c/2;
    starty = y - r/2;
    rows = r;
    cols = c;
}

WindowExit::~WindowExit() {
    delwin(win);
}

bool WindowExit::draw(int colour) {
    this->colour = colour;
    win = newwin(rows, cols, starty, startx);
    box(win, 0, 0);
    if (colour != 0)
        wbkgd(win, COLOR_PAIR(colour));

    mvwprintw(win, 0, 2, " Exit ");
    mvwprintw(win, 1, 2, "Are you really want to leave File Manager?");
    // keys
    Keys *Yes = new Keys(3, cols/4, " Yes ", 1);
    Keys *No = new Keys(3, cols/4*3, " No ", 0);
    No->setNext(Yes);
    Yes->setNext(No);
    Keys *current = Yes;

    mvwprintw(win, Yes->getY(), Yes->getX(), Yes->getLabel().c_str());
    mvwprintw(win, No->getY(), No->getX(), No->getLabel().c_str());
    showCursor(current);
    wrefresh(win);

    bool ex = false, ret = false;
    while (!ex) {
        int c = mvwgetch(win, current->getY(), current->getX() + 1);
        // debug
        //mvwprintw(win, 0, 15, "%d=%s", c, keyname(c));

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
            case 68: // KEY_LEFT
                hideCursor(current);
                current = current->getNext();
                showCursor(current);
                break;
            case 67: // KEY_RIGHT
                hideCursor(current);
                current = current->getNext();
                showCursor(current);
                break;
            case 9: // TAB
                hideCursor(current);
                current = current->getNext();
                showCursor(current);
                break;
            case 10: { // enter key
                    if (current->getStatus())
                        ret = true;
                    ex = true;
                }
            break;
        }
        wrefresh(win);
    }

    return ret;
}

void WindowExit::hideCursor(Keys *k) {
    mvwchgat(win, k->getY(), k->getX(), k->getLabel().size(), A_COLOR, colour, NULL);
}

void WindowExit::showCursor(Keys *k) {
    mvwchgat(win, k->getY(), k->getX(), k->getLabel().size(), A_COLOR, WHITE_ON_GREEN, NULL);
}
