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
    bool leftRight;
//    std::string path;
    Directory *dir;
    int totalFiles;
    int cursorLengh;
    int position;
    int offset;
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
    std::string cmd;
    std::string commandString;

    std::vector<std::string> *leftCustomMode;
    std::vector<std::string> *rightCustomMode;

    WINDOW *createWindow(int y, int x, int rows, int cols, int colour);
    void fillWindow(WINDOW *win, PanelType type, ListMode mode, std::vector<std::string> *custom);
    int printFiles(WINDOW *win, Directory *dir, SortOrder sortOrder, ListMode listMode, int cursorLengh, int offset);
};
