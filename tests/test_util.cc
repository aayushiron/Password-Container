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