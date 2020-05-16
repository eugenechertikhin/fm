//
// Created by Eugene Chertikhin on 16.05.2020.
//

#include "WindowEdit.h"
#include "Colors.h"
#include "KeyBar.h"

WindowEdit::WindowEdit() {
    Colors::initColors();
}

WindowEdit::~WindowEdit() {
}

void WindowEdit::draw(int y, int x, int rows, int cols, bool colour, std::string fileName) throw(std::string) {
    // open and read file
    std::ifstream file;
    file.open(fileName.c_str());
    if (!file)
        throw std::runtime_error("can't open file");

    WINDOW *win = newwin(rows, cols, y, x);
    box(win, 0, 0);
    if (colour > 0)
        wbkgd(win, COLOR_PAIR(colour));

    // print filename at the header
    mvwprintw(win, 0, 2, " %s ", fileName.c_str());
    wrefresh(win);

    WINDOW *content = newwin(rows-2, cols-2, y+1, x+1);
    if (colour > 0)
        wbkgd(content, COLOR_PAIR(colour));


    std::string line;
    int i = 0;
    while (getline(file, line) && i < rows-2) {
        mvwprintw(content, 1+i, 1, line.c_str());
        i++;
    }

    wrefresh(content);

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
                wrefresh(win);
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
        wrefresh(content);
    }

    file.close();
    delwin(content);
    delwin(win);
}
