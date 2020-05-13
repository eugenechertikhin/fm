//
// Created by Eugene Chertikhin on 03.05.2020.
//

#pragma once

#include <string>
#include <sstream>
#include <iterator>
#include <vector>

namespace util {

    class Utils {
    public:
        static std::string parentPath(std::string path) {
            size_t pos = path.find_last_of("\\/");
            std::string res = path.substr(0, pos);
            return res.empty() ? "/" : res;
        }

        static void split(std::vector<std::string> *tokens, const std::string &s, char delim) {
            std::string token;
            std::stringstream ss(s);
            while (std::getline(ss, token, delim)) {
                tokens->push_back(token);
            }
        }

        static void paddingLeft(std::string *str, int size) {
            while (str->size() < size)
                str->insert(0, " ");
        }

        static void paddingRight(std::string *str, int size) {
            while (str->size() < size)
                str->append(" ");
        }
    };
}