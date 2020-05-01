//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>
#include <vector>
#include "Config.h"

enum FileType { unknown, fifo, chardev, directory, blockdev, regular, link, socket};

class FileEntry {
public:
    string name;
    int uid, gid;
    string linkedName;
    bool linkOk;
    int size;
    FileType type;
    string atime;
    string mtime;
    string ctime;
    string perm;
};

class Directory {
  public:
    Directory(Config *pConfig);
    ~Directory();

    std::vector<FileEntry *> getDirectory(std::string sPath) throw (string);

  private:
    Config *config;
    std::string path;
    std::vector<FileEntry *> files;
};

