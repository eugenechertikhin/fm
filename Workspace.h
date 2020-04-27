//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>
#include <ncurses.h>
#include <panel.h>
#include "Config.h"

using namespace std;

class Workspace {
public:
    Workspace(Config *pConfig);

    void show();

private:
    Config *config;
    WINDOW *leftWindow;
    PANEL *leftPanel;
    WINDOW *rightWindow;
    PANEL *rightPanel;
    PANEL *currentPanel;

    WINDOW *initWindow(int y, int x, int rows, int cols, int colour);
};
