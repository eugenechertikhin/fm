//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include "Workspace.h"
#include <iostream>
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

WINDOW * Workspace::initWindow(int y, int x, int rows, int cols, int colour) {
    WINDOW *win = newwin(rows, cols, y, x);
    box(win, 0, 0);
    wbkgd(win, COLOR_PAIR(colour));

    return win;
}

void Workspace::fillInsideWindow(WINDOW *win, PanelType type, ListMode mode, string path) {
    if ((type == FileList) || (type == Tree)) {

        if (type == FileList) {

            // print path at the header
            wattron(win, COLOR_PAIR(3));
            mvwprintw(win, 0, 2, " %s ", const_cast<char*>(path.c_str()));
            wattroff(win, COLOR_PAIR(3));

            wattron(win, COLOR_PAIR(1));
            if (mode == Brief) {
                for (int i = 0; i < config->getRows() - 1 - 3; i++) {
                    mvwaddch(win, i + 1, config->getCols() / 4 - 1, ACS_VLINE);
                }

                // print column name
                string n("Name");
                wattron(win, COLOR_PAIR(2));
                int sizeOfPart = config->getCols() / 2 /*left or right*/ / 2 /*2part*/;
                for (int i = 1; i <= 2 /*part*/; i++) {
                    mvwprintw(win, 1, (sizeOfPart*i) - (sizeOfPart / 2) /*center of part*/ - (n.size() / 2), const_cast<char *>(n.c_str()));
                }
                wattroff(win, COLOR_PAIR(2));

            } else if (mode == Custom) {
                // todo
            } else if (mode == Full) {
                // Name | Size | MTime
            }

        }
        mvwaddch(win, config->getRows() - 1 - 3, 0, ACS_LTEE);
        mvwhline(win, config->getRows() - 1 - 3, 1, ACS_HLINE, config->getCols() / 2 - 2);
        mvwaddch(win, config->getRows() - 1 - 3, config->getCols() / 2 - 1, ACS_RTEE);

        wattroff(win, COLOR_PAIR(1));
    }
}

//enum PanelType {FileList, QuckView, Info, Tree};
//enum ListMode {Full, Brief, Custom};
void Workspace::show() {
    bool ex = false;

    // show panels
    leftWindow = initWindow(0, 0, config->getRows()-1, config->getCols()/2, 1);
    fillInsideWindow(leftWindow, config->getLeftPanelType(), config->getLeftPanelMode(), config->getLeftPath());
    leftPanel = new_panel(leftWindow);

    rightWindow = initWindow(0, config->getCols()/2, config->getRows()-1,config->getCols()/2, 1);
    fillInsideWindow(rightWindow, config->getRightPanelType(), config->getRightPanelMode(), config->getRightPath());
    rightPanel = new_panel(rightWindow);

    set_panel_userptr(leftPanel, rightPanel);
    set_panel_userptr(rightPanel, leftPanel);

    // and path string
    commandString = config->getCurrentPath() + ' ' + config->getUserPromp() + ' ' + cmd + ' ';
    mvprintw(config->getRows()-1, 0, const_cast<char *>(commandString.c_str()));

    // read content of directories
    Directory *dir = new Directory(config, config->getCurrentPath());
    dir->getDirectory(false);

    // put dirs into panels
    // todo

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