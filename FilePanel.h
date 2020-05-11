//
// Created by Eugene Chertikhin on 04.05.2020.
//

#pragma once

#include <string>
#include <vector>
#include <ncurses.h>
#include <sys/statvfs.h>

#include "Utils.h"
#include "Config.h"
#include "Directory.h"

class FilePanel {

public:
    FilePanel();
    ~FilePanel();

    void setNext(FilePanel *fp);
    FilePanel *getNext();

    void setPath(std::string path);
    std::string getPath();
    void setType(PanelType type);
    void setMode(ListMode mode, std::string params);
    void setSort(SortType sortType, bool sortOrder);
    void setShowDot(bool showDot);

    void draw(int y, int x, int rows, int cols, bool colour);
    void redraw();

    void hideCursor();
    void showCursor();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

private:
    void sortDirectory(std::vector<FileEntry *> *files);

    std::string path;
    PanelType type;
    ListMode mode;
    std::vector<std::string> *modeParams;
    SortType sortType;
    bool sortOrder; // true == asc
    bool showDot, showBorder, showStatus, showFree, showTotal, useSi;

    Directory *directory;
    std::vector<FileEntry *> *files;
    int pos;
    int offset;
    int cursorLengh;

    WINDOW *win;
    FilePanel *next;
};