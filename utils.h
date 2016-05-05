#ifndef _UTILS_
#define _UTILS_

#include <string>

// return given mumber as a string
std::string str(long n);

// return true iff given character is '0'..'9'
bool isdig(char c);
bool isBool(const std::string & token);
bool isCharacter(const std::string & token);

// Errro when "test"", "test"s
// But allow "test\" a"
bool isString(const std::string & token);

std::string parseCharacter(const std::string & token);

#endif
