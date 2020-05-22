//
// Created by Eugene Chertikhin on 23.05.2020.
//

#pragma once

#include <string>
#include <sstream>
#include <iterator>
#include <vector>

class Keys {
public:
    Keys(int y, int x, std::string label, int flag) {
        this->y = y;
        this->x = x;
        this->label = label;
        this->flag = flag;
    }

    void setNext(Keys *k) {
        next = k;
    }
    Keys *getNext() {
        return next;
    }
    void setPrev(Keys *k) {
        prev = k;
    }
    Keys *getPrev() {
        return prev;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    std::string getLabel() {
        return label;
    }
    int getStatus() {
        return flag;
    }

private:
    int x, y;
    int flag;
    std::string label;
    Keys *next, *prev;
};
