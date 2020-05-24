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
    FilePanel(Config *conf);
    ~FilePanel();

    void setNext(FilePanel *fp);
    FilePanel *getNext();

    void setPath(std::string path);
    std::string getPath();
    void setType(PanelType type);
    void setMode(ListMode mode, std::string params);
    void setSort(SortType sortType, bool sortOrder);

    void draw(int y, int x, int rows, int cols, bool colour);
    void printInside();
    void update();
    void clear();

    void hideCursor(bool p);
    void showCursor(bool p);

    void updateStatusLine();
    void updateFiles();
    void rescanDirectory();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void enter();

    FileEntry *getCurrentFile();

private:
    Config *config;
    int statusLine, topLine, keybar;

    void sortDirectory(std::vector<FileEntry *> *files);

    std::string path;
    PanelType type;
    ListMode mode;
    std::vector<std::string> *modeParams;
    SortType sortType;
    bool sortOrder; // true == asc

    int cols;
    int rows;
    bool colour;

    Directory *dir;
    std::vector<FileEntry *> *files;
    int pos;
    int offset;
    int cursorLengh;
    int filesCount;
    int rowsCount;

    WINDOW *win;
    FilePanel *next;
};