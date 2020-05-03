//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>

#define CONFIG_DIR "~/.fc"
#define CONFIG_NAME "config"

enum PanelType {FileList, QuickView, Info, Tree};
enum ListMode  {Full, Brief, Custom};
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

    std::string getCurrentPath();
    void setCurrentPath(const std::string &sPath);
    void setRoot(bool isRoot);
    char getUserPromp();

    // left panel
    std::string getLeftPath();
    void setLeftPath(const std::string &path);
    std::string getLeftCustomMode();
    void setLeftCustomMode(std::string custom);
    PanelType getLeftPanelType();
    void setLeftPanelType(PanelType type);
    ListMode getLeftPanelMode();
    void setLeftPanelMode(ListMode mode);
    SortOrder getLeftPanelSort();
    void setLeftPanelSort(SortOrder sort);

    // right panel
    std::string getRightPath();
    void setRightPath(const std::string &path);
    std::string getRightCustomMode();
    void setRightCustomMode(std::string custom);
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
    void setEditor(const std::string &filename);
    std::string getEditor();

    bool isInternalView();
    void setInternalView();
    void setViewer(const std::string &filename);
    std::string getViewer();

private:
    std::string defaultPath;
    bool color, root;
    int rows, cols;

    // config
    std::string leftPath;
    std::string leftCustomMode;
    PanelType leftPanelType;
    ListMode leftPanelMode;
    SortOrder leftPanelSort;

    std::string rightPath;
    std::string rightCustomMode;
    PanelType rightPanelType;
    ListMode rightPanelMode;
    SortOrder rightPanelSort;

    bool internalEdit, internalView;
    std::string editorCmd, viewerCmd;

    int hotPanels;
    bool showDot, showBorder, showStatus, showFree, showTotal, showMenuBar, showKeyBar, useSi;
    bool confirmExit, confirmDelete, confirmOverride, confirmExecute;
};
