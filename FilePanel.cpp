//
// Created by Eugene Chertikhin on 04.05.2020.
//

#include <algorithm>
#include <iostream>
#include "FilePanel.h"
#include "Colors.h"

#define EXTRA_COLUMN 11
#define COLUMN_NAME_LINE 1

#define HEADER_NAME "Name"
#define HEADER_SIZE "Size"
//m = "Modify";
//a = "Access";
//c = "Create";
#define HEADER_PERM "Perm"

FilePanel::FilePanel(Config *conf) {
    config = conf;
    Colors::initColors();
    modeParams = new std::vector<std::string>;

    if (config->isShowStatus()) statusLine = 3;
    else statusLine = 0;

    if (config->isShowMenuBar()) topLine = 1;
    else topLine = 0;

    if (config->isShowKeyBar()) keybar = 1;
    else keybar = 0;
}

FilePanel::~FilePanel() {
    delwin(win);
    delete dir;
}

void FilePanel::setNext(FilePanel *fp) {
    next = fp;
}
FilePanel *FilePanel::getNext() {
    return next;
}

void FilePanel::setPath(std::string path) {
    this->path = path;
    pos = 0;
    offset = 0;
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

// todo desc order doesn't work
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
            // todo sort by extension
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

void FilePanel::draw(int y, int x, int rows, int cols, bool colour) {
    this->cols = cols;
    this->rows = rows-1; // because path-line
    this->colour = colour;

    dir = new Directory();

    pos = 0;
    offset = 0;

    win = newwin(this->rows-topLine-keybar, cols, y+topLine, x);
    if (colour)
        wbkgd(win, COLOR_PAIR(WHITE_ON_BLUE));

    printInside();
    wrefresh(win);
}

void FilePanel::printInside() {
    box(win, 0, 0);

    if (type == FileList) {
        if (config->isShowStatus()) {
            if (colour)
                wattron(win, COLOR_PAIR(WHITE_ON_BLUE));
            mvwaddch(win, rows-statusLine-topLine-keybar, 0, ACS_LTEE);
            mvwhline(win, rows-statusLine-topLine-keybar, 1, ACS_HLINE, cols - 2);
            mvwaddch(win, rows-statusLine-topLine-keybar, cols - 1, ACS_RTEE);
            if (colour)
                wattroff(win, COLOR_PAIR(WHITE_ON_BLUE));
        }

        // print path at the header
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, topLine, 2, " %s ", const_cast<char*>(path.c_str()));
        wattroff(win, COLOR_PAIR(1));

        // Override. Full is just variant of Custom
        if (mode == Full) {
            mode = Custom;
            modeParams->clear();
            modeParams->push_back(HEADER_NAME);
            modeParams->push_back(HEADER_SIZE);
            modeParams->push_back(HEADER_PERM);
        }

        if (mode == Custom) {
            rowsCount = rows-COLUMN_NAME_LINE-statusLine-topLine-keybar-1;
            cursorLengh = cols - (EXTRA_COLUMN * (modeParams->size()-1)) - 2;
            if (cursorLengh < 0)
                throw std::runtime_error("screen size is too small");

            for (int i = 0; i < rows - 1 - statusLine - topLine - keybar; i++) {
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
        } else if (mode == Brief) {
            rowsCount = rows-COLUMN_NAME_LINE-statusLine-topLine-keybar-1;
            cursorLengh = cols/2 - 2;

            for (int i = 0; i < rows - 1 - statusLine - topLine - keybar; i++)
                mvwaddch(win, i + 1, cols/2 - 1, ACS_VLINE);

            // print column name
            wattron(win, COLOR_PAIR(YELLOW_ON_BLUE));
            mvwprintw(win, 1 + topLine, 1 + 1, HEADER_NAME);
            mvwprintw(win, 1 + topLine, cols/2 + 1, HEADER_NAME);
            wattroff(win, COLOR_PAIR(YELLOW_ON_BLUE));
        }

        rescanDirectory();
        updateFiles();
        updateStatusLine();
    } else if (type == Tree) {
        // todo tree panel
    } else if (type == Info) {
        // todo info panel
    } else if (type == QuickView) {
        // todo quickview panel
    }
}
void FilePanel::update() {
    redrawwin(win);
    wrefresh(win);
}

void FilePanel::hideCursor(bool p) {
    if (type == FileList || type == QuickView) {
        // highlight path
        if (p)
            mvwchgat(win, 0, 2, path.size() + 2, A_COLOR, WHITE_ON_BLUE, NULL);

        int style = Colors::getStyleForFileEntry(files->at(pos+offset)->type);
        // print cursor
        if (mode == Brief) {
            if (pos < rowsCount)
                mvwchgat(win, 2 + pos, 1, cursorLengh, style, WHITE_ON_BLUE, NULL);
            else
                mvwchgat(win, 2 + pos-rowsCount, cols/2+1, cursorLengh, style, WHITE_ON_BLUE, NULL);
        } else {
            mvwchgat(win, 2 + pos, 1, cursorLengh, style, WHITE_ON_BLUE, NULL);
        }
    }
    wrefresh(win);
}
void FilePanel::showCursor(bool p) {
    if (type == FileList || type == QuickView) {
        // highlight path
        if (p)
            mvwchgat(win, 0, 2, path.size() + 2, A_COLOR, BLACK_ON_CYAN, NULL);

        // print cursor
        int style = Colors::getStyleForFileEntry(files->at(pos+offset)->type);
        if (mode == Brief) {
            if (pos < rowsCount)
                mvwchgat(win, 2 + pos, 1, cursorLengh, style, BLACK_ON_CYAN, NULL);
            else
                mvwchgat(win, 2 + pos-rowsCount, cols/2+1, cursorLengh, style, BLACK_ON_CYAN, NULL);
        } else {
            mvwchgat(win, 2 + pos, 1, cursorLengh, style, BLACK_ON_CYAN, NULL);
        }
    }
    wrefresh(win);
}

FileEntry *FilePanel::getCurrentFile() {
    return files->at(pos+offset);
}

void FilePanel::updateStatusLine() {
    if (config->isShowStatus()) {
        std::string _name = files->at(pos + offset)->name;
        util::Utils::paddingRight(&_name, cols - 22);
        mvwprintw(win, rowsCount+topLine+statusLine, 2, "%s", _name.c_str());
        mvwprintw(win, rowsCount+topLine+statusLine, cols - 22, "%d", files->at(pos + offset)->size);
        mvwprintw(win, rowsCount+topLine+statusLine, cols - 11, "%s", files->at(pos + offset)->perm.c_str());
    }
}

void FilePanel::updateFiles() {
    if (mode == Custom) {
        for (int i = 0; i < rowsCount; i++) {
            if (i+offset < filesCount) {
                std::string _name = files->at(i + offset)->name;
                util::Utils::paddingRight(&_name, cursorLengh - 1);
                int style = Colors::getStyleForFileEntry(files->at(i+offset)->type);

                wattron(win, style);
                mvwprintw(win, 2 + i, 2, "%s", _name.c_str());

                std::string _size = std::to_string(files->at(i + offset)->size);
                util::Utils::paddingLeft(&_size, EXTRA_COLUMN - 1);
                mvwprintw(win, 2 + i, 2 + cursorLengh, _size.c_str());

                mvwprintw(win, 2 + i, 2 + cursorLengh + EXTRA_COLUMN, "%s", files->at(i + offset)->perm.c_str());
                wattroff(win, style);
            }
        }
    } else if (mode == Brief) {
        int i, j = 0;
        for (i = 0; i < rowsCount; i++) {
            if (i+offset < filesCount) {
                std::string _name = files->at(i + offset)->name;
                util::Utils::paddingRight(&_name, cursorLengh - 1);
                int style = Colors::getStyleForFileEntry(files->at(i+offset)->type);

                wattron(win, style);
                mvwprintw(win, 2 + i, 2, "%s", _name.c_str());
                wattroff(win, style);
                j++;
            }
        }

        if (j < filesCount) {
            for (i = 0; i < rowsCount; i++) {
                if (i+j+offset < filesCount) {
                    std::string _name = files->at(i+j+offset)->name;
                    util::Utils::paddingRight(&_name, cursorLengh - 1);
                    int style = Colors::getStyleForFileEntry(files->at(i+j+offset)->type);

                    wattron(win, style);
                    mvwprintw(win, 2 + i, cols/2 + 1, "%s", _name.c_str());
                    wattroff(win, style);
                }
            }
        }
    }
}

void FilePanel::rescanDirectory() {
    dir->clear();

    try {
        files = dir->getDirectory(path, config->isShowDot());
        while (files->size() <= (pos+offset)) {
            if (pos > 1)
                pos--;
            else
                offset--;
        }

    } catch (const std::exception &e) {
        return;
    }
    sortDirectory(files);
    filesCount = files->size();

    // show total files count
    if (config->isShowTotal())
        mvwprintw(win, 0, cols - 7, " %d ", files->size());

    // showTotalSpace / showFreeSpace
    struct statvfs statfs;
    statvfs(path.c_str(), &statfs);
    if (config->isShowTotal() && config->isShowFree())
        mvwprintw(win, rows-keybar-1, 2, " %u / %u ", statfs.f_bavail*statfs.f_frsize, statfs.f_bfree*statfs.f_frsize);
    else if (config->isShowTotal())
        mvwprintw(win, rows-keybar-1, 2, " %u ", statfs.f_bavail*statfs.f_frsize);
    else if (config->isShowFree())
        mvwprintw(win, rows-keybar-1, 2, " %u ", statfs.f_bfree*statfs.f_frsize);
}

void FilePanel::moveUp() {
    if (pos == 0 && offset == 0)
        return;

    hideCursor(false);
    if (pos > 0)
        pos--;
    else if (pos + offset > 0) {
        offset--;
        updateFiles();
    }

    updateStatusLine();
    showCursor(false);
}

void FilePanel::moveDown() {
    hideCursor(false);

    if (pos < rowsCount-1 && pos < filesCount-1)
        pos++;
    else if (pos+offset < filesCount-1) {
        if (mode == Brief && pos < rowsCount*2-1) {
            pos++;
        } else {
            offset++;
            updateFiles();
        }
    }

    updateStatusLine();
    showCursor(false);
}

void FilePanel::moveLeft() {
    hideCursor(false);
    pos-=rowsCount;

    while (pos < 0) {
        pos++;
        if (offset > 0)
            offset--;
    }

    while (pos+offset < 0)
        pos++;

    updateFiles();
    updateStatusLine();
    showCursor(false);
}

void FilePanel::moveRight() {
    hideCursor(false);
    pos+=rowsCount;
    while (pos+offset > filesCount-1)
        pos--;

    int c = 0;
    if (mode == Custom)
        c = rowsCount-1;
    else if (mode == Brief)
        c = rowsCount*2-1;

    while (pos > c) {
        pos--;
        offset++;
    }

    updateFiles();
    updateStatusLine();
    showCursor(false);
}

void FilePanel::clear() {
    wclear(win);
}

void FilePanel::enter() {
    FileEntry *f = getCurrentFile();
    if (f->type == directory) {

        pos = 0;
        offset = 0;
        if (f->name == "..") {
            goBack();
        } else
            (path == "/") ? path.append(f->name) : path.append("/" + f->name);

        wclear(win);
        printInside();
        showCursor(true);
    } else if (false) {
        // todo run file
    }
}

void FilePanel::goBack() {
    size_t p = path.find_last_of("\\/");
    std::string res = path.substr(0, p);
    std::string name = path.substr(p+1, path.size());
    res.empty() ? path = "/" : path = res;

    rescanDirectory();
    bool found = false;
    for (int i = 0; i < files->size(); i++) {
        if (files->at(i)->name == name) {
            found = true;
            break;
        }

        if (pos < rowsCount-1)
            pos++;
        else
            offset++;
    }

    if (!found) {
        pos = 0;
        offset = 0;
    }

}