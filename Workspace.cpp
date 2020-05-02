//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include "Workspace.h"
#include <iostream>
#include <dirent.h>
#include "Directory.h"

using namespace std;

Workspace::Workspace(Config *pConfig) {
    this->config = pConfig;

    // colours
    init_pair(1, COLOR_WHITE, COLOR_BLUE); // main panel color
    init_pair(2, COLOR_YELLOW, COLOR_BLUE); // highline text at main panel
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    // colorText, colorBackground, colorDirectory, colorSelection, colorFile, colorExeFile, colorArchive, colorLink, colorSocket, colorBroken
    // colorMenuText, colorMenuBackground, colorMenuInput, colorMenuSelection, colorMenuHot
    // warningMenuText, warningMenuBackground, warningMenuSelection, warningMenuHot

}

WINDOW * Workspace::createWindow(int y, int x, int rows, int cols, int colour) {
    WINDOW *win = newwin(rows, cols, y, x);
    box(win, 0, 0);
    wbkgd(win, COLOR_PAIR(colour));

    return win;
}

void Workspace::fillWindow(WINDOW *win, PanelType type, ListMode mode, const string &path, bool active) {
    if ((type == FileList) || (type == Tree)) {

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
                for (int i = 0; i < config->getRows() - 1 - 3; i++) {
                    mvwaddch(win, i + 1, config->getCols() / 4 - 1, ACS_VLINE);
                }

                // print column name
                wattron(win, COLOR_PAIR(2));
                int sizeOfPart = config->getCols() / 2 /*left or right*/ / 2 /*2part*/;
                for (int i = 1; i <= 2 /*part*/; i++) {
                    mvwprintw(win, 1, (sizeOfPart*i) - (sizeOfPart / 2) /*center of part*/ - (strlen(n) / 2), n);
                }
                wattroff(win, COLOR_PAIR(2));

            } else if (mode == Custom) {
                // todo
            } else if (mode == Full) {
                // Name | Size | perm

                int sizeOfPart = config->getCols() / 2 - 10 - 10;
                for (int i = 0; i < config->getRows() - 1 - 3; i++) {
                    mvwaddch(win, i + 1, sizeOfPart - 1, ACS_VLINE);
                }

                for (int i = 0; i < config->getRows() - 1 - 3; i++) {
                    mvwaddch(win, i + 1, sizeOfPart + 10 - 1, ACS_VLINE);
                }

                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 1, sizeOfPart / 2 - (strlen(n)/2), n);
                mvwprintw(win, 1, sizeOfPart, s);
                mvwprintw(win, 1, sizeOfPart + 10, p);

                wattroff(win, COLOR_PAIR(2));
            }
        }
        mvwaddch(win, config->getRows() - 1 - 3, 0, ACS_LTEE);
        mvwhline(win, config->getRows() - 1 - 3, 1, ACS_HLINE, config->getCols() / 2 - 2);
        mvwaddch(win, config->getRows() - 1 - 3, config->getCols() / 2 - 1, ACS_RTEE);

        wattroff(win, COLOR_PAIR(1));
    }
}

void Workspace::printFiles(WINDOW *win, const string &path) {
    Directory *dir = new Directory(config);
    vector<FileEntry *> files = dir->getDirectory(path);
    mvwprintw(win, 0, config->getCols() / 2 - 7, " %d ", files.size());

    for (int i = 0; i < files.size(); i++) {
        // todo
        mvwprintw(win, 2 + i, 2, " %s\t%d\t%s", files[i]->name.c_str(), files[i]->size, files[i]->perm.c_str());
    }
}

//enum PanelType {FileList, QuckView, Info, Tree};
//enum ListMode {Full, Brief, Custom};
void Workspace::show() {
    bool ex = false;

    // temp
    config->setLeftPath("/");

    // show panels
    leftWindow = createWindow(0, 0, config->getRows() - 1, config->getCols() / 2, 1);
    fillWindow(leftWindow, config->getLeftPanelType(), config->getLeftPanelMode(), config->getLeftPath(), true);
    printFiles(leftWindow, config->getLeftPath());
    leftPanel = new_panel(leftWindow);

    rightWindow = createWindow(0, config->getCols() / 2, config->getRows() - 1, config->getCols() / 2, 1);
    fillWindow(rightWindow, config->getRightPanelType(), config->getRightPanelMode(), config->getRightPath(), false);
    printFiles(rightWindow, config->getRightPath());
    rightPanel = new_panel(rightWindow);

    set_panel_userptr(leftPanel, rightPanel);
    set_panel_userptr(rightPanel, leftPanel);

    // and path string
    commandString = config->getCurrentPath() + ' ' + config->getUserPromp() + ' ' + cmd + ' ';
    mvprintw(config->getRows()-1, 0, const_cast<char *>(commandString.c_str()));

    // current panel
    currentPanel = leftPanel;

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
                break;
            case KEY_DOWN:
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