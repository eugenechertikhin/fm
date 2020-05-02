//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>
#include <ncurses.h>
#include <panel.h>
#include "Config.h"

class Workspace {
public:
    Workspace(Config *pConfig);

    void fillWindow(WINDOW *win, PanelType type, ListMode mode, const string &path, bool active);
    void printFiles(WINDOW *win, const string &path);

    void show();

private:
    Config *config;
    WINDOW *leftWindow;
    PANEL *leftPanel;
    WINDOW *rightWindow;
    PANEL *rightPanel;
    PANEL *currentPanel;
    string cmd;
    string commandString;

    WINDOW *createWindow(int y, int x, int rows, int cols, int colour);
};
