#include "core/util.h"

#include <random>
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

std::string ConvertToLowerCase(const std::string& to_convert) {
  std::string lower_case_string;

  // Loops through all characters and converts them to lower case
  for (char character : to_convert) {
    lower_case_string += tolower(character);
  }

  return lower_case_string;
}

// https://www.delftstack.com/howto/cpp/how-to-generate-random-doubles-cpp/
int GenerateRandomInt(int min, int max) {
  if (min == max) {
    return min;  // Only one possible value
  } else if (max < min) {
    throw std::invalid_argument("The passed in bounds are invalid!");
  }

  // Creates a random double between min and max and casts it to an int
  std::random_device random;
  std::default_random_engine engine(random());
  std::uniform_real_distribution<double> distribution(min, max);
  return static_cast<int>(distribution(engine));
}

std::string GenerateRandomPassword(size_t password_length) {
  std::string generated_password;

  // Adds password_length random chars to the password
  for (size_t index = 0; index < password_length; index++) {
    // Adding 1 to ~ since GenerateRandomInt's upper bound is exclusive
    generated_password += static_cast<char>(GenerateRandomInt('!', '~' + 1));
  }

  return generated_password;
}

}  // namespace util