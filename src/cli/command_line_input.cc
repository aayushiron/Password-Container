#include "cli/command_line_input.h"

#include <fstream>

#include "core/util.h"

using std::string;

namespace passwordcontainer {

namespace cli {

CommandLineInput::CommandLineInput(std::istream& user_input,
                                   std::ostream& user_output,
                                   const string& container_location,
                                   const string& key)
    : user_input_(user_input),
      user_output_(user_output),
      container_location_(container_location) {
  LoadContainer(key);
}

CommandLineInput::~CommandLineInput() {
  if (container_ != nullptr)
    delete container_;
}

void CommandLineInput::HandleMultipleCommands() {
  // Stays in an infinite loop until the user wants to quit
  while (HandleSingleCommand()) {
  }

  user_output_ << "Goodbye!" << std::endl;
}

bool CommandLineInput::HandleSingleCommand() {
  // Gets the user input and converts it to lowercase
  string command = PromptForInput("> ");
  command = util::ConvertToLowerCase(command);

  if (command == kQuitCommand) {
    return false;
  } else {
    ParseCommand(command);
  }

  return true;
}

PasswordContainer CommandLineInput::GetContainer() const {
  return *container_;
}

void CommandLineInput::LoadContainer(const std::string& key) {
  container_ = new PasswordContainer(kDefaultOffset, key);

  // Creates a new istream to read data from
  std::ifstream file_input(container_location_);

  // Makes sure the file actually exists
  if (!file_input.is_open()) {
    throw std::invalid_argument("There is no file in the passed in location!");
  }

  file_input >> *container_;
}

void CommandLineInput::SaveContainer() {
  std::ofstream file_output(container_location_);

  // Makes sure container_location_ actually exists
  if (!file_output.is_open()) {
    throw std::invalid_argument("The passed location doesn't exist!");
  }

  file_output << *container_;
}

void CommandLineInput::ParseCommand(const string& command) {
  // Calls the correct method based on the passed in command
  if (command == kAddCommand) {
    AddSpecifiedAccount();
  } else if (command == kDeleteCommand) {
    DeleteSpecifiedAccount();
  } else if (command == kModifyCommand) {
    ModifySpecifiedAccount();
  } else if (command == kListCommand) {
    ListAccounts();
  } else if (command == kShowDetailsCommand) {
    ShowAccountDetails();
  } else if (command == kGeneratePassCommand) {
    GeneratePassword();
  } else if (command == kKeyChangeCommand) {
    ChangeContainerKey();
  } else if (command == kSaveCommand) {
    SaveContainer();
  } else {
    IndicateInvalidCommand();
  }
}

void CommandLineInput::AddSpecifiedAccount() {
  // Prompts the user for all the data needed to add a new account
  string account_name = PromptForInput("Please enter the Account Name: ");
  string username = PromptForInput("Please enter the username: ");
  string password = PromptForInput("Please enter the password: ");
  container_->AddAccount(account_name, username, password);

  user_output_ << "The account has been added!" << std::endl << std::endl;
}

void CommandLineInput::DeleteSpecifiedAccount() {
  string account_name = PromptForInput("Please enter the Account Name: ");

  // Makes sure the container really has the account
  if (container_->HasAccount(account_name)) {
    container_->DeleteAccount(account_name);
    user_output_ << "The account has been deleted!" << std::endl << std::endl;
  } else {
    user_output_ << "That account does not exist!" << std::endl << std::endl;
  }
}

void CommandLineInput::ModifySpecifiedAccount() {
  string account_name = PromptForInput("Please enter the Account Name: ");

  // Leaves the function if there is no account with the passed in name
  if (!(container_->HasAccount(account_name))) {
    user_output_ << "That account does not exist!" << std::endl << std::endl;
    return;
  }

  // Gets the new username and password and modifies the account
  string new_username = PromptForInput("Please enter the new username: ");
  string new_password = PromptForInput("Please enter the new password: ");
  container_->ModifyAccount(account_name, new_username, new_password);

  user_output_ << "The account has been modified!" << std::endl << std::endl;
}

void CommandLineInput::ListAccounts() {
  // Lists out all accounts in the container
  for (auto& account : container_->GetAccounts()) {
    user_output_ << account.account_name << std::endl;
  }

  user_output_ << std::endl;
}

void CommandLineInput::ShowAccountDetails() {
  string account_name = PromptForInput("Please enter the account name: ");

  if (container_->HasAccount(account_name)) {
    // Finds the account and prints out the details
    auto account = *(container_->FindAccount(account_name));
    user_output_ << "Username: " << account.username << std::endl;
    user_output_ << "Password: " << account.password << std::endl << std::endl;
  } else {
    user_output_ << "That account does not exist!" << std::endl << std::endl;
  }
}

void CommandLineInput::GeneratePassword() {
  size_t password_size;

  // Keeps prompting for password until a valid integer is passed in.
  while (true) {
    try {
      string input = PromptForInput("Please enter the size of the password: ");
      password_size = static_cast<size_t>(util::ConvertStringToInt(input));
      break;
    } catch (...) {
    }
  }

  user_output_ << util::GenerateRandomPassword(password_size) << std::endl
               << std::endl;
}

void CommandLineInput::ChangeContainerKey() {
  // Gets the new_key from the user
  string new_key = PromptForInput("Please enter the new key: ");
  container_->SetCryptographerKey(new_key);

  user_output_ << "Key Changed!" << std::endl << std::endl;
}

void CommandLineInput::IndicateInvalidCommand() {
  user_output_ << "Invalid Command!" << std::endl << std::endl;
}

string CommandLineInput::PromptForInput(const std::string& prompt) {
  string current_input;

  // Keeps prompting user for input until non-empty input is passed in
  while (current_input.empty()) {
    user_output_ << prompt;
    std::getline(user_input_, current_input);
  }

  return current_input;
}

}  // namespace cli

}  // namespace passwordcontainer