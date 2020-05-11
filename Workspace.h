//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once

#include <string>
#include "Config.h"
#include "FilePanel.h"

class Workspace {
public:
    Workspace(Config *pConfig);
    ~Workspace();

    void show(int rows, int cols);

private:
    Config *config;

//    std::vector<FilePanel> panels;
    FilePanel *current;

    std::string cmd;
};
