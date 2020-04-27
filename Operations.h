//
// Created by Eugene Chertikhin on 27.04.2020.
//

#pragma once

class Operations {

public:
    Operations();
    ~Operations();

    void help();
    void view();
    void edit();
    void copy();
    void move();
    void mkdir();
    void rm();
    void conf();
    void exit();

    void chattr();
    void link();
    void quickChangeDir();

    void selectGroup();
    void unselectGroup();
    void invertSelection();

    void findFile();
    void swapPanels();
    void compareFiles();

    void commandHistory();
    
    // ftp link
    // shell link
    // open archive

private:

};
