#include <catch2/catch.hpp>

#include "core/password_container.h"
#include <fstream>
#include <sstream>

using passwordcontainer::PasswordContainer;
using std::ifstream;
using std::stringstream;

void CheckForValidData(const PasswordContainer& container) {
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

  SECTION("Throws error for wrong offset passed in") {
    ifstream file("../../../tests/resources/Data.pwords");
    container.SetOffset(200);
    REQUIRE_THROWS_AS(file >> container, std::invalid_argument);
  }

  SECTION("Stores correct data for the correct key passed in") {
    ifstream file("../../../tests/resources/Data.pwords");
    file >> container;

    CheckForValidData(container);
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

  SECTION("Correctly encrypts data when the offset is changed") {
    container.SetOffset(200);
    stringstream stream;
    stream << container;

    std::string correct_data = "36640040041241841141735031038641640241541139841"
        "0402350310381398416416420412415401350311366400400412418411417351310386"
        "4164024154113984104023513103813984164164204124154013513113664004004124"
        "18411417352310386416402415411398410402352310381398416416420412415401352";

    REQUIRE(stream.str() == correct_data);
  }

  SECTION("Doesn't change data when generating encrypted data string") {
    stringstream stream;
    stream << container;

    CheckForValidData(container);
  }
}

TEST_CASE("Tests for SetKey") {
  PasswordContainer container(100, "CorrectKey");
  ifstream file("../../../tests/resources/Data.pwords");
  file >> container;

  SECTION("Throws error when passed in key is empty") {
    REQUIRE_THROWS_AS(container.SetKey(""), std::invalid_argument);
  }

  SECTION("Does nothing when passed in key is valid") {
    REQUIRE_NOTHROW(container.SetKey("NewKey"));
  }

  // This test is here because if the accounts are calculated whenever the
  // GetAccounts function is called, changing the key will change the
  // decryption of the data
  SECTION("Doesn't cause data to get corrupted") {
    container.SetKey("NewKey");

    CheckForValidData(container);
  }
}

TEST_CASE("Tests for SetOffset") {
  PasswordContainer container(100, "CorrectKey");
  ifstream file("../../../tests/resources/Data.pwords");
  file >> container;

  SECTION("Throws error when passed in offset is too small") {
    REQUIRE_THROWS_AS(container.SetOffset(99), std::invalid_argument);
  }

  SECTION("Does nothing when passed in offset is valid") {
    REQUIRE_NOTHROW(container.SetOffset(101));
  }

  // This test is here because if the accounts are calculated whenever the
  // GetAccounts function is called, changing the offset will change the
  // decryption of the data
  SECTION("Doesn't cause data to get corrupted") {
    container.SetOffset(200);

    CheckForValidData(container);
  }
}