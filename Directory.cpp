//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include <dirent.h>
#include "Directory.h"

Directory::Directory(Config *pConfig, string sPath) {
    this->path = sPath;
    this->config = pConfig;
    this->notRead = true;
}

Directory::~Directory() {
}

int Directory::getNumberOfFiles(bool force) {
    if(this->notRead || force)
        getDirectory(true);

    return files.size();
}

int Directory::getDirectory(bool force) {
    int i = 0;
    DIR *dir;
    struct dirent *dirent;

    if (force)
        files.clear();

    dir = opendir(const_cast<char*>(path.c_str()));
    if (dir == NULL)
        return -1;

    while ((dirent = readdir(dir)) != NULL) {
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0)
            if (!((dirent->d_name[0] == '.') && !config->isShowDot())) {
                files.push_back(string(dirent->d_name));
                // todo also save file attribute, etc
            }
    }

    closedir (dir);
}

string Directory::getCurrentPath() {
    return this->path;
}
