//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>
#include <vector>
#include "Config.h"

using namespace std;

class Directory {
  public:
    Directory(Config *pConfig, string sPath);
    ~Directory();

    int getNumberOfFiles(bool force);
    int getDirectory(bool force);
    string getCurrentPath();

  private:
    Config *config;
    string path;
    vector<string> files;
    bool notRead;
};

