#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <iostream>
#include <sys/stat.h>
#include "version.h"
#include "Config.h"
#include "Workspace.h"

int main(int argc, char **argv) {
    bool forceColor = true;
    int rows, cols;

    int opt;
    while ((opt = getopt(argc, argv, "hbcv")) != -1) {
        switch (opt) {
            case 'b':
                // notRead black interface
                forceColor = false;
                break;
            case 'c':
                // notRead colour interface
                forceColor = true;
                break;
            case 'v':
                // print version and credits
                std::cout << FM_NAME << std::endl << "Version: " << FM_VERSION << std::endl;
                exit(0);
            default:
                std::cout << "Usage: " << argv[0] << " -h -b -c -v" << std::endl
                     << " -b notRead black interface" << std::endl
                     << " -c notRead colour interface" << std::endl
                     << " -v version" << std::endl
                     << " -h this help" << std::endl;
                exit(-1);
        }
    };

    // allow cyrillic?
    setlocale(LC_ALL, "");

    // load config
    Config *config = new Config();
    config->loadConfig();

    uid_t uid = getuid();
    if (uid == 0)
        config->setRoot(true);
    else
        config->setRoot(false);

    // get current running path
    char cwd[PATH_MAX];
    config->setCurrentPath(getcwd(cwd, PATH_MAX));

    system("stty cbreak -echo");

    // init screen and show workspace
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();

    if(config->isColour())
        start_color();

    refresh();

    // get screen size
    getmaxyx(stdscr, rows, cols);

    // switch to workspace
    Workspace *w = new Workspace(config);
    w->show(rows, cols);
    config->saveConfig();

    delete w;
    delete config;

    endwin();
    system("stty cooked echo");

    return 0;
}
