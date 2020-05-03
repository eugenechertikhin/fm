//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>
#include <vector>
#include "Config.h"

enum FileType { unknown, fifo, chardev, directory, blockdev, regular, softlink, socket};

struct FileEntry {
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

    void setPath(string path);
    vector<FileEntry *> *getDirectory() throw (string);

  private:
    Config *config;
    std::string path;
    bool force;
    std::vector<FileEntry *> *files;
};

