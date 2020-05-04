//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "Workspace.h"
#include "Utils.h"

#define SmallColumnSize 11

Workspace::Workspace(Config *pConfig) {
    config = pConfig;

    leftFilesOffset = 0;
    rightFilesOffset = 0;

    // colours
    init_pair(1, COLOR_WHITE, COLOR_BLUE); // main panel color
    init_pair(2, COLOR_YELLOW, COLOR_BLUE); // highline text at main panel
    init_pair(3, COLOR_BLACK, COLOR_CYAN);

    // colorText, colorBackground, colorDirectory, colorSelection, colorFile, colorExeFile, colorArchive, colorLink, colorSocket, colorBroken
    // colorMenuText, colorMenuBackground, colorMenuInput, colorMenuSelection, colorMenuHot
    // warningMenuText, warningMenuBackground, warningMenuSelection, warningMenuHot

}

Workspace::~Workspace() {
}

WINDOW *Workspace::createWindow(int y, int x, int rows, int cols, int colour) {
    WINDOW *win = newwin(rows, cols, y, x);
    box(win, 0, 0);
    wbkgd(win, COLOR_PAIR(colour));

    return win;
}

void Workspace::fillWindow(WINDOW *win, PanelType type, ListMode mode, std::vector<std::string> *custom) {
    if (type == FileList) {

        if (type == FileList) {
            // headers
            char n[] = "Name";
            char s[] = "Size";
            char m[] = "Modify";
            char a[] = "Access";
            char c[] = "Create";
            char p[] = "Perm";

            wattron(win, COLOR_PAIR(1));
            if (mode == Brief) {
                for (int i = 0; i < config->getRows() - 1 - 3; i++)
                    mvwaddch(win, i + 1, config->getCols() / 4 - 1, ACS_VLINE);

                // print column name
                wattron(win, COLOR_PAIR(2));
                int sizeOfPart = config->getCols() / 2 /*left or right*/ / 2 /*2part*/;
                for (int i = 1; i <= 2 /*part*/; i++)
                    mvwprintw(win, 1, (sizeOfPart*i) - (sizeOfPart / 2) /*center of part*/ - (strlen(n) / 2), n);
                wattroff(win, COLOR_PAIR(2));

            } else if (mode == Custom) {
                int sizeOfPart = config->getCols() / 2 - (custom->size() * (SmallColumnSize+1)) -1;
                for (int i = 0; i < config->getRows() - 1 - 3; i++)
                    mvwaddch(win, i + 1, sizeOfPart - 1, ACS_VLINE);

                for(int j = 1; j < custom->size(); j++) {
                    for (int i = 0; i < config->getRows() - 1 - 3; i++)
                        mvwaddch(win, i + 1, sizeOfPart + (SmallColumnSize+1*j), ACS_VLINE);
                }

                wattron(win, COLOR_PAIR(2));
                int i = 0;
                for(auto const str: *custom) {
                    if (i == 0) {
                        mvwprintw(win, 1, sizeOfPart / 2 - (strlen(n) / 2), str.c_str());
                        i++;
                    } else {
                        mvwprintw(win, 1, sizeOfPart + 1 + (SmallColumnSize+1*i) + ((SmallColumnSize - str.size())/2), str.c_str());
                    }
                }
                wattroff(win, COLOR_PAIR(2));

            } else if (mode == Full) {
                int sizeOfPart = config->getCols() / 2 - (SmallColumnSize+1) - (SmallColumnSize+1) -1;
                for (int i = 0; i < config->getRows() - 1 - 3; i++)
                    mvwaddch(win, i + 1, sizeOfPart, ACS_VLINE);

                for (int i = 0; i < config->getRows() - 1 - 3; i++)
                    mvwaddch(win, i + 1, sizeOfPart + (SmallColumnSize + 1), ACS_VLINE);

                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 1, sizeOfPart / 2 - (strlen(n)/2), n);
                mvwprintw(win, 1, sizeOfPart + 1 + ((SmallColumnSize - strlen(s))/2), s);
                mvwprintw(win, 1, sizeOfPart + 1 + (SmallColumnSize+1) + ((SmallColumnSize - strlen(p))/2), p);

                wattroff(win, COLOR_PAIR(2));
            }
        }
        mvwaddch(win, config->getRows() - 1 - 3, 0, ACS_LTEE);
        mvwhline(win, config->getRows() - 1 - 3, 1, ACS_HLINE, config->getCols() / 2 - 2);
        mvwaddch(win, config->getRows() - 1 - 3, config->getCols() / 2 - 1, ACS_RTEE);

        wattroff(win, COLOR_PAIR(1));
    } else if (type == Tree) {
        // todo
    } else if (type == Info) {
        // todo
    } else if (type == QuickView) {
        // todo
    }
}

int Workspace::printFiles(WINDOW *win, Directory *dir, SortOrder sortOrder, ListMode listMode, int cursorLengh, int offset) {
    std::vector<FileEntry *> *files = dir->getDirectory();

    // files count in the directory
    mvwprintw(win, 0, config->getCols() / 2 - 7, " %d ", files->size());

    // sort
    if (sortOrder != Unsorted) {
        if (sortOrder == Name) {
            sort(files->begin(), files->end(), [](const FileEntry *l, const FileEntry *r) {
                return l->name < r->name;
            });
        } else if (sortOrder == Ext) {
            // todo
        } else if (sortOrder == Size) {
            sort(files->begin(), files->end(), [](const FileEntry *l, const FileEntry *r) {
                return l->size < r->size;
            });
        } else if (sortOrder == MTime) {
            // todo
        } else if (sortOrder == ATime) {
            // todo
        } else if (sortOrder == CTime) {
            // todo
        }
    }

    int i = 0;
    for(auto const &entry: *files) {
        if (i < offset) {
            i++;
            continue;
        }

        if (listMode == Full) {
            int sizeOfPart = config->getCols() / 2 - (SmallColumnSize+1) - (SmallColumnSize+1) -1;

            // padding right
            while(entry->name.size() < (cursorLengh-1))
                entry->name.append(" ");

            mvwprintw(win, 2 + i - offset, 1, " %s", entry->name.c_str());
            mvwprintw(win, 2 + i - offset, sizeOfPart+1, " %d", entry->size);
            mvwprintw(win, 2 + i - offset, sizeOfPart + SmallColumnSize+2, " %s", entry->perm.c_str());
        } else if (listMode == Brief) {
            mvwprintw(win, 2 + i - offset, 1, " %s", entry->name.c_str());
        } else if (listMode == Custom) {
            // todo
        }
        i++;
        if ((i - offset) == config->getRowsInPanel())
            return i - offset;
    }

    return i - offset;
}

void Workspace::show() {
    bool ex = false;
    int cursorLengh = 0;

    // left panel
    PANEL_DATA lpd;
    lpd.leftRight = false;
    lpd.position = 0;
    lpd.offset = 0;
    lpd.dir = new Directory(config);
    lpd.dir->setPath(config->getLeftPath());
    lpd.totalFiles = lpd.dir->getDirectory()->size();

    if (config->getLeftPanelMode() == Full)
        cursorLengh = config->getCols() / 2 - SmallColumnSize-2 - SmallColumnSize-2;
    else if (config->getLeftPanelMode() == Brief)
        cursorLengh = config->getCols() / 4 - 2;
    else {
        leftCustomMode->clear();
        Utils::split(leftCustomMode, config->getLeftCustomMode(), ' ');
        cursorLengh = (leftCustomMode->size() - 1) * SmallColumnSize - 1 /**/;
    }
    lpd.cursorLengh = cursorLengh;

    WINDOW *leftWindow = createWindow(0, 0, config->getRows() - 1, config->getCols() / 2, 1);
    fillWindow(leftWindow, config->getLeftPanelType(), config->getLeftPanelMode(), leftCustomMode);
    printFiles(leftWindow, lpd.dir, config->getLeftPanelSort(), config->getLeftPanelMode(), cursorLengh, 0);
    PANEL *leftPanel = new_panel(leftWindow);

    // right panel
    PANEL_DATA rpd;
    rpd.leftRight = true;
    rpd.position = 0;
    rpd.offset = 0;
    rpd.dir = new Directory(config);
    rpd.dir->setPath(config->getRightPath());
    rpd.totalFiles = rpd.dir->getDirectory()->size();

    if (config->getRightPanelMode() == Full)
        cursorLengh = config->getCols() / 2 - SmallColumnSize-2 - SmallColumnSize-2;
    else if (config->getRightPanelMode() == Brief)
        cursorLengh = config->getCols() / 4 -  2;
    else {
        rightCustomMode->clear();
        Utils::split(rightCustomMode, config->getRightCustomMode(), ' ');
        cursorLengh = (rightCustomMode->size() - 1) * SmallColumnSize - 1 /**/;
    }
    rpd.cursorLengh = cursorLengh;

    WINDOW *rightWindow = createWindow(0, config->getCols() / 2, config->getRows() - 1, config->getCols() / 2, 1);
    fillWindow(rightWindow, config->getRightPanelType(), config->getRightPanelMode(), rightCustomMode);
    printFiles(rightWindow, rpd.dir, config->getRightPanelSort(), config->getRightPanelMode(), cursorLengh, 0);
    PANEL *rightPanel = new_panel(rightWindow);

    // set panels sources
    lpd.next = rightPanel;
    rpd.next = leftPanel;

    set_panel_userptr(leftPanel, &lpd);
    set_panel_userptr(rightPanel, &rpd);

    // current panel
    currentPanel = leftPanel;

    // print path at the header
    wattron(leftWindow, COLOR_PAIR(3));
    mvwprintw(leftWindow, 0, 2, " %s ", const_cast<char*>(config->getLeftPath().c_str()));
    wattroff(leftWindow, COLOR_PAIR(3));

    wattron(rightWindow, COLOR_PAIR(1));
    mvwprintw(rightWindow, 0, 2, " %s ", const_cast<char*>(config->getRightPath().c_str()));
    wattroff(rightWindow, COLOR_PAIR(0));

    // print cursor
    PANEL_DATA *d = (PANEL_DATA *)panel_userptr(currentPanel);
    mvwchgat(currentPanel->win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 3, NULL);

    // and path string
    commandString = config->getCurrentPath() + ' ' + config->getUserPromp() + ' ' + cmd + ' ';
    mvprintw(config->getRows()-1, 0, const_cast<char *>(commandString.c_str()));

    // update and show panels
    update_panels();
    doupdate();

    // read keypressed
    while (!ex) {
        int c = mvgetch(config->getRows()-1,commandString.size() - 1);
        switch (c) {
            // functional
            case KEY_F(1):
                break;
            case KEY_F(2):
                break;
            case KEY_F(3):
                break;
            case KEY_F(4):
                break;
            case KEY_F(5):
                break;
            case KEY_F(6):
                break;
            case KEY_F(7):
                break;
            case KEY_F(8):
                break;
            case KEY_F(9):
                break;
            case KEY_F(10):
                delete d->dir;
                d = (PANEL_DATA *)panel_userptr(d->next);
                delete d->dir;

                ex = true;
                break;

            // moving keys
            case 9: // TAB
                mvwchgat(currentPanel->win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 1, NULL);

                wattron(currentPanel->win, COLOR_PAIR(1));
                if (d->leftRight)
                    mvwprintw(currentPanel->win, 0, 2, " %s ", const_cast<char*>(config->getRightPath().c_str()));
                else
                    mvwprintw(currentPanel->win, 0, 2, " %s ", const_cast<char*>(config->getLeftPath().c_str()));
                wattroff(currentPanel->win, COLOR_PAIR(0));

                currentPanel = d->next;
                d = (PANEL_DATA *)panel_userptr(currentPanel);

                mvwchgat(currentPanel->win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 3, NULL);

                wattron(currentPanel->win, COLOR_PAIR(3));
                if (d->leftRight)
                    mvwprintw(currentPanel->win, 0, 2, " %s ", const_cast<char*>(config->getRightPath().c_str()));
                else
                    mvwprintw(currentPanel->win, 0, 2, " %s ", const_cast<char*>(config->getLeftPath().c_str()));
                wattroff(currentPanel->win, COLOR_PAIR(3));

                top_panel(currentPanel);
                break;
            case KEY_UP:
                if (d->position != 0) {
                    mvwchgat(currentPanel->win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 1, NULL);
                    d->position--;
                    mvwchgat(currentPanel->win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 3, NULL);
                } else if (d->offset > 0) {
                    mvwchgat(currentPanel->win, 2, 1, d->cursorLengh, A_COLOR, 1, NULL);
                    d->offset--;
                    if(d->leftRight)
                        printFiles(currentPanel->win, d->dir, config->getRightPanelSort(), config->getRightPanelMode(), d->cursorLengh, d->offset);
                    else
                        printFiles(currentPanel->win, d->dir, config->getLeftPanelSort(), config->getLeftPanelMode(), d->cursorLengh, d->offset);

                    mvwchgat(currentPanel->win, 2, 1, d->cursorLengh, A_COLOR, 3, NULL);
                }
                break;
            case KEY_DOWN:
                if ((d->position < d->totalFiles-1) && (d->position < config->getRowsInPanel()-1)) {
                    mvwchgat(currentPanel->win, 2 + d->position-d->offset, 1, d->cursorLengh, A_COLOR, 1, NULL);
                    d->position++;
                    mvwchgat(currentPanel->win, 2 + d->position-d->offset, 1, d->cursorLengh, A_COLOR, 3, NULL);
                } else if (((d->position+d->offset) != d->totalFiles-1) && (d->position == config->getRowsInPanel()-1)) {
                    mvwchgat(currentPanel->win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 1, NULL);
                    d->offset++;
                    if(d->leftRight)
                        printFiles(currentPanel->win, d->dir, config->getRightPanelSort(), config->getRightPanelMode(), d->cursorLengh, d->offset);
                    else
                        printFiles(currentPanel->win, d->dir, config->getLeftPanelSort(), config->getLeftPanelMode(), d->cursorLengh, d->offset);

                    mvwchgat(currentPanel->win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 3, NULL);
                }
                break;
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
                break;

            // redraw screen ^L
            // select file ^T
            // select files goup ^+
            // unselect file group ^-
            // swap panel ^U
            // quick change dir ^C
            // change attr (own,mod) ??? ^X
            // find file ^S
            // compare files ^D
            // show screen ^O

            // begin user line ^A
            // end user line ^E
            // remove last word ^W
            // removve all after cursor ^K
            // char right ^F
            // char left ^B

            // find ^/

            // keys for command line
            case 127: // backspace
                cmd.pop_back();
                break;
            case 10: // enter key
                if (cmd.size() < 1)
                    break;

                endwin();
                // append "cd `d->path`;" to begin of cmd
                system(const_cast<char *>(cmd.c_str()));
                std::cout << "Press any key to continue...";
                getch();
                refresh();

                // todo: save command to history

                // clear command line
                move(config->getRows()-1, 0);
                clrtoeol();
                cmd = "";
                break;
            default:
                cmd.push_back(c);
                break;
        }

        // print user prompt
        commandString = config->getCurrentPath() + ' ' + config->getUserPromp() + ' ' + cmd + ' ';
        mvprintw(config->getRows()-1, 0, const_cast<char *>(commandString.c_str()));

        update_panels();
        doupdate();
    }
}