#include <catch2/catch.hpp>

#include "core/password_container.h"
#include <fstream>
#include <sstream>

using passwordcontainer::PasswordContainer;
using std::ifstream;
using std::stringstream;

TEST_CASE("Tests for constructor") {
  SECTION("Throws error if offset is less than minimum") {
    REQUIRE_THROWS_AS(PasswordContainer(0, "key"), std::invalid_argument);
  }

  SECTION("Throws error if the key is an empty string") {
    REQUIRE_THROWS_AS(PasswordContainer(100, ""), std::invalid_argument);
  }

  SECTION("Doesn't throw error if all parameters are valid") {
    REQUIRE_NOTHROW(PasswordContainer(100, "key"));
  }
}

TEST_CASE("Tests for overloaded >> operator") {
  PasswordContainer container(100, "CorrectKey");

  SECTION("Throws error for bad data passed in") {
    ifstream file("../../../tests/resources/BadData.pwords");
    REQUIRE_THROWS_AS(file >> container, std::invalid_argument);
  }

  SECTION("Throws error for wrong key passed in") {
    ifstream file("../../../tests/resources/Data.pwords");
    container.SetKey("Key");
    REQUIRE_THROWS_AS(file >> container, std::invalid_argument);
  }

  SECTION("Stores correct data for the correct key passed in") {
    ifstream file("../../../tests/resources/Data.pwords");

    file >> container;

    std::vector<PasswordContainer::AccountDetails> accounts =
        container.GetAccounts();

    SECTION("Has correct number of accounts") {
      REQUIRE(container.GetAccounts().size() == 3);
    }

    SECTION("Has correct data for first account") {
      REQUIRE(accounts[0].name == "Account1");
      REQUIRE(accounts[0].username == "Username1");
      REQUIRE(accounts[0].password == "Password1");
    }

    SECTION("Has correct data for second account") {
      REQUIRE(accounts[1].name == "Account2");
      REQUIRE(accounts[1].username == "Username2");
      REQUIRE(accounts[1].password == "Password2");
    }

    SECTION("Has correct data for third account") {
      REQUIRE(accounts[2].name == "Account3");
      REQUIRE(accounts[2].username == "Username3");
      REQUIRE(accounts[2].password == "Password3");
    }
  }
}

TEST_CASE("Tests for overloaded << operator") {
  PasswordContainer container(100, "CorrectKey");
  ifstream file("../../../tests/resources/Data.pwords");
  file >> container;

  SECTION("Correctly encrypts the data in the container") {
    stringstream stream;
    stream << container;

    std::string correct_data = "26630030031231831131725021028631630231531129831"
        "0302250210281298316316320312315301250211266300300312318311317251210286"
        "31630231531129831030225121028129831631632031231530125121126630030031231"
        "8311317252210286316302315311298310302252210281298316316320312315301252";

    REQUIRE(stream.str() == correct_data);
  }

  SECTION("Correctly encrypts data when the key is changed") {
    container.SetKey("NewDifferentKey");
    stringstream stream;
    stream << container;

    std::string correct_data = "26529929931131731031624920928531530131431029730"
        "9301249209280297315315319311314300249210265299299311317310316250209285"
        "3153013143102973093012502092802973153153193113143002502102652992993113"
        "17310316251209285315301314310297309301251209280297315315319311314300251";

    REQUIRE(stream.str() == correct_data);
  }
}