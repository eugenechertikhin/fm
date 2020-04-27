#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <ncurses.h>
#include "version.h"
#include "Config.h"
#include "Workspace.h"

using namespace std;

int main(int argc, char **argv) {
    bool forceBlack = false;
    bool forceColor = false;
    int row, col;

    int opt;
    while ((opt = getopt(argc, argv, "hbcv")) != -1) {
        switch (opt) {
            case 'b':
                // notRead black interface
                forceBlack = true;
                break;
            case 'c':
                // notRead colour interface
                forceColor = true;
                break;
            case 'v':
                // print version and credits
                cout << FM_NAME <<endl << "Version: " << FM_VERSION << endl;
                exit(0);
            default:
                cout << "Usage: " << argv[0] << " -h -b -c -v" << endl
                     << " -b notRead black interface" << endl
                     << " -c notRead colour interface" << endl
                     << " -v version" << endl
                     << " -h this help" << endl;
                exit(-1);
        }
    };

    // allow cyrillic?
    setlocale(LC_ALL, "");

    // load config
    Config *config = new Config();
    config->loadConfig();

    if(forceColor)
        config->forceColor();
    else if(forceBlack)
        config->forceBlack();

    // init screen and show workspace
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();

    if(config->isColour())
        start_color();

    refresh();

    // get screen size
    getmaxyx(stdscr, row, col);
    config->setSize(row, col);

    // switch to workspace
    Workspace *w = new Workspace(config);
    w->show();

    delete w;
    delete config;

    endwin();

    return 0;
}
