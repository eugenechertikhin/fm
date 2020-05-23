//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include "Config.h"
#include "version.h"
#include "Simpleini/Simpleini.h"

Config::Config() {
    history = new std::vector<std::string>;
}

Config::~Config() {
    // todo save history
    // todo save config to ini
}

void Config::loadConfig() {
    // initial values
    root = false;
    color = true;
    showDot = true;

    leftType = FileList;
    leftMode = Brief;
    leftModeParams = "Name Size";
    leftSort = Name;
    leftSortOrder = true;

    rightType = FileList;
    rightMode = Custom;
    rightModeParams = "Name Size Perm";
    rightSort = Name;
    rightSortOrder = true;

    confirmExit = true;
    confirmDelete = true;
    confirmOverride = true;
    confirmExecute = true;

    internalView = true;
    internalEdit = false;
    editorCmd = "vi";
    viewerCmd = "less";

//    showKeyBar = true;

    // todo load config from ini
    // todo load history
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