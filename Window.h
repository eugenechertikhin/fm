//
// Created by Eugene Chertikhin on 24.05.2020.
//

#pragma once

#include <vector>
#include <string>
#include <ncurses.h>
#include "Colors.h"
#include "Utils.h"

#define KEYBAR_SIZE 6

class Window {
protected:
    std::vector<std::string> *keyBar;

    void showKeyBar(int y, std::vector<std::string> *keyBar) {
        move(y, 0);
        clrtoeol();
        for (int i=0; i < keyBar->size(); i++) {
            mvprintw(y, i*(KEYBAR_SIZE+2), "%d", i+1);
            attron(COLOR_PAIR(BLACK_ON_CYAN));
            std::string _s = keyBar->at(i);
            util::Utils::paddingRight(&_s, KEYBAR_SIZE);
            i >= 9 ? mvprintw(y, i*(KEYBAR_SIZE+2)+2, _s.c_str()) : mvprintw(y, i*(KEYBAR_SIZE+2)+1, _s.c_str());
            attroff(COLOR_PAIR(BLACK_ON_CYAN));
        }
    }
};
