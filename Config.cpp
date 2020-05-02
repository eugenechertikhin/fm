//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include "Config.h"
#include "version.h"
#include "Simpleini/Simpleini.h"

Config::Config() {
}

Config::~Config() {
    // save config to ini
}

void Config::loadConfig() {
    // load config from inni

    // temp
    root = false;
    color = true;
    showDot = true;
    hotPanels = 0;

    leftPath = "/";
    leftPanelType = FileList;
    leftPanelMode = Full;
    leftPanelSort = Size;

    rightPanelType = FileList;
    rightPanelMode = Brief; // Custom;
    rightCustomMode = "name size modify access create perm";
    rightPanelSort = Name;
}

void Config::forceColor() {
    color = true;
}

void Config::forceBlack() {
    color = false;
}

void Config::setSize(int row, int col) {
    rows = row;
    cols = col;
}

bool Config::isColour() {
    return color;
}

int Config::getCols() {
    return cols;
}

int Config::getRows() {
    return rows;
}

int Config::getRowsInPanel() {
    return rows - 2 /* top size */ - 1 /* cmd line */ - 3 /* file info line */;
}

char Config::getUserPromp() {
    if(root)
        return '#';

    return '$';
}

string Config::getLeftPath() {
    if (leftPath.empty())
        leftPath = defaultPath;

    return leftPath;
}
void Config::setLeftPath(const string &path) {
    leftPath = path;
}
PanelType Config::getLeftPanelType() {
    return leftPanelType;
}
void Config::setLeftPanelType(PanelType type) {
    leftPanelType = type;
}
ListMode Config::getLeftPanelMode() {
    return leftPanelMode;
}
void Config::setLeftPanelMode(ListMode mode) {
    leftPanelMode = mode;
}
SortOrder Config::getLeftPanelSort() {
    return leftPanelSort;
}
void Config::setLeftPanelSort(SortOrder sort) {
    leftPanelSort = sort;
}

string Config::getRightPath() {
    if (rightPath.empty())
        rightPath = defaultPath;
    return rightPath;
}
void Config::setRightPath(const string &path) {
    rightPath = path;
}
PanelType Config::getRightPanelType() {
    return rightPanelType;
}
void Config::setRightPanelType(PanelType type) {
    rightPanelType = type;
}
ListMode Config::getRightPanelMode() {
    return rightPanelMode;
}
void Config::setRightPanelMode(ListMode mode) {
    rightPanelMode = mode;
}
SortOrder Config::getRightPanelSort() {
    return rightPanelSort;
}
void Config::setRightPanelSort(SortOrder sort) {
    rightPanelSort = sort;
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

void Config::setCurrentPath(const string &sPath) {
    this->defaultPath = sPath;
}

string Config::getCurrentPath() {
    return defaultPath;
}

bool Config::isInternalEdit() {
    return this->internalEdit;
}
void Config::setInternalEdit() {
    this->internalEdit = true;
}

void Config::setEditor(const string &filename) {
    this->internalEdit = false;
    this->editorCmd = filename;
}

string Config::getEditor() {
    return editorCmd;
}

bool Config::isInternalView() {
    return this->internalView;
}

void Config::setInternalView() {
    this->internalView = true;
}

void Config::setViewer(const string &filename) {
    this->internalView = false;
    this->viewerCmd = filename;
}

string Config::getViewer() {
    return viewerCmd;
}
