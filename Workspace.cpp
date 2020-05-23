//
// Created by Eugene Chertikhin on 26.04.2020.
//

#include <iostream>
#include "Window.h"
#include "Workspace.h"
#include "WindowHelp.h"
#include "WindowView.h"
#include "WindowEdit.h"
#include "WindowExit.h"
#include "Colors.h"
#include "Directory.h"

Workspace::Workspace(Config *pConfig) {
    config = pConfig;

    keyBar = new std::vector<std::string>;
    keyBar->push_back("Help");
    keyBar->push_back("Menu");
    keyBar->push_back("View");
    keyBar->push_back("Edit");
    keyBar->push_back("Copy");
    keyBar->push_back("Move");
    keyBar->push_back("MkDir");
    keyBar->push_back("Remove");
    keyBar->push_back("Config");
    keyBar->push_back("Quit");
}

Workspace::~Workspace() {
}

void Workspace::show(int rows, int cols) {
    bool ex = false;
    int minus = 1;  // for path

    if (config->isShowKeyBar())
        minus++;

    if (config->isShowMenuBar())
        minus++;

    FilePanel *left = new FilePanel();
    left->setPath(config->getLeftPath());
    left->setMode(config->getLeftMode(), config->getLeftModeParams());
    left->setSort(config->getLeftSort(), config->getLeftSortOrder());
    left->setType(config->getLeftType());
    left->setShowDot(config->isShowDot());
    left->draw(0, 0, rows-minus, cols/2, config->isColour());

    FilePanel *right = new FilePanel();
    right->setPath(config->getRightPath());
    right->setMode(config->getRightMode(), config->getRightModeParams());
    right->setSort(config->getRightSort(), config->getRightSortOrder());
    right->setType(config->getRightType());
    right->setShowDot(config->isShowDot());
    right->draw(0, cols/2, rows-minus, cols / 2, config->isColour());

    left->setNext(right);
    right->setNext(left);

    current = left;
    current->showCursor(true);

    if (config->isShowKeyBar())
        showKeyBar(rows-1, keyBar);

    // read keypressed
    while (!ex) {
        move(rows-minus, 0);
        clrtoeol();

        std::string s(current->getPath() + ' ' + config->getUserPromp() + ' ' + cmd);
        mvprintw(rows-minus, 0, const_cast<char *>(s.c_str()));

        int c = mvgetch(rows-minus,s.size());
        switch (c) {
            // functional
            case KEY_F(1): {
                    WindowHelp *w = new WindowHelp(5, 20, rows - 10, cols - 40);
                    w->draw(WHITE_ON_BLUE);
                    delete w;
                    left->update();
                    right->update();
                }
                break;
            case KEY_F(2):
                break;
            case KEY_F(3): {
                    FileEntry *f = current->getCurrentFile();
                    if (f->type == regular) {
                        std::string file = current->getPath() + "/" + f->name;
                        if (config->isInternalView()) {
                            try {
                                WindowView *w = new WindowView(file);
                                w->draw(0, 0, rows - 1, cols, WHITE_ON_BLUE);
                                delete w;
                            } catch (const std::exception &e) {
                                ;
                            }
                        } else {
                            endwin();

                            std::string pager = config->getViewer() + " " + file;
                            system(const_cast<char *>(pager.c_str()));

                            current->rescanDirectory();
                            current->showCursor(true);
                        }
                        showKeyBar(rows-1, keyBar);
                        left->update();
                        right->update();
                    } else if (f->type == directory) {
                        current->enter();
                    }
                }
                break;
            case KEY_F(4): {
                    FileEntry *f = current->getCurrentFile();
                    if (f->type == regular) {
                        std::string file = current->getPath() + "/" + f->name;
                        if (config->isInternalEdit()) {
                            WindowEdit *w = new WindowEdit();
                            w->draw(0, 0, rows - 1, cols, WHITE_ON_BLUE, file);
                            delete w;
                        } else {
                            endwin();

                            std::string edit = config->getEditor() + " " + file;
                            system(const_cast<char *>(edit.c_str()));

                            current->rescanDirectory();
                            current->showCursor(true);
                        }
                        showKeyBar(rows-1, keyBar);
                        left->update();
                        right->update();
                    }
                }
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
                        WindowExit *w = new WindowExit(rows/2, cols/2, 5, 45);
                        ex = w->draw(BLACK_ON_GREY);
                        delete w;
                        left->update();
                        right->update();
                    } else {
                        ex = true;
                    }
                }
                break;

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

            // screen commannds
            case 12: // redraw screen ^L
                current->update();
                current->getNext()->update();
                doupdate();
                break;
            case 20: // select file ^T
                break;
            case 61: // select files goup ^+
                break;
            case 31: // unselect file group ^-
                break;
            case 21: // swap panel ^U
                break;
            case 3: // quick change dir ^C
                break;
            case 24: // change attr (own,mod) ??? ^X
                break;
            case 19: // find file ^S
                break;
            case 4: // compare files ^D
                break;
            case 15: // show screen ^O
                endwin();
                getchar();
                fflush(stdin);
                break;
            case 25:  // history window ^H
                break;
            case 28: // find ^H
                break;
            case 18: // re-read directory ^R
                current->clear();
                current->printInside();
                current->rescanDirectory();
                current->showCursor(true);
                doupdate();
                break;

            // bash commands
            case 1: // begin user line ^A
                break;
            case 5: // end user line ^E
                break;
            case 23: // remove last word ^W
                break;
            case 11: // remove all after cursor ^K
                break;
            case 6: // char right ^F
                break;
            case 2: // char left ^B
                break;

            case 127: // backspace
                cmd.pop_back();
                break;
            case 10: { // enter key
                    if (cmd.size() < 1) {
                        current->enter();
                        break;
                    }
                    endwin();

                    std::string s = "cd " + current->getPath() + "; " + cmd;
                    system(const_cast<char *>(s.c_str()));

                    if (config->isConfirmExecute()) {
                        std::cout << "Press enter to continue...";
                        fflush(stdout);
                        getchar();
                        fflush(stdin);
                    }
                    current->rescanDirectory();
                    current->getNext()->rescanDirectory();
                    current->showCursor(true);

                    config->getHistory()->push_back(cmd);

                    // clear command line
                    cmd = "";
                }
                break;
            default:
                if (keyname(c)[0] != '^' || c != 8)
                    cmd.push_back(c);
                break;
        }

        doupdate();
    }
    delete left;
    delete right;
}