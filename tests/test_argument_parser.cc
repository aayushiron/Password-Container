#include <catch2/catch.hpp>

#include "cli/argument_parser.h"
#include "cli/command_line_input.h"

#include <iostream>

using passwordcontainer::cli::CommandLineInput;
using passwordcontainer::PasswordContainer;
using namespace passwordcontainer::cli::argumentparser;

// Code to create simulated argv found here:
// https://stackoverflow.com/questions/39883433/create-argc-argv-in-the-code
TEST_CASE("Tests for CreateCommandLineInput") {
  SECTION("Throws error if the file location is missing") {
    char* argument[] = {
        (char*)"./password_container_main.exe",
        (char*)"CorrectKey",
        NULL
    };
    REQUIRE_THROWS_AS(CreateCommandLineInput(2, argument, std::cin, std::cout),
                      std::invalid_argument);
  }

  SECTION("Throws error if the key is missing") {
    char* argument[] = {
        (char*)"./password_container_main.exe",
        (char*)"../../../tests/resources/Data.pwords",
        NULL
    };
    REQUIRE_THROWS_AS(CreateCommandLineInput(2, argument, std::cin, std::cout),
                      std::invalid_argument);
  }

  SECTION("Throws error if the key and location is missing") {
    char* argument[] = {
        (char*)"./password_container_main.exe",
        NULL
    };
    REQUIRE_THROWS_AS(CreateCommandLineInput(1, argument, std::cin, std::cout),
                      std::invalid_argument);
  }

  SECTION("Throws error if an extra argument is passed in") {
    char* argument[] = {
        (char*)"./password_container_main.exe",
        (char*)"../../../tests/resources/Data.pwords",
        (char*)"CorrectKey",
        (char*)"ExtraCommand",
        NULL
    };
    REQUIRE_THROWS_AS(CreateCommandLineInput(4, argument, std::cin, std::cout),
                      std::invalid_argument);
  }

  SECTION("Throws error if the key and file location arguments are swapped") {
    char* argument[] = {
        (char*)"./password_container_main.exe",
        (char*)"CorrectKey",
        (char*)"../../../tests/resources/Data.pwords",
        NULL
    };
    REQUIRE_THROWS_AS(CreateCommandLineInput(3, argument, std::cin, std::cout),
                      std::invalid_argument);
  }

  SECTION("Throws error if the file location doesn't exist") {
    char* argument[] = {
        (char*)"./password_container_main.exe",
        (char*)"InvalidPath",
        (char*)"CorrectKey",
        NULL
    };
    REQUIRE_THROWS_AS(CreateCommandLineInput(3, argument, std::cin, std::cout),
                      std::invalid_argument);
  }

  SECTION("Throws error if the file data is bad") {
    char* argument[] = {
        (char*)"./password_container_main.exe",
        (char*)"../../../tests/resources/BadData.pwords",
        (char*)"CorrectKey",
        NULL
    };
    REQUIRE_THROWS_AS(CreateCommandLineInput(3, argument, std::cin, std::cout),
                      std::invalid_argument);
  }

  SECTION("Throws error if the key is incorrect") {
    char* argument[] = {
        (char*)"./password_container_main.exe",
        (char*)"../../../tests/resources/Data.pwords",
        (char*)"11037",
        NULL
    };
    REQUIRE_THROWS_AS(CreateCommandLineInput(3, argument, std::cin, std::cout),
                      std::invalid_argument);
  }

  SECTION("Creates a cli with correct information if arguments are correct") {
    char* argument[] = {
        (char*)"./password_container_main.exe",
        (char*)"../../../tests/resources/Data.pwords",
        (char*)"CorrectKey",
        NULL
    };
    CommandLineInput input = CreateCommandLineInput(2, argument,
                                                    std::cin, std::cout);
    PasswordContainer container = input.GetContainer();

    REQUIRE(container.GetAccounts().size() == 3);
    REQUIRE(container.GetAccounts()[0].account_name == "Account1");
    REQUIRE(container.GetAccounts()[0].username == "Username1");
    REQUIRE(container.GetAccounts()[0].password == "Password1");

    REQUIRE(container.GetAccounts()[1].account_name == "Account2");
    REQUIRE(container.GetAccounts()[1].username == "Username2");
    REQUIRE(container.GetAccounts()[1].password == "Password2");

    REQUIRE(container.GetAccounts()[2].account_name == "Account3");
    REQUIRE(container.GetAccounts()[2].username == "Username3");
    REQUIRE(container.GetAccounts()[2].password == "Password3");
  }
}