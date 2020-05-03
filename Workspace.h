//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>
#include <ncurses.h>
#include <panel.h>
#include "Config.h"
#include "Directory.h"

typedef struct _PANEL_DATA {
    // left ? right
    string path;
    Directory *dir;
    int position;
    PANEL *next;
}PANEL_DATA;

class Workspace {
public:
    Workspace(Config *pConfig);
    ~Workspace();

    void show();

private:
    Config *config;

    int leftFilesOffset;
    int rightFilesOffset;

    PANEL *currentPanel;
    string cmd;
    string commandString;

    WINDOW *createWindow(int y, int x, int rows, int cols, int colour);
    void fillWindow(WINDOW *win, PanelType type, ListMode mode);
    void printFiles(WINDOW *win, Directory *dir, SortOrder sortOrder, ListMode listMode);

};
