//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "Workspace.h"

#define SmallColumnSize 10

using namespace std;

Workspace::Workspace(Config *pConfig) {
    this->config = pConfig;

    selection = 0;
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

WINDOW *Workspace::createWindow(int y, int x, int rows, int cols, int colour) {
    WINDOW *win = newwin(rows, cols, y, x);
    box(win, 0, 0);
    wbkgd(win, COLOR_PAIR(colour));

    return win;
}

void Workspace::fillWindow(WINDOW *win, PanelType type, ListMode mode, const string &path, bool active) {
    if (type == FileList) {

        if (type == FileList) {
            // headers
            char n[] = "Name";
            char s[] = "Size";
            char m[] = "Modify";
            char a[] = "Access";
            char c[] = "Create";
            char p[] = "Perm";

            // print path at the header
            if (active)
                wattron(win, COLOR_PAIR(3));
            else
                wattron(win, COLOR_PAIR(1));
            mvwprintw(win, 0, 2, " %s ", const_cast<char*>(path.c_str()));
            if (active)
                wattroff(win, COLOR_PAIR(3));
            else
                wattroff(win, COLOR_PAIR(0));

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
                // todo
            } else if (mode == Full) {
                int sizeOfPart = config->getCols() / 2 - SmallColumnSize-1 - SmallColumnSize-1;
                for (int i = 0; i < config->getRows() - 1 - 3; i++)
                    mvwaddch(win, i + 1, sizeOfPart - 1, ACS_VLINE);

                for (int i = 0; i < config->getRows() - 1 - 3; i++)
                    mvwaddch(win, i + 1, sizeOfPart + SmallColumnSize - 1, ACS_VLINE);

                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 1, sizeOfPart / 2 - (strlen(n)/2), n);
                mvwprintw(win, 1, sizeOfPart, s);
                mvwprintw(win, 1, sizeOfPart + SmallColumnSize, p);

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

void Workspace::printFiles(WINDOW *win, const string &path, SortOrder sortOrder, ListMode listMode) {
    Directory *dir = new Directory(config);
    vector<FileEntry *> *files = dir->getDirectory(path);

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
        if (listMode == Full) {
            int sizeOfPart = config->getCols() / 2 - SmallColumnSize-1 - SmallColumnSize-1;

            mvwprintw(win, 2 + i, 1, " %s", entry->name.c_str());
            mvwprintw(win, 2 + i, sizeOfPart, " %d", entry->size);
            mvwprintw(win, 2 + i, sizeOfPart + SmallColumnSize, " %s", entry->perm.c_str());
        } else if (listMode == Brief) {
            mvwprintw(win, 2 + i, 2, " %s", entry->name.c_str());
        } else if (listMode == Custom) {
            // todo
        }
        i++;
    }

    delete dir;
}

void Workspace::show() {
    bool ex = false;

    // show panels
    leftWindow = createWindow(0, 0, config->getRows() - 1, config->getCols() / 2, 1);
    fillWindow(leftWindow, config->getLeftPanelType(), config->getLeftPanelMode(), config->getLeftPath(), true);
    printFiles(leftWindow, config->getLeftPath(), config->getLeftPanelSort(), config->getLeftPanelMode());
    leftPanel = new_panel(leftWindow);

    rightWindow = createWindow(0, config->getCols() / 2, config->getRows() - 1, config->getCols() / 2, 1);
    fillWindow(rightWindow, config->getRightPanelType(), config->getRightPanelMode(), config->getRightPath(), false);
    printFiles(rightWindow, config->getRightPath(), config->getRightPanelSort(), config->getRightPanelMode());
    rightPanel = new_panel(rightWindow);

    set_panel_userptr(leftPanel, rightPanel);
    set_panel_userptr(rightPanel, leftPanel);

    // current panel
    currentPanel = leftPanel;

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
                ex = true;
                break;

            // moving keys
            case 9: // TAB
                currentPanel = (PANEL *)panel_userptr(currentPanel);
                top_panel(currentPanel);
                break;
            case KEY_UP:
                selection = (selection == 0) ? 0 : selection--;
                break;
            case KEY_DOWN:
                if (selection == config->getRowsInPanel()) {

                }
                selection = (selection == config->getRowsInPanel()) ? config->getRowsInPanel() : selection++;
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
                system(const_cast<char *>(cmd.c_str()));
                cout << "Press any key to continue...";
                cin.get();
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