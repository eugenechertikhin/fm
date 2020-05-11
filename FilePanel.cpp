//
// Created by Eugene Chertikhin on 04.05.2020.
//

#include <algorithm>
#include <iostream>
#include "FilePanel.h"
#include "Colors.h"

FilePanel::FilePanel() {
    Colors::initColors();
    modeParams = new std::vector<std::string>;

    showDot = true;
    showBorder = true;
    showStatus = true;
    showFree = true;
    showTotal = true;
    useSi = true;
}

FilePanel::~FilePanel() {
    delete directory;
}

void FilePanel::setNext(FilePanel *fp) {
    next = fp;
}
FilePanel *FilePanel::getNext() {
    return next;
}

void FilePanel::setPath(std::string path) {
    this->path = path;
}
std::string FilePanel::getPath() {
    return path;
}
void FilePanel::setType(PanelType type) {
    this->type = type;
}
void FilePanel::setMode(ListMode mode, std::string params) {
    this->mode = mode;
    this->modeParams->clear();
    util::Utils::split(modeParams, params, ' ');
}
void FilePanel::setSort(SortType sortType, bool sortOrder) {
    this->sortType = sortType;
    this->sortOrder = sortOrder;
}
void FilePanel::setShowDot(bool showDot) {
    this->showDot = showDot;
}

void FilePanel::sortDirectory(std::vector<FileEntry *> *files) {
    if (sortType != Unsorted) {
        if (sortType == Name) {
            if (sortOrder) {
                sort(files->begin(), files->end(), [](const FileEntry *l, const FileEntry *r) {
                    return l->name < r->name;
                });
            } else {
                sort(files->begin(), files->end(), [](const FileEntry *l, const FileEntry *r) {
                    return l->name > r->name;
                });
            }
        } else if (sortType == Ext) {
            // todo
        } else if (sortType == Size) {
            if (sortOrder) {
                sort(files->begin(), files->end(), [](const FileEntry *l, const FileEntry *r) {
                    return l->size < r->size;
                });
            } else {
                sort(files->begin(), files->end(), [](const FileEntry *l, const FileEntry *r) {
                    return l->size > r->size;
                });
            }
        } else if (sortType == MTime) {
            if (sortOrder) {
                sort(files->begin(), files->end(), [](const FileEntry *l, const FileEntry *r) {
                    return l->mtime < r->mtime;
                });
            } else {
                sort(files->begin(), files->end(), [](const FileEntry *l, const FileEntry *r) {
                    return l->mtime > r->mtime;
                });
            }
        } else if (sortType == ATime) {
            if (sortOrder) {
                sort(files->begin(), files->end(), [](const FileEntry *l, const FileEntry *r) {
                    return l->atime < r->atime;
                });
            } else {
                sort(files->begin(), files->end(), [](const FileEntry *l, const FileEntry *r) {
                    return l->atime > r->atime;
                });
            }
        } else if (sortType == CTime) {
            if (sortOrder) {
                sort(files->begin(), files->end(), [](const FileEntry *l, const FileEntry *r) {
                    return l->ctime < r->ctime;
                });
            } else {
                sort(files->begin(), files->end(), [](const FileEntry *l, const FileEntry *r) {
                    return l->ctime > r->ctime;
                });
            }
        }
    }
}

void FilePanel::redraw() {
    redrawwin(win);
    wrefresh(win);
}

#define STATUS_LINE 3
#define EXTRA_COLUMN 10
#define TOP_LINE 1
#define COLUMN_NAME_LINE 1

void FilePanel::draw(int y, int x, int rows, int cols, bool colour) {
    // headers
    char n[] = "Name";
    char s[] = "Size";
    char m[] = "Modify";
    char a[] = "Access";
    char c[] = "Create";
    char p[] = "Perm";

    win = newwin(rows, cols, y, x);
    box(win, 0, 0);
    if (colour)
        wbkgd(win, COLOR_PAIR(1));

    // print window inside lines and column names
    if (type == FileList) {
        if (colour)
            wattron(win, COLOR_PAIR(WHITE_ON_BLUE));
        mvwaddch(win, rows - STATUS_LINE, 0, ACS_LTEE);
        mvwhline(win, rows - STATUS_LINE, 1, ACS_HLINE, cols - 2);
        mvwaddch(win, rows - STATUS_LINE, cols - 1, ACS_RTEE);
        if (colour)
            wattroff(win, COLOR_PAIR(WHITE_ON_BLUE));

        // print path at the header
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 2, " %s ", const_cast<char*>(path.c_str()));
        wattroff(win, COLOR_PAIR(1));

        // read directory
        directory = new Directory();
        files = directory->getDirectory(path, showDot);
        sortDirectory(files);

        // show total files count
        mvwprintw(win, 0, cols - 7, " %d ", files->size());

        // showTotalSpace / showFreeSpace
        struct statvfs statfs;
        statvfs(path.c_str(), &statfs);
        mvwprintw(win, rows-1, 2, " %u / %u ", statfs.f_bavail*statfs.f_frsize, statfs.f_bfree*statfs.f_frsize);

        // Override. Full is just variant of Custom
        if (mode == Full) {
            mode = Custom;
            modeParams->clear();
            modeParams->push_back(n);
            modeParams->push_back(s);
            modeParams->push_back(p);
        }

        if (mode == Custom) {
            for (int i = 0; i < rows-1 - STATUS_LINE; i++) {
                for (int j = 1; j < modeParams->size(); j++)
                    mvwaddch(win, i + 1, cols - (EXTRA_COLUMN * j) - 1, ACS_VLINE);
            }

            wattron(win, COLOR_PAIR(YELLOW_ON_BLUE));
            // print first column name
            mvwprintw(win, 1, 2, modeParams->at(0).c_str());

            // print extra custom column names
            for (int j = 1; j < modeParams->size(); j++)
                mvwprintw(win, 1, 1+cols - (EXTRA_COLUMN * (modeParams->size()-j)), modeParams->at(j).c_str());
            wattroff(win, COLOR_PAIR(YELLOW_ON_BLUE));

            // print files
            for (int i = 0; i < rows - COLUMN_NAME_LINE - STATUS_LINE - TOP_LINE; i++) {
                mvwprintw(win, 2+i, 2, "%s", files->at(i)->name.c_str());

//            int sizeOfPart = config->getCols() / 2 - (SmallColumnSize+1) - (SmallColumnSize+1) -1;
//
//            util::Utils::paddingRight(&entry->name, cursorLengh-1);
//            mvwprintw(win, 2 + i - offset, 2, "%s", entry->name.c_str());
//            std::string size = std::to_string(entry->size);
//            util::Utils::paddingLeft(&size, SmallColumnSize);
//            mvwprintw(win, 2 + i - offset, sizeOfPart+1, size.c_str());
//            mvwprintw(win, 2 + i - offset, sizeOfPart + SmallColumnSize+2, "%s", entry->perm.c_str());
            }

        } else if (mode == Brief) {
            for (int i = 0; i < rows-1 - STATUS_LINE; i++)
                mvwaddch(win, i + 1, cols/2 - 1, ACS_VLINE);

            // print column name
            wattron(win, COLOR_PAIR(YELLOW_ON_BLUE));
            mvwprintw(win, 1, 1 + 1, n);
            mvwprintw(win, 1, cols/2 + 1, n);
            wattroff(win, COLOR_PAIR(YELLOW_ON_BLUE));

            // print files
            for (int i = 0; i < rows - COLUMN_NAME_LINE - STATUS_LINE - TOP_LINE; i++) {
//            util::Utils::paddingRight(&entry->name, cursorLengh-1);
                mvwprintw(win, 2 + i, 2, "%s", files->at(i)->name.c_str());
            }
        }
    } else if (type == Tree) {
        // todo
    } else if (type == Info) {
        // todo
    } else if (type == QuickView) {
        // todo
    }

    wrefresh(win);
}

void FilePanel::hideCursor() {
    if (type == FileList || type == QuickView)
        mvwchgat(win, 0, 2, path.size()+2, A_COLOR, 1, NULL);

    // todo print cursor

    //    mvwchgat(win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 3, NULL);

    wrefresh(win);
}
void FilePanel::showCursor() {
    if (type == FileList || type == QuickView)
        mvwchgat(win, 0, 2, path.size()+2, A_COLOR, 3, NULL);

    // todo print cursor

    //    mvwchgat(win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 3, NULL);

    wrefresh(win);
}
