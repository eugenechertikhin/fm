//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include <iostream>
#include <vector>
#include "Workspace.h"
#include "Window.h"

Workspace::Workspace(Config *pConfig) {
    config = pConfig;
}

Workspace::~Workspace() {
}

void Workspace::show(int rows, int cols) {
    bool ex = false;

    FilePanel *left = new FilePanel();
    left->setPath(config->getLeftPath());
    left->setMode(config->getLeftMode(), config->getLeftModeParams());
    left->setSort(config->getLeftSort(), config->getLeftSortOrder());
    left->setType(config->getLeftType());
    left->setShowDot(config->isShowDot());

    left->draw(0, 0, rows - 1, cols / 2, config->isColour());

    FilePanel *right = new FilePanel();
    right->setPath(config->getRightPath());
    right->setMode(config->getRightMode(), config->getRightModeParams());
    right->setSort(config->getRightSort(), config->getRightSortOrder());
    right->setType(config->getRightType());
    right->setShowDot(config->isShowDot());

    right->draw(0, cols / 2, rows - 1, cols / 2, config->isColour());

    left->setNext(right);
    right->setNext(left);

    current = left;
    current->showCursor();

    // is it required?
    doupdate();

    // read keypressed
    while (!ex) {
        move(rows-1, 0);
        clrtoeol();

        std::string s(current->getPath() + ' ' + config->getUserPromp() + ' ' + cmd);
        mvprintw(rows-1, 0, const_cast<char *>(s.c_str()));

        int c = mvgetch(rows-1,s.size());
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
            case KEY_F(10): {
                if (config->isConfirmExit()) {
                    // todo move it to another class
                    Window *w = new Window();
                    w->draw(rows/2 - 3, cols/2 - 14, 5, 28, 4);
                    mvprintw(rows/2-2, cols/2-9, "Exit. Are you sure ?");
                    mvprintw(rows/2, cols/2-7, "Yes");
                    mvprintw(rows/2, cols/2+7, "No");
                    int c = mvgetch(rows/2, cols/2-5);
                    if (c == 'y' || c == 'Y')
                        ex = true;
                    delete w;
                    left->redraw();
                    right->redraw();
                } else {
                    ex = true;
                }
                break;
            }

            // moving keys
            case 9: // TAB
                current->hideCursor();
                current = current->getNext();
                current->showCursor();
                break;
            case KEY_UP:
//                if (d->position != 0) {
//                    mvwchgat(currentPanel->win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 1, NULL);
//                    d->position--;
//                    mvwchgat(currentPanel->win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 3, NULL);
//                } else if (d->offset > 0) {
//                    mvwchgat(currentPanel->win, 2, 1, d->cursorLengh, A_COLOR, 1, NULL);
//                    d->offset--;
//                    if(d->leftRight)
//                        printFiles(currentPanel->win, d->dir, config->getRightSort(), config->getRightMode(), d->cursorLengh, d->offset);
//                    else
//                        printFiles(currentPanel->win, d->dir, config->getLeftSort(), config->getLeftMode(), d->cursorLengh, d->offset);
//
//                    mvwchgat(currentPanel->win, 2, 1, d->cursorLengh, A_COLOR, 3, NULL);
//                }
                break;
            case KEY_DOWN:
//                if ((d->position < d->totalFiles-1) && (d->position < config->getRowsInPanel()-1)) {
//                    mvwchgat(currentPanel->win, 2 + d->position-d->offset, 1, d->cursorLengh, A_COLOR, 1, NULL);
//                    d->position++;
//                    mvwchgat(currentPanel->win, 2 + d->position-d->offset, 1, d->cursorLengh, A_COLOR, 3, NULL);
//                } else if (((d->position+d->offset) != d->totalFiles-1) && (d->position == config->getRowsInPanel()-1)) {
//                    mvwchgat(currentPanel->win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 1, NULL);
//                    d->offset++;
//                    if(d->leftRight)
//                        printFiles(currentPanel->win, d->dir, config->getRightSort(), config->getRightMode(), d->cursorLengh, d->offset);
//                    else
//                        printFiles(currentPanel->win, d->dir, config->getLeftSort(), config->getLeftMode(), d->cursorLengh, d->offset);
//
//                    mvwchgat(currentPanel->win, 2 + d->position, 1, d->cursorLengh, A_COLOR, 3, NULL);
//                }
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
            // history window ^H

            // bash commands
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
                if (cmd.size() < 1) {
                    // try to change direrctory or run file
                    break;
                }

                endwin();
                // todo? append "cd `d->path`;" to begin of cmd
                system(const_cast<char *>(cmd.c_str()));
                std::cout << "Press enter to continue...";
                getch();
                refresh();

                // todo: save command to history

                // clear command line
                cmd = "";

                break;
            default:
                cmd.push_back(c);
                break;
        }

        doupdate();
    }
}