#include <catch2/catch.hpp>

#include "core/util.h"

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