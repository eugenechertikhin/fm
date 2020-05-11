//
// Created by Eugene Chertikhin on 05.05.2020.
//

#pragma once

#include <ncurses.h>

class Colors {
public:
    static void initColors() {
        init_pair(1, COLOR_WHITE, COLOR_BLUE);  // main panel color
        init_pair(2, COLOR_YELLOW, COLOR_BLUE); // highline text at main panel
        init_pair(3, COLOR_BLACK, COLOR_CYAN);  // cursors
        init_pair(4, COLOR_WHITE, COLOR_GREEN); // dialog window

        // colorText, colorBackground, colorDirectory, colorSelection, colorFile, colorExeFile, colorArchive, colorLink, colorSocket, colorBroken
        // colorMenuText, colorMenuBackground, colorMenuInput, colorMenuSelection, colorMenuHot
        // warningMenuText, warningMenuBackground, warningMenuSelection, warningMenuHot
    }
};