//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>
#include <vector>
#include "Config.h"

enum FileType { unknown, fifo, chardev, directory, blockdev, regular, softlink, socket};

struct FileEntry {
    std::string name;
    int uid, gid;
    std::string linkedName;
    bool linkOk;
    int size;
    FileType type;
    std::string atime;
    std::string mtime;
    std::string ctime;
    std::string perm;
};

class Directory {
  public:
    Directory(Config *pConfig);
    ~Directory();

    void setPath(std::string path);
    std::vector<FileEntry *> *getDirectory() throw (std::string);

  private:
    Config *config;
    std::string path;
    bool force;
    std::vector<FileEntry *> *files;
};

