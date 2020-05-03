//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>

#define CONFIG_DIR "~/.fc"
#define CONFIG_NAME "config"

using namespace std;

enum PanelType {FileList, QuickView, Info, Tree};
enum ListMode {Full, Brief, Custom};
enum SortOrder {Unsorted, Name, Ext, Size, MTime, ATime, CTime};

class Config {

  public:
    Config();
    ~Config();

    void loadConfig();

    void forceColor();
    void forceBlack();
    bool isColour();

    void setSize(int row, int col);
    int getCols();
    int getRows();
    int getRowsInPanel();

    string getCurrentPath();
    void setCurrentPath(const string &sPath);
    void setRoot(bool isRoot);
    char getUserPromp();

    // left panel
    string getLeftPath();
    void setLeftPath(const string &path);
    PanelType getLeftPanelType();
    void setLeftPanelType(PanelType type);
    ListMode getLeftPanelMode();
    void setLeftPanelMode(ListMode mode);
    SortOrder getLeftPanelSort();
    void setLeftPanelSort(SortOrder sort);

    // right panel
    string getRightPath();
    void setRightPath(const string &path);
    PanelType getRightPanelType();
    void setRightPanelType(PanelType type);
    ListMode getRightPanelMode();
    void setRightPanelMode(ListMode mode);
    SortOrder getRightPanelSort();
    void setRightPanelSort(SortOrder sort);

    bool isShowDot();
    void setShowDot(bool f);
    bool isShowBorder();
    void setShowBorder(bool f);
    bool isShowStatus();
    void setShowStatus(bool f);
    bool isShowFree();
    void setShowFree(bool f);
    bool isShowTotal();
    void setShowTotal(bool f);
    bool isShowMenuBar();
    void setShowMenuBar(bool f);
    bool isShowKeyBar();
    void setShowKeyBar(bool f);
    bool isUseSi();
    void setUseSi(bool f);

//    confirmExit, confirmDelete, confirmOverride, confirmExecute;

    bool isInternalEdit();
    void setInternalEdit();
    void setEditor(const string &filename);
    string getEditor();

    bool isInternalView();
    void setInternalView();
    void setViewer(const string &filename);
    string getViewer();

private:
    string defaultPath;
    bool color, root;
    int rows, cols;

    // config
    string leftPath;
    string leftCustomMode;
    PanelType leftPanelType;
    ListMode leftPanelMode;
    SortOrder leftPanelSort;

    string rightPath;
    string rightCustomMode;
    PanelType rightPanelType;
    ListMode rightPanelMode;
    SortOrder rightPanelSort;

    bool internalEdit, internalView;
    string editorCmd, viewerCmd;

    int hotPanels;
    bool showDot, showBorder, showStatus, showFree, showTotal, showMenuBar, showKeyBar, useSi;
    bool confirmExit, confirmDelete, confirmOverride, confirmExecute;
};
