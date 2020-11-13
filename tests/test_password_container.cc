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

  SECTION("Throws error if there is no data in the container") {
    stringstream stream;
    REQUIRE_THROWS_AS(stream << container, std::logic_error);
  }

  SECTION("Correctly encrypts the data in the container") {
    ifstream file("../../../tests/resources/Data.pwords");
    stringstream stream;
    file >> container;
    // TODO: Add correct string representation into test
  }
}