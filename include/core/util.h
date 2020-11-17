#ifndef CORE_UTIL_H
#define CORE_UTIL_H

#include <string>

namespace util {

// Converts the passed in string to an int.
//
// Takes in a string to_convert that is the string to be converted to an int.
//
// Throws an invalid_argument exception if the string cannot be converted to
// an int.
int ConvertStringToInt(const std::string& to_convert);

}  // namespace util

#endif  // CORE_UTIL_H
