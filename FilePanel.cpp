//
// Created by Eugene Chertikhin on 04.05.2020.
//

#include <algorithm>

#include "FilePanel.h"
#include "Colors.h"

FilePanel::FilePanel() {
    Colors::initColors();

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
    this->modeParams = params;
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

//void Workspace::fillWindow(WINDOW *win, PanelType type, ListMode mode, std::vector<std::string> *custom) {
//    if (type == FileList) {
//
//        if (type == FileList) {
//            // headers
//            char n[] = "Name";
//            char s[] = "Size";
//            char m[] = "Modify";
//            char a[] = "Access";
//            char c[] = "Create";
//            char p[] = "Perm";
//
//            wattron(win, COLOR_PAIR(1));
//            if (mode == Brief) {
//                for (int i = 0; i < config->getRows() - 1 - 3; i++)
//                    mvwaddch(win, i + 1, config->getCols() / 4 - 1, ACS_VLINE);
//
//                // print column name
//                wattron(win, COLOR_PAIR(2));
//                int sizeOfPart = config->getCols() / 2 /*left or right*/ / 2 /*2part*/;
//                for (int i = 1; i <= 2 /*part*/; i++)
//                    mvwprintw(win, 1, (sizeOfPart*i) - (sizeOfPart / 2) /*center of part*/ - (strlen(n) / 2), n);
//                wattroff(win, COLOR_PAIR(2));
//
//            } else if (mode == Custom) {
//                int sizeOfPart = config->getCols() / 2 - (custom->size() * (SmallColumnSize+1)) -1;
//                for (int i = 0; i < config->getRows() - 1 - 3; i++)
//                    mvwaddch(win, i + 1, sizeOfPart - 1, ACS_VLINE);
//
//                for(int j = 1; j < custom->size(); j++) {
//                    for (int i = 0; i < config->getRows() - 1 - 3; i++)
//                        mvwaddch(win, i + 1, sizeOfPart + (SmallColumnSize+1*j), ACS_VLINE);
//                }
//
//                wattron(win, COLOR_PAIR(2));
//                int i = 0;
//                for(auto const str: *custom) {
//                    if (i == 0) {
//                        mvwprintw(win, 1, sizeOfPart / 2 - (strlen(n) / 2), str.c_str());
//                        i++;
//                    } else {
//                        mvwprintw(win, 1, sizeOfPart + 1 + (SmallColumnSize+1*i) + ((SmallColumnSize - str.size())/2), str.c_str());
//                    }
//                }
//                wattroff(win, COLOR_PAIR(2));
//
//            } else if (mode == Full) {
//                int sizeOfPart = config->getCols() / 2 - (SmallColumnSize+1) - (SmallColumnSize+1) -1;
//                for (int i = 0; i < config->getRows() - 1 - 3; i++)
//                    mvwaddch(win, i + 1, sizeOfPart, ACS_VLINE);
//
//                for (int i = 0; i < config->getRows() - 1 - 3; i++)
//                    mvwaddch(win, i + 1, sizeOfPart + (SmallColumnSize + 1), ACS_VLINE);
//
//                wattron(win, COLOR_PAIR(2));
//                mvwprintw(win, 1, sizeOfPart / 2 - (strlen(n)/2), n);
//                mvwprintw(win, 1, sizeOfPart + 1 + ((SmallColumnSize - strlen(s))/2), s);
//                mvwprintw(win, 1, sizeOfPart + 1 + (SmallColumnSize+1) + ((SmallColumnSize - strlen(p))/2), p);
//
//                wattroff(win, COLOR_PAIR(2));
//            }
//        }
//        mvwaddch(win, config->getRows() - 1 - 3, 0, ACS_LTEE);
//        mvwhline(win, config->getRows() - 1 - 3, 1, ACS_HLINE, config->getCols() / 2 - 2);
//        mvwaddch(win, config->getRows() - 1 - 3, config->getCols() / 2 - 1, ACS_RTEE);
//
//        wattroff(win, COLOR_PAIR(1));
//    } else if (type == Tree) {
//        // todo
//    } else if (type == Info) {
//        // todo
//    } else if (type == QuickView) {
//        // todo
//    }
//}
//
//
//int Workspace::printFiles(WINDOW *win, Directory *dir, SortType sortOrder, ListMode listMode, int cursorLengh, int offset) {
//    std::vector<FileEntry *> *files = dir->getDirectory();
//
//    // files count in the directory
//    mvwprintw(win, 0, config->getCols() / 2 - 7, " %d ", files->size());
//
//    int i = 0;
//    for(auto const &entry: *files) {
//        if (i < offset) {
//            i++;
//            continue;
//        }
//
//        if (listMode == Full) {
//            int sizeOfPart = config->getCols() / 2 - (SmallColumnSize+1) - (SmallColumnSize+1) -1;
//
//            util::Utils::paddingRight(&entry->name, cursorLengh-1);
//            mvwprintw(win, 2 + i - offset, 2, "%s", entry->name.c_str());
//            std::string size = std::to_string(entry->size);
//            util::Utils::paddingLeft(&size, SmallColumnSize);
//            mvwprintw(win, 2 + i - offset, sizeOfPart+1, size.c_str());
//            mvwprintw(win, 2 + i - offset, sizeOfPart + SmallColumnSize+2, "%s", entry->perm.c_str());
//        } else if (listMode == Brief) {
//            util::Utils::paddingRight(&entry->name, cursorLengh-1);
//            mvwprintw(win, 2 + i - offset, 1, "%s", entry->name.c_str());
//        } else if (listMode == Custom) {
//            // todo
//        }
//        i++;
//        if ((i - offset) == config->getRowsInPanel())
//            return i - offset;
//    }
//
//    return i - offset;
//}

void FilePanel::redraw() {
    redrawwin(win);
    wrefresh(win);
}

void FilePanel::draw(int y, int x, int rows, int cols, bool colour) {
    win = newwin(rows, cols, y, x);
    box(win, 0, 0);
    if (colour)
        wbkgd(win, COLOR_PAIR(1));

    //    fillWindow(rightWindow, config->getRightType(), config->getRightMode(), rightCustomMode);

    directory = new Directory();
    files = directory->getDirectory(path, showDot);
    sortDirectory(files);

//    printFiles(rightWindow, rpd.dir, config->getRightSort(), config->getRightMode(), cursorLengh, 0);

    // show total files count
//    lpd.totalFiles = lpd.dir->getDirectory()->size();

    // showTotalSpace / showFreeSpace

    // print path at the header
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 0, 2, " %s ", const_cast<char*>(path.c_str()));
    wattroff(win, COLOR_PAIR(1));

//    if (config->getLeftPanelMode() == Full)
//        cursorLengh = config->getCols() / 2 - SmallColumnSize-2 - SmallColumnSize-2;
//    else if (config->getLeftPanelMode() == Brief)
//        cursorLengh = config->getCols() / 4 - 2;
//    else {
//        leftCustomMode->clear();
//        util::Utils::split(leftCustomMode, config->getLeftModeParams(), ' ');
//        cursorLengh = (leftCustomMode->size() - 1) * SmallColumnSize - 1 /**/;
//    }

    //    getRowsInPanel rows - 2 /* top size */ - 1 /* cmd line */ - 3 /* file info line */;

    // print cursor
//    mvwchgat(win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 3, NULL);

    wrefresh(win);
}

void FilePanel::hideCursor() {
    mvwchgat(win, 0, 2, path.size()+2, A_COLOR, 1, NULL);
    // todo print cursor
    wrefresh(win);
}
void FilePanel::showCursor() {
    mvwchgat(win, 0, 2, path.size()+2, A_COLOR, 3, NULL);
    // todo print cursor
    wrefresh(win);
}
