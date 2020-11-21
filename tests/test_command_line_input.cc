#include <catch2/catch.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "cli/command_line_input.h"

using passwordcontainer::cli::CommandLineInput;
using passwordcontainer::PasswordContainer;
using std::istream;
using std::istringstream;
using std::ostringstream;
using std::ifstream;
using std::string;

bool HasValidData(const PasswordContainer& container) {
  std::vector<PasswordContainer::AccountDetails> accounts =
      container.GetAccounts();

  bool correct_first_account = accounts[0].name == "Account1" &&
                               accounts[0].username == "Username1" &&
                               accounts[0].password == "Password1";

  bool correct_second_account = accounts[1].name == "Account2" &&
                                accounts[1].username == "Username2" &&
                                accounts[1].password == "Password2";

  bool correct_third_account = accounts[2].name == "Account3" &&
                               accounts[2].username == "Username3" &&
                               accounts[2].password == "Password3";

  return correct_first_account && correct_second_account && correct_third_account;
}

TEST_CASE("Tests for Constructor") {
  SECTION("Throws error when the file path for the container doesn't exist") {
    REQUIRE_THROWS_AS(CommandLineInput(std::cin, std::cout, "InvalidPath", "CorrectKey"),
                      std::invalid_argument);
  }

  SECTION("Throws error when the passed in file has bad data") {
    REQUIRE_THROWS_AS(CommandLineInput(std::cin, std::cout, "../../../tests/resources/BadData.pwords", "CorrectKey"),
                      std::invalid_argument);
  }

  SECTION("Throws error when the passed in key is not correct") {
    REQUIRE_THROWS_AS(CommandLineInput(std::cin, std::cout, "../../../tests/resources/Data.pwords", "key"),
                      std::invalid_argument);
  }

  SECTION("Constructor gets correct values when passed in data is correct") {
    CommandLineInput input = CommandLineInput(std::cin,std::cout,
                                              "../../../tests/resources/Data.pwords",
                                              "CorrectKey");

    REQUIRE(HasValidData(input.GetContainer()));
  }
}

TEST_CASE("Tests for HandleSingleCommand with an empty container") {
  std::stringstream input;
  std::stringstream output;
  CommandLineInput cli = CommandLineInput(input,output,
                                            "../../../tests/resources/BlankData.pwords",
                                            "CorrectKey");

  SECTION("Add command correctly adds account in empty container") {
    input << "add\n"
             "Account1\n"
             "Username1\n"
             "Password1\n";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(cli.GetContainer().GetAccounts().size() == 1);
    REQUIRE(cli.GetContainer().GetAccounts()[0].name == "Account1");
    REQUIRE(cli.GetContainer().GetAccounts()[0].username == "Username1");
    REQUIRE(cli.GetContainer().GetAccounts()[0].password == "Password1");
  }

  SECTION("Delete command shows error message in empty container") {
    input << "delete\n"
             "Account1";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(output.str() == "Please enter the Account Name: "
                            "That account does not exist!");
    REQUIRE(cli.GetContainer().GetAccounts().size() == 0);
  }

  SECTION("Modify command shows error message in empty container") {
    input << "modify\n"
             "Account1";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(output.str() == "Please enter the Account Name: "
                            "That account does not exist!");
    REQUIRE(cli.GetContainer().GetAccounts().size() == 0);
  }

  SECTION("List accounts command returns empty string") {
    input << "list accounts\n";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(output.str() == "\n");
    REQUIRE(cli.GetContainer().GetAccounts().size() == 0);
  }

  SECTION("Show account details command shows error message in empty container") {
    input << "show details\n"
             "Account1";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(output.str() == "Please enter the Account Name: "
                            "That account does not exist!");
    REQUIRE(cli.GetContainer().GetAccounts().size() == 0);
  }

  SECTION("Save command saves empty string to file") {
    input << "save\n";
    REQUIRE(cli.HandleSingleCommand());

    std::ifstream save_file("../../../tests/resources/BlankData.pwords");
    // Code to get all data from the input file found here:
    // https://stackoverflow.com/questions/3203452/how-to-read-entire-stream-into-a-stdstring
    string file_data(std::istreambuf_iterator<char>(save_file), {});
    REQUIRE(file_data == "");
  }

  SECTION("Save command saves empty string to file") {
    input << "change key\nNewKey";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(cli.GetContainer().GetKey() == "NewKey");
  }

  SECTION("Quit command returns false") {
    input << "quit\n";
    REQUIRE_FALSE(cli.HandleSingleCommand());
  }
}

TEST_CASE("Tests for HandleSingleCommand with a populated container") {
  std::stringstream input;
  std::stringstream output;
  CommandLineInput cli = CommandLineInput(input,output,
                                          "../../../tests/resources/Data.pwords",
                                          "CorrectKey");

  SECTION("Add command correctly adds account in populated container") {
    input << "add\n"
             "Account4\n"
             "Username4\n"
             "Password4\n";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(cli.GetContainer().GetAccounts().size() == 4);
    REQUIRE(cli.GetContainer().GetAccounts()[3].name == "Account4");
    REQUIRE(cli.GetContainer().GetAccounts()[3].username == "Username4");
    REQUIRE(cli.GetContainer().GetAccounts()[3].password == "Password4");
  }

  SECTION("Delete command deletes account in populated container") {
    input << "delete\n"
             "Account1";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(cli.GetContainer().GetAccounts().size() == 2);
    REQUIRE(cli.GetContainer().GetAccounts()[0].name == "Account2");
    REQUIRE(cli.GetContainer().GetAccounts()[0].username == "Username2");
    REQUIRE(cli.GetContainer().GetAccounts()[0].password == "Password2");

    REQUIRE(cli.GetContainer().GetAccounts()[1].name == "Account3");
    REQUIRE(cli.GetContainer().GetAccounts()[1].username == "Username3");
    REQUIRE(cli.GetContainer().GetAccounts()[1].password == "Password3");
  }

  SECTION("Modify command modifies account in populated container") {
    input << "modify\n"
             "Account1\n"
             "NewUsername\n"
             "NewPassword\n";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(cli.GetContainer().GetAccounts().size() == 3);
    REQUIRE(cli.GetContainer().GetAccounts()[0].name == "Account1");
    REQUIRE(cli.GetContainer().GetAccounts()[0].username == "NewUsername");
    REQUIRE(cli.GetContainer().GetAccounts()[0].password == "NewPassword");

    REQUIRE(cli.GetContainer().GetAccounts()[1].name == "Account2");
    REQUIRE(cli.GetContainer().GetAccounts()[1].username == "Username2");
    REQUIRE(cli.GetContainer().GetAccounts()[1].password == "Password2");

    REQUIRE(cli.GetContainer().GetAccounts()[2].name == "Account3");
    REQUIRE(cli.GetContainer().GetAccounts()[2].username == "Username3");
    REQUIRE(cli.GetContainer().GetAccounts()[2].password == "Password3");
  }

  SECTION("List accounts lists out all accounts") {
    input << "list accounts\n";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(output.str() == "Account1\n"
                            "Account2\n"
                            "Account3\n\n");
  }

  SECTION("Show account details command shows error message in empty container") {
    input << "show details\n"
             "Account1\n";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(output.str() == "Please enter the Account Name: "
                            "Username: Username1\n"
                            "Password: Password1\n\n");
  }

  SECTION("Save command saves encrypted string to file") {
    input << "save\n";
    REQUIRE(cli.HandleSingleCommand());

    std::ifstream save_file("../../../tests/resources/BlankData.pwords");
    // Code to get all data from the input file found here:
    // https://stackoverflow.com/questions/3203452/how-to-read-entire-stream-into-a-stdstring
    string file_data(std::istreambuf_iterator<char>(save_file), {});

    string correct_data = "2663003003123183113172502102863163023153112983103022"
                          "5021028129831631632031231530125021126630030031231831"
                          "1317251210286316302315311298310302251210281298316316"
                          "3203123153012512112663003003123183113172522102863163"
                          "02315311298310302252210281298316316320312315301252";

    REQUIRE(file_data == correct_data);
  }

  SECTION("Change key commands correctly changes the key") {
    input << "change key\nNewKey";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(cli.GetContainer().GetKey() == "NewKey");
  }

  SECTION("Quit command returns false") {
    input << "quit\n";
    REQUIRE_FALSE(cli.HandleSingleCommand());
  }
}

TEST_CASE("Tests for HandleSingleCommand with invalid commands") {
  std::stringstream input;
  std::stringstream output;
  CommandLineInput cli = CommandLineInput(input,output,
                                          "../../../tests/resources/Data.pwords",
                                          "CorrectKey");
  
  SECTION("Invalid Command passed in") {
    input << "invalid command\n";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(output.str() == "Invalid Command!\n\n");
  }
  
  SECTION("Only accepts non-empty strings for main command parameters") {
    input << "\n"
             "\n"
             "quit\n";
    REQUIRE_FALSE(cli.HandleSingleCommand());
  }

  SECTION("Only accepts non-empty strings for add command parameters") {
    input << "add\n"
             "\n"
             "Account4\n"
             "\n"
             "Username4\n"
             "\n"
             "Password4\n";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(cli.GetContainer().GetAccounts().size() == 4);
    REQUIRE(cli.GetContainer().GetAccounts()[3].name == "Account4");
    REQUIRE(cli.GetContainer().GetAccounts()[3].username == "Username4");
    REQUIRE(cli.GetContainer().GetAccounts()[3].password == "Password4");
  }

  SECTION("Only accepts non-empty strings for delete command parameters") {
    input << "delete\n"
             "\n"
             "Account1\n";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(cli.GetContainer().GetAccounts().size() == 2);
  }

  SECTION("Only accepts non-empty strings for modify command parameters") {
    input << "modify\n"
             "\n"
             "Account1\n"
             "\n"
             "NewUsername\n"
             "\n"
             "NewPassword\n";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(cli.GetContainer().GetAccounts().size() == 3);
    REQUIRE(cli.GetContainer().GetAccounts()[0].name == "Account1");
    REQUIRE(cli.GetContainer().GetAccounts()[0].username == "NewUsername");
    REQUIRE(cli.GetContainer().GetAccounts()[0].password == "NewPassword");
  }

  SECTION("Show account details command shows error message in empty container") {
    input << "show details\n"
             "\n"
             "Account1\n";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(output.str() == "Please enter the Account Name: "
                            "Username: Username1\n"
                            "Password: Password1\n\n");
  }

  SECTION("Change key commands correctly changes the key") {
    input << "change key\n"
             "\n"
             "NewKey\n";
    REQUIRE(cli.HandleSingleCommand());

    REQUIRE(cli.GetContainer().GetKey() == "NewKey");
  }
}