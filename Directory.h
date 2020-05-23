//
// Created by Eugene Chertikhin on 26.04.2020.
//

#pragma once
#include <string>
#include <vector>

enum FileType {
    unknown,
    fifo,
    chardev,
    directory,
    blockdev,
    regular,
    softlink,
    socket,
};

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
    bool select;
};

class Directory {
  public:
    Directory();
    ~Directory();

    void clear();
    std::vector<FileEntry *> *getDirectory(std::string path, bool showDot) throw (std::string);

  private:
    std::vector<FileEntry *> *files;
};

