#ifndef CLI_ARGUMENT_PARSER_H
#define CLI_ARGUMENT_PARSER_H

#include "cli/command_line_input.h"

#include <iostream>

namespace passwordcontainer {

namespace cli {

namespace argumentparser {

// Method that creates a command line input object. Expects the filepath of the
// save file for the PasswordContainer followed by the key used to decrypt the
// contents of that save file.
//
// Takes in an int called argc that represents the number of command line
// arguments and a char* argv[] that represents the contents of the command
// line arguments. Also takes in an istream called input and an ostream called
// output that represents the input and output streams used by the
// CommandLineInput.
//
// Throws an invalid_argument exception if the passed in command line arguments
// are not matching expectations.
CommandLineInput& CreateCommandLineInput(int argc, char* argv[],
                                         std::istream& input, std::ostream& output);

}

}

}

#endif  // CLI_ARGUMENT_PARSER_H
