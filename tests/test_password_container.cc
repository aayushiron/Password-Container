#include <catch2/catch.hpp>
#include <fstream>
#include <sstream>

#include "core/password_container.h"

using passwordcontainer::PasswordContainer;
using std::ifstream;
using std::stringstream;

bool HasValidData(const PasswordContainer& container) {
  std::vector<PasswordContainer::AccountDetails> accounts =
      container.GetAccounts();

  bool correct_first_account = accounts[0].account_name == "Account1" &&
                               accounts[0].username == "Username1" &&
                               accounts[0].password == "Password1";

  bool correct_second_account = accounts[1].account_name == "Account2" &&
                                accounts[1].username == "Username2" &&
                                accounts[1].password == "Password2";

  bool correct_third_account = accounts[2].account_name == "Account3" &&
                               accounts[2].username == "Username3" &&
                               accounts[2].password == "Password3";

  return correct_first_account && correct_second_account &&
         correct_third_account;
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
    container.SetCryptographerKey("Key");
    REQUIRE_THROWS_AS(file >> container, std::invalid_argument);
  }

  SECTION("Throws error for wrong offset passed in") {
    ifstream file("../../../tests/resources/Data.pwords");
    container.SetCryptographerOffset(200);
    REQUIRE_THROWS_AS(file >> container, std::invalid_argument);
  }

  SECTION("Stores correct data for the correct key passed in") {
    ifstream file("../../../tests/resources/Data.pwords");
    file >> container;

    REQUIRE(HasValidData(container));
  }
}

TEST_CASE("Tests for overloaded << operator") {
  PasswordContainer container(100, "CorrectKey");

  SECTION("Returns empty string when there is no data in the container") {
    stringstream stream;
    stream << container;

    REQUIRE(stream.str() == "");
  }

  ifstream file("../../../tests/resources/Data.pwords");
  file >> container;

  SECTION("Correctly encrypts the data in the container") {
    stringstream stream;
    stream << container;

    std::string correct_data =
        "26630030031231831131725021028631630231531129831"
        "0302250210281298316316320312315301250211266300300312318311317251210286"
        "3163023153112983103022512102812983163163203123153012512112663003003123"
        "1"
        "831131725221028631630231531129831030225221028129831631632031231530125"
        "2";

    REQUIRE(stream.str() == correct_data);
  }

  SECTION("Correctly encrypts data when the key is changed") {
    container.SetCryptographerKey("NewDifferentKey");
    stringstream stream;
    stream << container;

    std::string correct_data =
        "26529929931131731031624920928531530131431029730"
        "9301249209280297315315319311314300249210265299299311317310316250209285"
        "3153013143102973093012502092802973153153193113143002502102652992993113"
        "1731031625120928531530131431029730930125120928029731531531931131430025"
        "1";

    REQUIRE(stream.str() == correct_data);
  }

  SECTION("Correctly encrypts data when the offset is changed") {
    container.SetCryptographerOffset(200);
    stringstream stream;
    stream << container;

    std::string correct_data =
        "36640040041241841141735031038641640241541139841"
        "0402350310381398416416420412415401350311366400400412418411417351310386"
        "4164024154113984104023513103813984164164204124154013513113664004004124"
        "1841141735231038641640241541139841040235231038139841641642041241540135"
        "2";

    REQUIRE(stream.str() == correct_data);
  }

  SECTION("Doesn't change data when generating encrypted data string") {
    stringstream stream;
    stream << container;

    REQUIRE(HasValidData(container));
  }
}

TEST_CASE("Tests for SetCryptographerKey") {
  PasswordContainer container(100, "CorrectKey");
  ifstream file("../../../tests/resources/Data.pwords");
  file >> container;

  SECTION("Throws error when passed in key is empty") {
    REQUIRE_THROWS_AS(container.SetCryptographerKey(""), std::invalid_argument);
  }

  SECTION("Does nothing when passed in key is valid") {
    REQUIRE_NOTHROW(container.SetCryptographerKey("NewKey"));
  }

  // This test is here because if the accounts are calculated whenever the
  // GetAccounts function is called, changing the key will change the
  // decryption of the data
  SECTION("Doesn't cause data to get corrupted") {
    container.SetCryptographerKey("NewKey");

    REQUIRE(HasValidData(container));
  }
}

TEST_CASE("Tests for SetCryptographerOffset") {
  PasswordContainer container(100, "CorrectKey");
  ifstream file("../../../tests/resources/Data.pwords");
  file >> container;

  SECTION("Throws error when passed in offset is too small") {
    REQUIRE_THROWS_AS(container.SetCryptographerOffset(99),
                      std::invalid_argument);
  }

  SECTION("Does nothing when passed in offset is valid") {
    REQUIRE_NOTHROW(container.SetCryptographerOffset(101));
  }

  // This test is here because if the accounts are calculated whenever the
  // GetAccounts function is called, changing the offset will change the
  // decryption of the data
  SECTION("Doesn't cause data to get corrupted") {
    container.SetCryptographerOffset(200);

    REQUIRE(HasValidData(container));
  }
}

TEST_CASE("Tests for AddAccount") {
  PasswordContainer container(100, "CorrectKey");

  SECTION("Adds account to empty container") {
    REQUIRE_NOTHROW(
        container.AddAccount("NewAccount", "NewUsername", "NewPassword"));

    SECTION("Account name is correct") {
      REQUIRE(container.GetAccounts()[0].account_name == "NewAccount");
    }

    SECTION("Username is correct") {
      REQUIRE(container.GetAccounts()[0].account_name == "NewAccount");
    }

    SECTION("Password is correct") {
      REQUIRE(container.GetAccounts()[0].account_name == "NewAccount");
    }
  }

  ifstream file("../../../tests/resources/Data.pwords");
  file >> container;

  SECTION("Adds account to container with values") {
    REQUIRE_NOTHROW(
        container.AddAccount("NewAccount", "NewUsername", "NewPassword"));

    SECTION("Doesn't change previous data") {
      REQUIRE(HasValidData(container));
    }

    SECTION("New Account name is correct") {
      REQUIRE(container.GetAccounts()[3].account_name == "NewAccount");
    }

    SECTION("New Username is correct") {
      REQUIRE(container.GetAccounts()[3].account_name == "NewAccount");
    }

    SECTION("New Password is correct") {
      REQUIRE(container.GetAccounts()[3].account_name == "NewAccount");
    }
  }

  SECTION("Throws error when adding invalid accounts") {
    SECTION("Account with the passed in name already exists") {
      REQUIRE_THROWS_AS(container.AddAccount("Account1", "user", "pass"),
                        std::invalid_argument);
    }

    SECTION("Account with empty name throws error") {
      REQUIRE_THROWS_AS(container.AddAccount("", "user", "pass"),
                        std::invalid_argument);
    }

    SECTION("Account with empty username throws error") {
      REQUIRE_THROWS_AS(container.AddAccount("acc_name", "", "pass"),
                        std::invalid_argument);
    }

    SECTION("Account with empty password throws error") {
      REQUIRE_THROWS_AS(container.AddAccount("acc_name", "user", ""),
                        std::invalid_argument);
    }
  }
}

TEST_CASE("Tests for DeleteAccount") {
  PasswordContainer container(100, "CorrectKey");

  SECTION("Throws error when deleting account from empty container") {
    REQUIRE_THROWS_AS(container.DeleteAccount("Account1"),
                      std::invalid_argument);
  }

  ifstream file("../../../tests/resources/Data.pwords");
  file >> container;

  SECTION("Deletes account from container with values") {
    REQUIRE_NOTHROW(container.DeleteAccount("Account1"));

    SECTION("Correct number of accounts in container") {
      REQUIRE(container.GetAccounts().size() == 2);
    }

    SECTION("Remaining account names are correct") {
      REQUIRE(container.GetAccounts()[0].account_name == "Account2");
      REQUIRE(container.GetAccounts()[1].account_name == "Account3");
    }

    SECTION("Remaining usernames are correct") {
      REQUIRE(container.GetAccounts()[0].username == "Username2");
      REQUIRE(container.GetAccounts()[1].username == "Username3");
    }

    SECTION("Remaining passwords are correct") {
      REQUIRE(container.GetAccounts()[0].password == "Password2");
      REQUIRE(container.GetAccounts()[1].password == "Password3");
    }
  }

  SECTION("Throws error when deleting invalid accounts") {
    SECTION("Account with the passed in name doesn't exists") {
      REQUIRE_THROWS_AS(container.DeleteAccount("RandomUsername"),
                        std::invalid_argument);
    }

    SECTION("Account with empty name throws error") {
      REQUIRE_THROWS_AS(container.DeleteAccount(""), std::invalid_argument);
    }
  }
}

TEST_CASE("Tests for ModifyAccount") {
  PasswordContainer container(100, "CorrectKey");

  SECTION("Throws error when Modifying account from empty container") {
    REQUIRE_THROWS_AS(container.ModifyAccount("Account1", "NewUser", "NewPass"),
                      std::invalid_argument);
  }

  ifstream file("../../../tests/resources/Data.pwords");
  file >> container;

  SECTION("Modifies account from container with values") {
    REQUIRE_NOTHROW(container.ModifyAccount("Account1", "NewUser", "NewPass"));

    SECTION("Correct number of accounts in container") {
      REQUIRE(container.GetAccounts().size() == 3);
    }

    SECTION("Changed account name is correct") {
      REQUIRE(container.GetAccounts()[0].account_name == "Account1");
    }

    SECTION("Remaining usernames are correct") {
      REQUIRE(container.GetAccounts()[0].username == "NewUser");
    }

    SECTION("Remaining passwords are correct") {
      REQUIRE(container.GetAccounts()[0].password == "NewPass");
    }
  }

  SECTION("Throws error when Modifying invalid accounts") {
    SECTION("Account with the passed in name doesn't exists") {
      REQUIRE_THROWS_AS(container.DeleteAccount("RandomUsername"),
                        std::invalid_argument);
    }

    SECTION("Account with empty name throws error") {
      REQUIRE_THROWS_AS(container.ModifyAccount("", "user", "pass"),
                        std::invalid_argument);
    }

    SECTION("Account with empty username throws error") {
      REQUIRE_THROWS_AS(container.ModifyAccount("name", "", "pass"),
                        std::invalid_argument);
    }

    SECTION("Account with empty password throws error") {
      REQUIRE_THROWS_AS(container.ModifyAccount("name", "", "pass"),
                        std::invalid_argument);
    }
  }
}

TEST_CASE("Tests for HasAccount") {
  PasswordContainer container(100, "CorrectKey");
  ifstream file("../../../tests/resources/Data.pwords");
  file >> container;

  SECTION("Returns true when the container has the account") {
    REQUIRE(container.HasAccount("Account1"));
  }

  SECTION("Returns false when the container doesn't have the account") {
    REQUIRE_FALSE(container.HasAccount("RandomAccount"));
  }
}

TEST_CASE("Tests for FindAccount") {
  PasswordContainer container(100, "CorrectKey");
  ifstream file("../../../tests/resources/Data.pwords");
  file >> container;

  SECTION("Returns correct element iterator for account that exists") {
    PasswordContainer::AccountDetails account =
        *container.FindAccount("Account1");
    REQUIRE(account.account_name == "Account1");
    REQUIRE(account.username == "Username1");
    REQUIRE(account.password == "Password1");
  }
}