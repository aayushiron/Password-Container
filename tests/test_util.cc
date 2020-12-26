#include <rpc.h>

#include <catch2/catch.hpp>

#include "core/util.h"

// Code from:
// https://stackoverflow.com/questions/14762456/getclipboarddatacf-text
bool ClipboardHasString(const std::string& clipboard_string) {
  // Try opening the clipboard
  if (!OpenClipboard(nullptr)) {
    return false;
  }

  // Get handle of clipboard object for ANSI text
  HANDLE hData = GetClipboardData(CF_TEXT);
  if (hData == nullptr) {
    CloseClipboard();
    return false;
  }

  // Lock the handle to get the actual text pointer
  char * pszText = static_cast<char*>( GlobalLock(hData) );
  if (pszText == nullptr) {
    GlobalUnlock( hData );
    CloseClipboard();
    return false;
  }

  // Save text in a string class instance
  std::string text( pszText );

  // Release the lock
  GlobalUnlock( hData );

  // Release the clipboard
  CloseClipboard();

  return text == clipboard_string;
}

TEST_CASE("Tests for ConvertStringToInt") {
  SECTION("Converts negative int representation correctly") {
    REQUIRE(util::ConvertStringToInt("-1") == -1);
  }

  SECTION("Converts positive int representation correctly") {
    REQUIRE(util::ConvertStringToInt("1") == 1);
  }

  SECTION("Converts 0 int representation correctly") {
    REQUIRE(util::ConvertStringToInt("0") == 0);
  }

  SECTION("Throws error for string with non integer characters") {
    REQUIRE_THROWS_AS(util::ConvertStringToInt("ascii1"),
                      std::invalid_argument);
  }
}

TEST_CASE("Tests for ConvertToLowerCase") {
  SECTION("Lowercase string remains lowercase") {
    REQUIRE("lowercase" == util::ConvertToLowerCase("lowercase"));
  }

  SECTION("Uppercase string is converted to lowercase") {
    REQUIRE("uppercase" == util::ConvertToLowerCase("UPPERCASE"));
  }

  SECTION("Mixed case string is converted to lowercase") {
    REQUIRE("mixed case" == util::ConvertToLowerCase("MiXeD CaSe"));
  }

  SECTION("Empty string remains as an empty string") {
    REQUIRE("" == util::ConvertToLowerCase(""));
  }

  SECTION("String with only integers doesn't change") {
    REQUIRE("11037" == util::ConvertToLowerCase("11037"));
  }
}

TEST_CASE("Testing GenerateRandomInt") {
  SECTION("Testing with negative bounds") {
    for (int test_index = 0; test_index < 1000; test_index++) {
      double random = util::GenerateRandomInt(-5, -1);
      REQUIRE(random >= -5);
      REQUIRE(random <= -1);
    }
  }

  SECTION("Testing with positive bounds") {
    for (int test_index = 0; test_index < 1000; test_index++) {
      double random = util::GenerateRandomInt(1, 5);
      REQUIRE(random >= 1);
      REQUIRE(random <= 5);
    }
  }

  SECTION("Testing with one positive and one negative bound") {
    for (int test_index = 0; test_index < 1000; test_index++) {
      double random = util::GenerateRandomInt(-5, 5);
      REQUIRE(random >= -5);
      REQUIRE(random <= 5);
    }
  }

  SECTION("Returns bound if the bounds are equal to each other") {
    for (int test_index = 0; test_index < 1000; test_index++) {
      double random = util::GenerateRandomInt(10, 10);
      REQUIRE(random >= 10);
      REQUIRE(random <= 10);
    }
  }

  SECTION("Throws error for invalid bounds") {
    REQUIRE_THROWS_AS(util::GenerateRandomInt(11037, -11037),
                      std::invalid_argument);
  }
}

TEST_CASE("Tests for GenerateRandomPassword") {
  SECTION("Returns empty string for a size of 0") {
    REQUIRE(util::GenerateRandomPassword(0).empty());
  }

  SECTION("Generated passwords have correct password size") {
    for (size_t index = 0; index < 100; index++) {
      REQUIRE(util::GenerateRandomPassword(index).size() == index);
    }
  }

  SECTION("Generated passwords only have valid characters") {
    for (size_t index = 0; index < 10; index++) {
      std::string password = util::GenerateRandomPassword(20);

      // Loops through all characters in the password and makes sure it is valid
      for (char c : password) {
        bool is_valid_character = c >= ' ' && c <= '~';
        REQUIRE(is_valid_character);
      }
    }
  }
}

TEST_CASE("Tests for ConvertStringVecToCharVec") {
  SECTION("Only has one nullptr when converting an empty vector") {
    std::vector<std::string> input;
    REQUIRE(util::ConvertStringVecToCharVec(input).size() == 1);
    REQUIRE(util::ConvertStringVecToCharVec(input)[0] == nullptr);
  }

  SECTION("Correctly converts the string a string vector to a char* vector") {
    std::vector<std::string> input = {"one", "two", "3"};
    REQUIRE(util::ConvertStringVecToCharVec(input).size() == 4);
    REQUIRE(util::ConvertStringVecToCharVec(input)[0] == &input[0][0]);
    REQUIRE(util::ConvertStringVecToCharVec(input)[1] == &input[1][0]);
    REQUIRE(util::ConvertStringVecToCharVec(input)[2] == &input[2][0]);
    REQUIRE(util::ConvertStringVecToCharVec(input)[3] == nullptr);
  }
}

TEST_CASE("Tests for CopyToClipboard") {
  SECTION("Puts empty string into clipboard") {
    REQUIRE_NOTHROW(util::CopyToClipboard(""));
    REQUIRE(ClipboardHasString(""));
  }

  SECTION("Puts populated string into clipboard") {
    REQUIRE_NOTHROW(util::CopyToClipboard("populatEd string 1"));
    REQUIRE(ClipboardHasString("populatEd string 1"));
  }
}