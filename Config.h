//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>

#define CONFIG_DIR "~/.fc"
#define CONFIG_NAME "config"

using namespace std;

class Config {

  public:
    Config();
    ~Config();

    void loadConfig();

    void forceColor();

    void forceBlack();

    void setSize(int row, int col);
    bool isColour();

    int getRows();

    int getCols();

    char getUserPromp();

    bool isShowDot();

private:
    string defaultPath;
    bool color, root;
    int rows, cols;

    // config
    string leftPath, rightPath;
    bool internalEdit, internalView;
    string internalEditName, internalViewName;
    int hotPanels;
    bool showDot, showBorder, showStatus, showFree, showTotal, showMenuBar, showKeyBar, useSi;
    bool confirmExit, confirmDelete, confirmOverride, confirmExecute;

    // colorText, colorBackground, colorDirectory, colorSelection, colorFile, colorExeFile, colorArchive, colorLink, colorSocket, colorBroken
    // colorMenuText, colorMenuBackground, colorMenuInput, colorMenuSelection, colorMenuHot
    // warningMenuText, warningMenuBackground, warningMenuSelection, warningMenuHot

    // panel type
    // FileList, QuickView, QuickEdit, Info, Tree
    // ListMode: Full, Brief, Custom
    // Status string: name | size | permission

    // Sort order: unsorted, name, ext, size, mtime, atime, ctime | executable first
};
