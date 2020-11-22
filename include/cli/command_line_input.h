#ifndef CLI_COMMAND_LINE_INPUT_H
#define CLI_COMMAND_LINE_INPUT_H

#include <iostream>
#include <string>

#include "core/password_container.h"

namespace passwordcontainer {

namespace cli {

// Class that handles input from an input source and outputs data to an output
// source. Has commands to add data, accounts, delete accounts, modify accounts,
// and display the contents currently in the container. The container cannot be
// edited until the correct key is entered. Allows the key to be changed once
// decrypted and also allows the container to be saved.
class CommandLineInput {
 public:
  // Creates a new CommandLineInput object.
  //
  // Takes in an istream called user_input that represents the istream used to
  // get user input data and an ostream called user_output that represents the
  // output for the cli output. Also takes in a string called container_location
  // that represents the file that the container data is stored and a string
  // called key that represents the key used to decrypt the string.
  //
  // Throws an invalid_argument exception if the container_location does not
  // exist or has invalid data. Also throws an invalid_argument exception if the
  // key is invalid.
  CommandLineInput(std::istream& user_input, std::ostream& user_output,
                   const std::string& container_location,
                   const std::string& key);

  ~CommandLineInput();

  // Prompts the user for input and handles the input accordingly.
  void HandleMultipleCommands();

  // Handles a single command from the user. Returns false if the game is user
  // indicates they want to quit and true if not.
  bool HandleSingleCommand();

  // Returns the password container (Method used for tests).
  PasswordContainer GetContainer() const;

 private:
  const size_t kDefaultOffset = 100;

  // The input and output streams for the user input.
  std::istream& user_input_;
  std::ostream& user_output_;

  // The file location of the container
  std::string container_location_;

  // The container used to store the data.
  PasswordContainer* container_ = nullptr;

  // Constants for the many possible user commands
  const std::string kAddCommand = "add";
  const std::string kDeleteCommand = "delete";
  const std::string kModifyCommand = "modify";
  const std::string kListCommand = "list accounts";
  const std::string kShowDetailsCommand = "show details";
  const std::string kGeneratePassCommand = "generate password";
  const std::string kKeyChangeCommand = "change key";
  const std::string kSaveCommand = "save";
  const std::string kQuitCommand = "quit";

  // Loads the container from the location specified in the container_location_
  // string. Uses the key passed into the function to load the container.
  // Throws an invalid_argument exception if there is no file at
  // container_location_ or if the data is bad or if the passed in key is
  // invalid.
  void LoadContainer(const std::string& key);

  // Saves the container to the location specified in the container_location_
  // string. Throws an invalid_argument exception if container_location_ is an
  // invalid path.
  void SaveContainer();

  // Parses the passed in command and calls the correct function to handle the
  // action stated in the command.
  void ParseCommand(const std::string& command);

  // Adds the account by asking the user for the required data.
  void AddSpecifiedAccount();

  // Deletes the account by asking the user for the required data.
  void DeleteSpecifiedAccount();

  // Modifies the account that is found by asking the user for the required
  // data.
  void ModifySpecifiedAccount();

  // Displays all the accounts in the container.
  void ListAccounts();

  // Shows the username and password for the requested account
  void ShowAccountDetails();

  // Changes the key in the container to the value passed in by the user.
  void ChangeContainerKey();

  // Generates a random password with the size of the value passed in by user.
  void GeneratePassword();

  // Indicates that the inputted command was invalid.
  void IndicateInvalidCommand();

  // Prompts user for input using the passed in prompt string and returns the
  // input. Prompts user again for empty input.
  std::string PromptForInput(const std::string& prompt);
};

}  // namespace cli

}  // namespace passwordcontainer

#endif  // CLI_COMMAND_LINE_INPUT_H