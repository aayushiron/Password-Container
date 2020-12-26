#include "cli/argument_parser.h"

namespace passwordcontainer {

namespace cli {

namespace argumentparser {

CommandLineInput CreateCommandLineInput(int argc, char* argv[],
                                        std::istream& input,
                                        std::ostream& output) {
  // Checks that the right number of arguments are being passed in
  if (argc != kNumArguments) {
    output << "Invalid number of arguments passed in!" << std::endl;
    throw std::invalid_argument("Incorrect number of arguments passed in!");
  }

  // Tries to create a new command line input but throws an error if the
  // command line input had an error
  try {
    return CommandLineInput(input, output, argv[1], argv[2]);
  } catch (std::invalid_argument& e) {
    output << "Bad arguments passed in!" << std::endl;
    throw e;
  }
}

}  // namespace argumentparser

}  // namespace cli

}  // namespace passwordcontainer