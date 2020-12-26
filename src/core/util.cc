#include "core/util.h"

#include <sstream>
#include <string>

namespace util {

int ConvertStringToInt(const std::string& to_convert) {
  // Creates a new string stream and puts the passed in string into the string
  // stream
  std::stringstream string_stream;
  string_stream << to_convert;

  // Makes sure that the passed in string can be converted to an int
  int asInt;
  if (!(string_stream >> asInt)) {
    throw std::invalid_argument("Cannot convert\"" + to_convert + "\"to int.");
  }

  return asInt;
}

}  // namespace util