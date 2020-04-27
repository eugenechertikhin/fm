//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include "Config.h"
#include "version.h"

Config::Config() {
    color = true;
    showDot = true;
}

Config::~Config() {

}

void Config::loadConfig() {
    root = false;

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

int Config::getRows() {
    return rows;
}

int Config::getCols() {
    return cols;
}

char Config::getUserPromp() {
    if(root)
        return '#';

    return '$';
}

bool Config::isShowDot() {
    return showDot;
}