//
// Created by Eugene Chertikhin on 26.04.2020.
//
#include "Config.h"
#include "version.h"

Config::Config() {
    history = new std::vector<std::string>;
}

void Config::saveConfig() {
    std::string path = getenv("HOME");
    path.append(CONFIG_PATH);

    // save config to ini
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.SetValue(CONFIG_NAME, "leftPath", leftPath.c_str());
    ini.SetValue(CONFIG_NAME, "rightPath", rightPath.c_str());
    ini.SetBoolValue(CONFIG_NAME, "color", color);

    if (leftType == QuickView) ini.SetValue(CONFIG_NAME, "leftType", "QuickView");
    else if (leftType == Info) ini.SetValue(CONFIG_NAME, "leftType", "Info");
    else if (leftType == Tree) ini.SetValue(CONFIG_NAME, "leftType", "Tree");
    else ini.SetValue(CONFIG_NAME, "leftType", "FileList");

    if (leftMode == Brief) ini.SetValue(CONFIG_NAME, "leftMode", "Brief");
    else if (leftMode == Custom) ini.SetValue(CONFIG_NAME, "leftMode", "Custom");
    else ini.SetValue(CONFIG_NAME, "leftMode", "Full");

    ini.SetBoolValue(CONFIG_NAME, "leftSortOrderAsc", leftSortOrder);
    if (leftSort == Unsorted) ini.SetValue(CONFIG_NAME, "leftSort", "Unsorted");
    else if (leftSort == Ext) ini.SetValue(CONFIG_NAME, "leftSort", "Ext");
    else if (leftSort == Size) ini.SetValue(CONFIG_NAME, "leftSort", "Size");
    else if (leftSort == MTime) ini.SetValue(CONFIG_NAME, "leftSort", "MTime");
    else if (leftSort == ATime) ini.SetValue(CONFIG_NAME, "leftSort", "ATime");
    else if (leftSort == CTime) ini.SetValue(CONFIG_NAME, "leftSort", "CTime");
    else ini.SetValue(CONFIG_NAME, "leftSort", "Name");
    ini.SetValue(CONFIG_NAME, "leftModeParams", "Name Size");

    if (rightType == QuickView) ini.SetValue(CONFIG_NAME, "rightType", "QuickView");
    else if (rightType == Info) ini.SetValue(CONFIG_NAME, "rightType", "Info");
    else if (rightType == Tree) ini.SetValue(CONFIG_NAME, "rightType", "Tree");
    else ini.SetValue(CONFIG_NAME, "rightType", "FileList");

    if (rightMode == Brief) ini.SetValue(CONFIG_NAME, "rightMode", "Brief");
    else if (rightMode == Custom) ini.SetValue(CONFIG_NAME, "rightMode", "Custom");
    else ini.SetValue(CONFIG_NAME, "rightMode", "Full");

    ini.SetBoolValue(CONFIG_NAME, "rightSortOrderAsc", rightSortOrder);
    if (rightSort == Unsorted) ini.SetValue(CONFIG_NAME, "rightSort", "Unsorted");
    else if (rightSort == Ext) ini.SetValue(CONFIG_NAME, "rightSort", "Ext");
    else if (rightSort == Size) ini.SetValue(CONFIG_NAME, "rightSort", "Size");
    else if (rightSort == MTime) ini.SetValue(CONFIG_NAME, "rightSort", "MTime");
    else if (rightSort == ATime) ini.SetValue(CONFIG_NAME, "rightSort", "ATime");
    else if (rightSort == CTime) ini.SetValue(CONFIG_NAME, "rightSort", "CTime");
    else ini.SetValue(CONFIG_NAME, "rightSort", "Name");
    ini.SetValue(CONFIG_NAME, "rightModeParams", "Name Size");

    ini.SetBoolValue(CONFIG_NAME, "internalView", internalView);
    ini.SetBoolValue(CONFIG_NAME, "internalEdit", internalEdit);
    ini.SetValue(CONFIG_NAME, "editorCmd", editorCmd.c_str());
    ini.SetValue(CONFIG_NAME, "viewerCmd", viewerCmd.c_str());

    ini.SetBoolValue(CONFIG_NAME, "showDot", showDot);
    ini.SetBoolValue(CONFIG_NAME, "showBorder", showBorder);
    ini.SetBoolValue(CONFIG_NAME, "showStatus", showStatus);
    ini.SetBoolValue(CONFIG_NAME, "showFree", showFree);
    ini.SetBoolValue(CONFIG_NAME, "showTotal", showTotal);
    ini.SetBoolValue(CONFIG_NAME, "showMenuBar", showMenuBar);
    ini.SetBoolValue(CONFIG_NAME, "showKeyBar", showKeyBar);
    ini.SetBoolValue(CONFIG_NAME, "useSi", useSi);

    ini.SetBoolValue(CONFIG_NAME, "confirmExit", confirmExit);
    ini.SetBoolValue(CONFIG_NAME, "confirmDelete", confirmDelete);
    ini.SetBoolValue(CONFIG_NAME, "confirmOverride", confirmOverride);
    ini.SetBoolValue(CONFIG_NAME, "confirmExecute", confirmExecute);
    ini.SaveFile((path + CONFIG_NAME).c_str());

    // save history
    std::ofstream hist;
    hist.open((path+HISTORY_NAME).c_str(), std::ios::trunc);
    if (hist.is_open()) {
        for (std::vector<std::string>::iterator i = history->begin(); i!=history->end(); ++i)
            hist << *i << std::endl;
        hist.close();
    }
}

void Config::loadConfig() {
    std::string path = getenv("HOME");
    path.append(CONFIG_PATH);

    // load config
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile((path+CONFIG_NAME).c_str());

    leftPath = ini.GetValue(CONFIG_NAME, "leftPath", defaultPath.c_str());
    rightPath = ini.GetValue(CONFIG_NAME, "rightPath", defaultPath.c_str());
    color = ini.GetBoolValue(CONFIG_NAME, "color", true);

    std::string lt = ini.GetValue(CONFIG_NAME, "leftType", "FileList");
    if (lt == "QuickView") leftType = QuickView;
    else if (lt == "Info") leftType = Info;
    else if (lt == "Tree") leftType = Tree;
    else leftType = FileList;

    std::string lm = ini.GetValue(CONFIG_NAME, "leftMode", "Full");
    if (lm == "Brief") leftMode = Brief;
    else if (lm == "Custom") leftMode = Custom;
    else leftMode = Full;

    leftSortOrder = ini.GetBoolValue(CONFIG_NAME, "leftSortOrderAsc", true);
    std::string ls = ini.GetValue(CONFIG_NAME, "leftSort", "Name");
    if (ls == "Unsorted") leftSort = Unsorted;
    else if (ls == "Ext") leftSort = Ext;
    else if (ls == "Size") leftSort = Size;
    else if (ls == "MTime") leftSort = MTime;
    else if (ls == "ATime") leftSort = ATime;
    else if (ls == "CTime") leftSort = CTime;
    else leftSort = Name;
    leftModeParams = ini.GetValue(CONFIG_NAME, "leftModeParams", "Name Size");

    lt = ini.GetValue(CONFIG_NAME, "rightType", "FileList");
    if (lt == "QuickView") rightType = QuickView;
    else if (lt == "Info") rightType = Info;
    else if (lt == "Tree") rightType = Tree;
    else rightType = FileList;

    lm = ini.GetValue(CONFIG_NAME, "rightMode", "Full");
    if (lm == "Brief") rightMode = Brief;
    else if (lm == "Custom") rightMode = Custom;
    else rightMode = Full;

    rightModeParams = ini.GetValue(CONFIG_NAME, "rightModeParams", "Name Size Perm");
    ls = ini.GetValue(CONFIG_NAME, "rightSort", "Name");
    if (ls == "Unsorted") rightSort = Unsorted;
    else if (ls == "Ext") rightSort = Ext;
    else if (ls == "Size") rightSort = Size;
    else if (ls == "MTime") rightSort = MTime;
    else if (ls == "ATime") rightSort = ATime;
    else if (ls == "CTime") rightSort = CTime;
    else rightSort = Name;
    rightSortOrder = ini.GetBoolValue(CONFIG_NAME, "rightSortOrderAsc", true);

    internalView = ini.GetBoolValue(CONFIG_NAME, "internalView", true);
    internalEdit = ini.GetBoolValue(CONFIG_NAME, "internalEdit", true);
    editorCmd = ini.GetValue(CONFIG_NAME, "editorCmd", "vi");
    viewerCmd = ini.GetValue(CONFIG_NAME, "viewerCmd","less");

    showDot = ini.GetBoolValue(CONFIG_NAME, "showDot", true);
    showBorder = ini.GetBoolValue(CONFIG_NAME, "showBorder", true);
    showStatus = ini.GetBoolValue(CONFIG_NAME, "showStatus", true);
    showFree = ini.GetBoolValue(CONFIG_NAME, "showFree", true);
    showTotal = ini.GetBoolValue(CONFIG_NAME, "showTotal", true);
    showMenuBar = ini.GetBoolValue(CONFIG_NAME, "showMenuBar", false);
    showKeyBar = ini.GetBoolValue(CONFIG_NAME, "showKeyBar", true);
    useSi = ini.GetBoolValue(CONFIG_NAME, "useSi", true);

    confirmExit = ini.GetBoolValue(CONFIG_NAME, "confirmExit", true);
    confirmDelete = ini.GetBoolValue(CONFIG_NAME, "confirmDelete", true);
    confirmOverride = ini.GetBoolValue(CONFIG_NAME, "confirmOverride", true);
    confirmExecute = ini.GetBoolValue(CONFIG_NAME, "confirmExecute", true);

    // load history
    std::ifstream hist;
    hist.open((path+HISTORY_NAME).c_str());
    if (hist.is_open()) {
        for(std::string line; getline(hist, line);) {
            history->push_back(line);
        }
        hist.close();
    }
}

void Config::setColor(bool colour) {
    color = colour;
}
bool Config::isColour() {
    return color;
}

void Config::setCurrentPath(const std::string &sPath) {
    this->defaultPath = sPath;
}
std::string Config::getCurrentPath() {
    return defaultPath;
}

void Config::setRoot(bool isRoot) {
    root = isRoot;
}
char Config::getUserPromp() {
    if(root)
        return '#';

    return '$';
}

std::string Config::getLeftPath() {
    if (leftPath.empty())
        leftPath = defaultPath;
    return leftPath;
}
void Config::setLeftPath(const std::string &path) {
    leftPath = path;
}
PanelType Config::getLeftType() {
    return leftType;
}
void Config::setLeftType(PanelType type) {
    leftType = type;
}
ListMode Config::getLeftMode() {
    return leftMode;
}
void Config::setLeftMode(ListMode mode) {
    leftMode = mode;
}
std::string Config::getLeftModeParams() {
    return leftModeParams;
}
void Config::setLeftModeParams(std::string params) {
    leftModeParams = params;
}
SortType Config::getLeftSort() {
    return leftSort;
}
void Config::setLeftSort(SortType sort) {
    leftSort = sort;
}
bool Config::getLeftSortOrder() {
    return leftSortOrder;
}
void Config::setLeftSortOrder(bool order) {
    leftSortOrder = order;
}

std::string Config::getRightPath() {
    if (rightPath.empty())
        rightPath = defaultPath;
    return rightPath;
}
void Config::setRightPath(const std::string &path) {
    rightPath = path;
}
PanelType Config::getRightType() {
    return rightType;
}
void Config::setRightType(PanelType type) {
    rightType = type;
}
ListMode Config::getRightMode() {
    return rightMode;
}
void Config::setRightMode(ListMode mode) {
    rightMode = mode;
}
std::string Config::getRightModeParams() {
    return rightModeParams;
}
void Config::setRightModeParams(std::string params) {
    rightModeParams = params;
}
SortType Config::getRightSort() {
    return rightSort;
}
void Config::setRightSort(SortType sort) {
    rightSort = sort;
}
bool Config::getRightSortOrder() {
    return rightSortOrder;
}
void Config::setRightSortOrder(bool order) {
    rightSortOrder = order;
}

bool Config::isShowDot() {
    return showDot;
}
void Config::setShowDot(bool f) {
    showDot = f;
}

bool Config::isShowBorder() {
    return showBorder;
}
void Config::setShowBorder(bool f) {
    showBorder = f;
}

bool Config::isShowStatus() {
    return showStatus;
}
void Config::setShowStatus(bool f) {
    showStatus = f;
}

bool Config::isShowFree() {
    return showFree;
}
void Config::setShowFree(bool f) {
    showFree = f;
}

bool Config::isShowTotal() {
    return showTotal;
}
void Config::setShowTotal(bool f) {
    showTotal = f;
}

bool Config::isShowMenuBar() {
    return showMenuBar;
}
void Config::setShowMenuBar(bool f) {
    showMenuBar = f;
}

bool Config::isShowKeyBar() {
    return showKeyBar;
}
void Config::setShowKeyBar(bool f) {
    showKeyBar = f;
}

bool Config::isUseSi() {
    return useSi;
}
void Config::setUseSi(bool f) {
    useSi = f;
}

bool Config::isInternalEdit() {
    return this->internalEdit;
}
void Config::setInternalEdit() {
    this->internalEdit = true;
}
void Config::setEditor(const std::string &filename) {
    this->internalEdit = false;
    this->editorCmd = filename;
}
std::string Config::getEditor() {
    return editorCmd;
}

bool Config::isInternalView() {
    return this->internalView;
}
void Config::setInternalView() {
    this->internalView = true;
}
void Config::setViewer(const std::string &filename) {
    this->internalView = false;
    this->viewerCmd = filename;
}
std::string Config::getViewer() {
    return viewerCmd;
}

bool Config::isConfirmExit() {
    return confirmExit;
}
void Config::setConfirmExit(bool confirm) {
    confirmExit = confirm;
}
bool Config::isConfirmExecute() {
    return confirmExecute;
}
void Config::setConfirmExecute(bool confirm) {
    confirmExecute = confirm;
}

bool Config::isConfirmDelete() {
    return confirmDelete;
}
void Config::setConfirmDelete(bool confirm) {
    confirmDelete = confirm;
}
bool Config::isConfirmOverride() {
    return confirmOverride;
}
void Config::setConfirmOverride(bool confirm) {
    confirmOverride = confirm;
}

std::vector<std::string> *Config::getHistory() {
    return history;
}