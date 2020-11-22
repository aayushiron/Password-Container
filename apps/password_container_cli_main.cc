#include "cli/command_line_input.h"
#include "cli/argument_parser.h"

#include <iostream>

using passwordcontainer::cli::CommandLineInput;

int main(int argc, char* argv[]) {
  try {
    // Creates a new command line input and asks it to get user commands
    CommandLineInput input =
        passwordcontainer::cli::argumentparser::CreateCommandLineInput(argc, argv,
                                                                       std::cin,
                                                                       std::cout);

    input.HandleMultipleCommands();
  } catch (...) {
    // Prints error message and quits application if an error occurs
    std::cout << "An error has occurred! Quitting application!" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}