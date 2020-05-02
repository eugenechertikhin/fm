//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>
#include <ncurses.h>
#include <panel.h>
#include "Config.h"
#include "Directory.h"

class Workspace {
public:
    Workspace(Config *pConfig);

    void show();

private:
    Config *config;

    WINDOW *leftWindow;
    PANEL *leftPanel;
    int leftFilesOffset;
    Directory *leftDir;

    WINDOW *rightWindow;
    PANEL *rightPanel;
    int rightFilesOffset;
    Directory *rightDir;

    PANEL *currentPanel;
    string cmd;
    string commandString;

    int selection;

    WINDOW *createWindow(int y, int x, int rows, int cols, int colour);
    void fillWindow(WINDOW *win, PanelType type, ListMode mode, const string &path, bool active);
    void printFiles(WINDOW *win, const string &path, SortOrder sortOrder, ListMode listMode);

};
