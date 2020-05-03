//
// Created by Eugene Chertikhin on 03.05.2020.
//

#pragma once

#include <string>
#include <sstream>
#include <iterator>
#include <vector>

class Utils {
public:
    static void split(std::vector<std::string> *tokens, const std::string &s, char delim) {
        std::string token;
        std::stringstream ss(s);
        while(std::getline(ss, token, delim)) {
            tokens->push_back(token);
        }
    }
};
