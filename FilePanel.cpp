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
#define EXTRA_COLUMN 11
#define TOP_LINE 1
#define COLUMN_NAME_LINE 1

void FilePanel::draw(int y, int x, int rows, int cols, bool colour) {
    this->cols = cols;
    this->rows = rows;

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
        filesCount = files->size();

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
            rowsCount = rows - COLUMN_NAME_LINE - STATUS_LINE - TOP_LINE;
            cursorLengh = cols - (EXTRA_COLUMN * (modeParams->size()-1)) - 2;

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
                util::Utils::paddingRight(&files->at(i+offset)->name, cursorLengh-1);
                mvwprintw(win, 2+i, 2, "%s", files->at(i+offset)->name.c_str());

                std::string size = std::to_string(files->at(i+offset)->size);
                util::Utils::paddingLeft(&size, EXTRA_COLUMN-1);
                mvwprintw(win, 2+i, 2 + cursorLengh, size.c_str());

                mvwprintw(win, 2+i, 2+cursorLengh + EXTRA_COLUMN, "%s", files->at(i+offset)->perm.c_str());
            }

        } else if (mode == Brief) {
            rowsCount = rows - COLUMN_NAME_LINE - STATUS_LINE - TOP_LINE;
            cursorLengh = cols/2 - 2;

            for (int i = 0; i < rows-1 - STATUS_LINE; i++)
                mvwaddch(win, i + 1, cols/2 - 1, ACS_VLINE);

            // print column name
            wattron(win, COLOR_PAIR(YELLOW_ON_BLUE));
            mvwprintw(win, 1, 1 + 1, n);
            mvwprintw(win, 1, cols/2 + 1, n);
            wattroff(win, COLOR_PAIR(YELLOW_ON_BLUE));

            // print files
            for (int i = 0; i < rows - COLUMN_NAME_LINE - STATUS_LINE - TOP_LINE; i++) {
                util::Utils::paddingRight(&files->at(i+offset)->name, cursorLengh-1);
                mvwprintw(win, 2 + i, 2, "%s", files->at(i+offset)->name.c_str());
            }
        }

        // print status line
        util::Utils::paddingRight(&files->at(pos+offset)->name, cols-22);
        mvwprintw(win, rowsCount + STATUS_LINE, 2, "%s", files->at(pos+offset)->name.c_str());
        mvwprintw(win, rowsCount + STATUS_LINE, cols-22, "%d", files->at(pos+offset)->size);
        mvwprintw(win, rowsCount + STATUS_LINE, cols-11, "%s", files->at(pos+offset)->perm.c_str());

    } else if (type == Tree) {
        // todo
    } else if (type == Info) {
        // todo
    } else if (type == QuickView) {
        // todo
    }

    wrefresh(win);
}

void FilePanel::hideCursor(bool p) {
    if (type == FileList || type == QuickView) {
        // highlight path
        if (p)
            mvwchgat(win, 0, 2, path.size() + 2, A_COLOR, WHITE_ON_BLUE, NULL);

        // print cursor
        mvwchgat(win, 2 + pos, 1, cursorLengh, A_COLOR, WHITE_ON_BLUE, NULL);
    }
    wrefresh(win);
}
void FilePanel::showCursor(bool p) {
    if (type == FileList || type == QuickView) {
        // highlight path
        if (p)
            mvwchgat(win, 0, 2, path.size() + 2, A_COLOR, BLACK_ON_CYAN, NULL);

        // print cursor
        mvwchgat(win, 2 + pos, 1, cursorLengh, A_COLOR, BLACK_ON_CYAN, NULL);
    }
    wrefresh(win);
}

void FilePanel::moveUp() {
    if (pos == 0 && offset == 0)
        return;

    hideCursor(false);
    if (pos > 0)
        pos--;
    else
        offset--;

    // print files

    // print status line
    util::Utils::paddingRight(&files->at(pos+offset)->name, cols-22);
    mvwprintw(win, rowsCount + STATUS_LINE, 2, "%s", files->at(pos+offset)->name.c_str());
    mvwprintw(win, rowsCount + STATUS_LINE, cols-22, "%d", files->at(pos+offset)->size);
    mvwprintw(win, rowsCount + STATUS_LINE, cols-11, "%s", files->at(pos+offset)->perm.c_str());

    showCursor(false);
}

void FilePanel::moveDown() {
    hideCursor(false);
    pos++;

    // print files

    // print status line
    util::Utils::paddingRight(&files->at(pos+offset)->name, cols-22);
    mvwprintw(win, rowsCount + STATUS_LINE, 2, "%s", files->at(pos+offset)->name.c_str());
    mvwprintw(win, rowsCount + STATUS_LINE, cols-22, "%d", files->at(pos+offset)->size);
    mvwprintw(win, rowsCount + STATUS_LINE, cols-11, "%s", files->at(pos+offset)->perm.c_str());

    showCursor(false);
}

void FilePanel::moveLeft() {
    // print status line
    util::Utils::paddingRight(&files->at(pos+offset)->name, cols-22);
    mvwprintw(win, rowsCount + STATUS_LINE, 2, "%s", files->at(pos+offset)->name.c_str());
    mvwprintw(win, rowsCount + STATUS_LINE, cols-22, "%d", files->at(pos+offset)->size);
    mvwprintw(win, rowsCount + STATUS_LINE, cols-11, "%s", files->at(pos+offset)->perm.c_str());
}

void FilePanel::moveRight() {
    // print status line
    util::Utils::paddingRight(&files->at(pos+offset)->name, cols-22);
    mvwprintw(win, rowsCount + STATUS_LINE, 2, "%s", files->at(pos+offset)->name.c_str());
    mvwprintw(win, rowsCount + STATUS_LINE, cols-22, "%d", files->at(pos+offset)->size);
    mvwprintw(win, rowsCount + STATUS_LINE, cols-11, "%s", files->at(pos+offset)->perm.c_str());
}

void FilePanel::enter() {

}