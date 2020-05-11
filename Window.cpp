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

void Window::draw(int y, int x, int rows, int cols, bool colour) {
    win = newwin(rows, cols, y, x);
    box(win, 0, 0);
    if (colour)
        wbkgd(win, COLOR_PAIR(colour));

    wrefresh(win);
}
