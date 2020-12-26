#ifndef CORE_UTIL_H
#define CORE_UTIL_H

#include <string>
#include <vector>

namespace util {

// Converts the passed in string to an int.
//
// Takes in a string to_convert that is the string to be converted to an int.
//
// Throws an invalid_argument exception if the string cannot be converted to
// an int.
int ConvertStringToInt(const std::string& to_convert);

// Converts the passed in string to a string with all lowercase characters
//
// Takes in a string called to_convert that represents the string to be
// converted to lowercase.
std::string ConvertToLowerCase(const std::string& to_convert);

// Generates a random int between min and max
int GenerateRandomInt(int min, int max);

// Generates a random password with valid characters with the specified length.
std::string GenerateRandomPassword(size_t password_length);

// Generates a char* vector from an input string vector.
std::vector<char*> ConvertStringVecToCharVec(std::vector<std::string> &input);

// Copies the passed in string to the clipboard.
void CopyToClipboard(const std::string &s);

}  // namespace util

#endif  // CORE_UTIL_H
