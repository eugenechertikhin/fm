//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <strings.h>
#include <time.h>
#include "Directory.h"

Directory::Directory() {
    files = new std::vector<FileEntry *>;
}

Directory::~Directory() {
    for (auto const *e: *files) {
        delete e;
    }
    delete files;
}

void Directory::clear() {
    for (auto const *e: *files) {
        delete e;
    }
    files->clear();
}

std::vector<FileEntry *> *Directory::getDirectory(std::string path, bool showDot) throw(std::string) {
    files->clear();

    DIR *dir = opendir(const_cast<char *>(path.c_str()));
    if (dir == NULL)
        throw std::runtime_error("can't open directory");

    struct dirent *dirent;
    while ((dirent = readdir(dir)) != NULL) {
        if (strcmp(dirent->d_name, ".") != 0) {
            if (!((dirent->d_name[0] == '.') && !showDot)) {
                struct stat sb;
                bzero(&sb, sizeof(sb));
                lstat((path + "/" + dirent->d_name).c_str(), &sb);
                char perm[11];
                bzero(perm, 5);

                FileEntry *e = new FileEntry();
                e->select = false;

                e->name = dirent->d_name;
                e->size = sb.st_size;
                e->uid = sb.st_uid;
                e->gid = sb.st_gid;
                e->type = unknown;

                perm[0] = (sb.st_mode & S_ISVTX) ? 'S' : '-';
                perm[1] = (sb.st_mode & S_IRUSR) ? 'r' : '-';
                perm[2] = (sb.st_mode & S_IWUSR) ? 'w' : '-';
                perm[3] = (sb.st_mode & S_IXUSR) ? 'x' : '-';
                perm[4] = (sb.st_mode & S_IRGRP) ? 'r' : '-';
                perm[5] = (sb.st_mode & S_IWGRP) ? 'w' : '-';
                perm[6] = (sb.st_mode & S_IXGRP) ? 'x' : '-';
                perm[7] = (sb.st_mode & S_IROTH) ? 'r' : '-';
                perm[8] = (sb.st_mode & S_IWOTH) ? 'w' : '-';
                perm[9] = (sb.st_mode & S_IXOTH) ? 'x' : '-';

                if (S_ISREG(sb.st_mode)) e->type = regular;
                if (S_ISDIR(sb.st_mode)) { e->type = directory; perm[0] = 'd'; }
                if (S_ISCHR(sb.st_mode)) e->type = chardev;
                if (S_ISBLK(sb.st_mode)) e->type = blockdev;
                if (S_ISFIFO(sb.st_mode)) e->type = fifo;
                if (S_ISLNK(sb.st_mode)) e->type = softlink;
                if (S_ISSOCK(sb.st_mode)) e->type = socket;

                e->perm = perm;

                e->ctime = ctime(&sb.st_ctimespec.tv_nsec);
                e->atime = ctime(&sb.st_atimespec.tv_nsec);
                e->mtime = ctime(&sb.st_mtimespec.tv_nsec);

                files->push_back(e);
            }
        }
    }

    closedir(dir);

    return files;
}
