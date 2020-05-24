//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "Simpleini/Simpleini.h"

#define CONFIG_PATH "/.fm_"
#define CONFIG_NAME "config"
#define HISTORY_NAME "history"

enum PanelType {
    FileList,
    QuickView,
    Info,
    Tree
};

enum ListMode  {
    Full, // this is 'custom' with name,size,perm
    Brief,
    Custom
};

enum SortType {
    Unsorted,
    Name,
    Ext,
    Size,
    MTime,
    ATime,
    CTime
};

class Config {

  public:
    Config();

    void saveConfig();
    void loadConfig();

    void setColor(bool colour);
    bool isColour();

    std::string getCurrentPath();
    void setCurrentPath(const std::string &sPath);

    void setRoot(bool isRoot);
    char getUserPromp();

    // left panel
    std::string getLeftPath();
    void setLeftPath(const std::string &path);
    PanelType getLeftType();
    void setLeftType(PanelType type);
    ListMode getLeftMode();
    void setLeftMode(ListMode mode);
    std::string getLeftModeParams();
    void setLeftModeParams(std::string params);
    SortType getLeftSort();
    void setLeftSort(SortType sort);
    bool getLeftSortOrder();
    void setLeftSortOrder(bool order);

    // right panel
    std::string getRightPath();
    void setRightPath(const std::string &path);
    PanelType getRightType();
    void setRightType(PanelType type);
    ListMode getRightMode();
    void setRightMode(ListMode mode);
    std::string getRightModeParams();
    void setRightModeParams(std::string params);
    SortType getRightSort();
    void setRightSort(SortType sort);
    bool getRightSortOrder();
    void setRightSortOrder(bool order);

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

    bool isInternalEdit();
    void setInternalEdit();
    void setEditor(const std::string &filename);
    std::string getEditor();

    bool isInternalView();
    void setInternalView();
    void setViewer(const std::string &filename);
    std::string getViewer();

    bool isConfirmExit();
    void setConfirmExit(bool confirm);

    bool isConfirmExecute();
    void setConfirmExecute(bool confirm);
    bool isConfirmDelete();
    void setConfirmDelete(bool confirm);
    bool isConfirmOverride();
    void setConfirmOverride(bool confirm);

    std::vector<std::string> *getHistory();

private:
    std::string defaultPath;
    bool color, root;

    std::string leftPath;
    PanelType leftType;
    ListMode leftMode;
    std::string leftModeParams;
    SortType leftSort;
    bool leftSortOrder;

    std::string rightPath;
    PanelType rightType;
    ListMode rightMode;
    std::string rightModeParams;
    SortType rightSort;
    bool rightSortOrder;

    bool internalEdit, internalView;
    std::string editorCmd, viewerCmd;

    bool showDot, showBorder, showStatus, showFree, showTotal, showMenuBar, showKeyBar, useSi;
    bool confirmExit, confirmDelete, confirmOverride, confirmExecute;

    std::vector<std::string> *history;
};
