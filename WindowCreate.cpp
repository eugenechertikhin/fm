//
// Created by Eugene Chertikhin on 06.06.2020.
//

#include "WindowCreate.h"
#include "Colors.h"

WindowCreate::WindowCreate(int y, int x, int r, int c) {
    Colors::initColors();
    startx = x - c/2;
    starty = y - r/2;
    rows = r;
    cols = c;
}

WindowCreate::~WindowCreate() {
    delwin(win);
}

bool WindowCreate::draw(int colour) {
    this->colour = colour;
    win = newwin(rows, cols, starty, startx);
    box(win, 0, 0);
    if (colour != 0)
        wbkgd(win, COLOR_PAIR(colour));

    mvwprintw(win, 0, 2, " Create directory ");
    mvwprintw(win, 1, 2, "Directory name:");
    mvwprintw(win, 2, 2, "_");

    // keys
    Keys *Ok = new Keys(4, cols/4, " Ok ", 1);
    Keys *Cancel = new Keys(4, cols/4*3, " Cancel ", 0);
    Cancel->setNext(Ok);
    Ok->setNext(Cancel);
    Keys *current = Ok;

    mvwprintw(win, Ok->getY(), Ok->getX(), Ok->getLabel().c_str());
    mvwprintw(win, Cancel->getY(), Cancel->getX(), Cancel->getLabel().c_str());
    showCursor(current);
    wrefresh(win);

    bool exec = false, finish = false;
    while (!finish) {
        int c = mvwgetch(win, current->getY(), current->getX() + 1);

        switch (c) {
            case 'o':
            case 'O':
                exec = true;
                break;
            case 'c':
                finish =  true;
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
            case 10: // enter key
                if (current->getStatus())
                    exec = true;
                else
                    finish = true;
                break;
        }

        if (exec) {

        }
        wrefresh(win);
    }

    return 1;
}

void WindowCreate::showCursor(Keys *k) {
    mvwchgat(win, k->getY(), k->getX(), k->getLabel().size(), A_COLOR, WHITE_ON_GREEN, NULL);
}

void WindowCreate::hideCursor(Keys *k) {
    mvwchgat(win, k->getY(), k->getX(), k->getLabel().size(), A_COLOR, colour, NULL);
}