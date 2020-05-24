//
// Created by Eugene Chertikhin on 13.05.2020.
//

#include "WindowView.h"
#include "Colors.h"
#include "Utils.h"

WindowView::WindowView(std::string fileName) {
    Colors::initColors();

    keyBar = new std::vector<std::string>;
    keyBar->push_back("Help");
    keyBar->push_back("Unwrap");
    keyBar->push_back("Quit");
    keyBar->push_back("Hex");
    keyBar->push_back("");
    keyBar->push_back("Edit");
    keyBar->push_back("Find");
    keyBar->push_back("");
    keyBar->push_back("Code");
    keyBar->push_back("Quit");

    file.open(fileName.c_str(), std::fstream::ate);
    if (!file.is_open())
        throw std::runtime_error("can't open file for view");
    e = file.tellg();   // end of file
    file.seekg(0); // move to begin of file

    this->fileName = fileName;
    pos = 0;
    lines.clear();
    lines.push_back(file.tellg());
}

WindowView::~WindowView() {
    file.close();
    delete keyBar;
}

void WindowView::draw(int y, int x, int r, int c, bool colour) {
    WINDOW *win = newwin(r, c, y, x);
    box(win, 0, 0);
    if (colour > 0)
        wbkgd(win, COLOR_PAIR(colour));

    // print filename at the header
    mvwprintw(win, 0, 2, " %s ", fileName.c_str());
    wrefresh(win);

    move(r, 0);
    clrtoeol();
    showKeyBar(r, keyBar);

    rows = r-2;
    cols = c-2;
    content = newwin(rows, cols, y+1, x+1);
    if (colour > 0)
        wbkgd(content, COLOR_PAIR(colour));

    // print file content for current window
    readFile();
    wrefresh(content);

    // read keypressed
    bool ret = false;
    while (!ret) {
        int ch = mvgetch(0,c-1);
        switch (ch) {
            case KEY_F(1):
                break;
            case 'q':
            case 'Q':
            case 27: // ESC
            case KEY_F(3):
            case KEY_F(10):
                ret = true;
                break;
            case KEY_UP:
                if (pos > 0)
                    pos--;
                readFile();
                break;
            case KEY_DOWN:
                if (pos+rows < lines.size())
                    pos++;
                readFile();
                break;
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
                break;
            case 'G':
                break;
            case ' ':
                if (lines.size() - pos > rows-1)
                    pos+= rows-2;
                readFile();
                break;
        }
        wrefresh(content);
    }
    delwin(content);
    delwin(win);
}

void WindowView::readFile() {
    std::string line;
    file.seekg(lines.at(pos));
    for (int i = 1; i < rows+1; i++) {
        if (file.tellg() != e) {
            std::getline(file, line);
            util::Utils::paddingRight(&line, cols);
            mvwprintw(content, i-1, 0, line.c_str());
            if (pos + i + 1 > lines.size())
                lines.push_back(file.tellg());
        } else {
            // clear last line in case of scroll
            if (i < rows+1) {
                line = "";
                util::Utils::paddingRight(&line, cols);
            }
            mvwprintw(content, i-1, 0, line.c_str());
        }
    }
}
