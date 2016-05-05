#include "utils.h"
#include "cell.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

// return given mumber as a string
std::string str(long n) { std::ostringstream os; os << n; return os.str(); }

// return true iff given character is '0'..'9'
bool isdig(char c) { return isdigit(static_cast<unsigned char>(c)) != 0; }

bool isBool(const std::string & token) {
    if (token.length() == 2) {
        if (token[0] == '#' && (token[1] == 'f' || token[1] == 't'))
            return true;
        else return false;
    } else {
        return false;
    };
}

bool isCharacter(const std::string & token) {
    if (token[0] == '#' && token[1] == '\\') {

        if (token.length() > 3) {
            // if #\newline or #\space character
            std::string cr = token.substr(2, token.length() - 2);
            if ( cr == "newline" || cr == "space") {
                return true;
            } else {
                std::cout << "Unknown character" << std::endl;
                return false;
            }
        } else if (token.length() == 3) {
            return true;
        }
    } else {
        return false;
    }
}
// Errro when "test"", "test"s
// But allow "test\" a"
bool isString(const std::string & token) {
    const char * s = token.c_str();
    int count = 2;
    ++s;
    if (token[0] == '"') {
        while(*s != '"') {
            if (*s == '\\') {
                ++count;
                ++s;
                if (*s == '"') {
                    // ++count;
                    // continue;
                }
            }
             if (*s == 0) {
                std::cout << "non-terminated string literal" << std::endl;
                exit(1);
            }
            ++count;
            ++s;
        }
        if (count != token.length()) {
            std::cout << "error in string literal" << std::endl;
            exit(1);
        }

        return true;
    }

    return false;

}

std::string parseCharacter(const std::string & token) {
    std::string ret;
    if (token[3] == '\n'){
        ret = "#\\newline";
        return ret;
    }
    if (token[3] == ' ') {
        ret = "#\\space";
        return ret;
    }
    return token;
}

bool isNill(cell & c) {
    return c.val == "nil";
}
