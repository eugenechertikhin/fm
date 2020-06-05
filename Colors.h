//
// Created by Eugene Chertikhin on 05.05.2020.
//

#pragma once

#include <ncurses.h>
#include "Directory.h"

#define WHITE_ON_BLUE  1
#define YELLOW_ON_BLUE 2
#define BLACK_ON_CYAN  3
#define WHITE_ON_GREEN 4
#define BLACK_ON_GREY 5
#define WHITE_ON_RED 6

class Colors {
public:
    static void initColors() {
        init_pair(WHITE_ON_BLUE, COLOR_WHITE, COLOR_BLUE);   // main panel color
        init_pair(YELLOW_ON_BLUE, COLOR_YELLOW, COLOR_BLUE); // highline text at main panel
        init_pair(BLACK_ON_CYAN, COLOR_BLACK, COLOR_CYAN);   // cursors
        init_pair(WHITE_ON_GREEN, COLOR_WHITE, COLOR_GREEN); // dialog window
        init_pair(BLACK_ON_GREY, COLOR_BLACK, COLOR_WHITE);  // dialog window
        init_pair(WHITE_ON_RED, COLOR_WHITE, COLOR_RED);     // error/notification window

        // colorText, colorBackground, colorDirectory, colorSelection, colorFile, colorExeFile, colorArchive, colorLink, colorSocket, colorBroken
        // colorMenuText, colorMenuBackground, colorMenuInput, colorMenuSelection, colorMenuHot
        // warningMenuText, warningMenuBackground, warningMenuSelection, warningMenuHot
    }

    static int getStyleForFileEntry(FileType f) {
        int s = 0;

        if (f == directory)
            s = A_BOLD;

        // todo coloring

        return s;
    }
};
