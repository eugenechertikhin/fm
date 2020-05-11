//
// Created by Eugene Chertikhin on 05.05.2020.
//

#include "Window.h"
#include "Colors.h"

Window::Window() {
    Colors::initColors();
}

Window::~Window() {
    delwin(win);
}

WINDOW *Window::get() {
    return win;
}

void Window::draw(int y, int x, int rows, int cols, int colour) {
    win = newwin(rows, cols, y, x);
    box(win, 0, 0);
    if (colour != 0)
        wbkgd(win, COLOR_PAIR(colour));

    wattron(win, COLOR_PAIR(colour));
    mvwprintw(win, rows/2-2, cols/2-10, " Exit. Are you sure ? ");
    mvwprintw(win, rows/2, cols/2-7, "Yes");
    mvwprintw(win, rows/2, cols/2+7, "No");

    wrefresh(win);
}

