//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include <iostream>
#include <vector>
#include "Workspace.h"
#include "WindowView.h"
#include "WindowExit.h"
#include "Colors.h"
#include "Directory.h"
#include "KeyBar.h"

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
    current->showCursor(true);

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
                if (true) {
                    FileEntry *f = current->getCurrentFile();
                    WindowView *w = new WindowView();
                    w->draw(0, 0, rows-1, cols, WHITE_ON_BLUE, f->name);
                    delete w;
                    left->redraw();
                    right->redraw();
                }
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
                    WindowExit *w = new WindowExit();
                    ex = w->draw(5, 28, rows/2 - 3, cols/2 - 14, BLACK_ON_GREY);
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
                current->hideCursor(true);
                current = current->getNext();
                current->showCursor(true);
                break;
            case KEY_UP:
                current->moveUp();
                break;
            case KEY_DOWN:
                current->moveDown();
                break;
            case KEY_LEFT:
                current->moveLeft();
                break;
            case KEY_RIGHT:
                current->moveRight();
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
                    current->enter();
                    break;
                }

                endwin();
                // todo? append "cd `d->path`;" to begin of cmd

                system(const_cast<char *>(cmd.c_str()));
                if (config->isConfirmExecute()) {
                    std::cout << "Press enter to continue...";
                    getch();
                }
                current->rescanDirectory();
                current->showCursor(false);

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
    delete left;
    delete right;
}