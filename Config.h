//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>

#define CONFIG_DIR "~/.fc"
#define CONFIG_NAME "config"

using namespace std;

enum PanelType {FileList, QuckView, Info, Tree};
enum ListMode {Full, Brief, Custom};
enum SortOrder {Unsorted, Name, Ext, Size, MTime, ATime, CTime};
// Status string: name | size | permission

class Config {

  public:
    Config();
    ~Config();

    void loadConfig();

    void forceColor();
    void forceBlack();
    bool isColour();

    void setSize(int row, int col);
    int getRows();
    int getCols();

    void setCurrentPath(string sPath);
    string getCurrentPath();
    char getUserPromp();

    string getLeftPath();
    PanelType getLeftPanelType();
    void setLeftPanelType(PanelType type);
    ListMode getLeftPanelMode();
    void setLeftPanelMode(ListMode mode);

    string getRightPath();
    PanelType getRightPanelType();
    void setRightPanelType(PanelType type);
    ListMode getRightPanelMode();
    void setRightPanelMode(ListMode mode);

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
    void setEditor(string filename);
    string getEditor();

    bool isInternalView();
    void setInternalView();
    void setViewer(string filename);
    string getViewer();

private:
    string defaultPath;
    bool color, root;
    int rows, cols;

    // config
    string leftPath;
    PanelType leftPanelType;
    ListMode leftPanelMode;

    string rightPath;
    PanelType rightPanelType;
    ListMode rightPanelMode;

    bool internalEdit, internalView;
    string editorCmd, viewerCmd;

    int hotPanels;
    bool showDot, showBorder, showStatus, showFree, showTotal, showMenuBar, showKeyBar, useSi;
    bool confirmExit, confirmDelete, confirmOverride, confirmExecute;
};
