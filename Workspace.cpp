//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include "Workspace.h"

using namespace std;

Workspace::Workspace(Config *pConfig) {
    this->config = pConfig;
}

WINDOW * Workspace::initWindow(int y, int x, int rows, int cols, int colour) {
    WINDOW *win = newwin(rows, cols, y, x);
    box(win, 0, 0);

    wattron(win, COLOR_PAIR(colour));
    mvwaddch(win, rows -3, 0, ACS_LTEE);
    mvwhline(win, rows -3, 1, ACS_HLINE, cols - 2);
    mvwaddch(win, rows -3, cols - 1, ACS_RTEE);
    wattroff(win, COLOR_PAIR(colour));
    wbkgd(win, COLOR_PAIR(1));

    refresh();

    return win;
}

void Workspace::show() {
    bool ex = false;

    // colours
    init_pair(1, COLOR_WHITE, COLOR_BLUE); // main panel color

    // show panels
    leftWindow = initWindow(0, 0, config->getRows()-1, config->getCols()/2, 1);
    rightWindow = initWindow(0, config->getCols()/2, config->getRows()-1,config->getCols()/2, 1);

    leftPanel = new_panel(leftWindow);
    rightPanel = new_panel(rightWindow);

    set_panel_userptr(leftPanel, rightPanel);
    set_panel_userptr(rightPanel, leftPanel);

    // print panel path
//    mvprintw(0, 2, const_cast<char*>(title.c_str()));
    mvwprintw(leftWindow, 0, 2, " left ");
    mvwprintw(rightWindow, 0, 2, " right ");

    // print user prompt
//    mvprintw(config->getRows(), 0, "~ %c ", config->getUserPromp());
    mvprintw(config->getRows()-1, 0, "~ $ ");
    doupdate();

    // read content of directories

    // put dirs into panels

    // current panel
    currentPanel = leftPanel;

    /* Update the stacking order. 2nd panel will be on top */
    update_panels();

    /* Show it on the screen */
    doupdate();

    // read keypressed
    string userInput;

    while (!ex) {
        int c = getch();
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

            // action
            // redraw screen ^L
            // select file ^T
            // select files goup ^+
            // unselect file group ^-
            // swap panel ^U
            // get inputChar || quick change dir ^C
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
            case KEY_BACKSPACE:
                break;
            case KEY_ENTER:
                break;
            default:
                break;
        }
        update_panels();
        doupdate();
    }

    // program should terminate
    return;
}