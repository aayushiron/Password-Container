#include "core/password_container.h"

#include <sstream>

#include "core/util.h"

using std::string;
using std::vector;

namespace passwordcontainer {

PasswordContainer::PasswordContainer(size_t offset, const string& key)
    : cryptographer_(offset, key) {
}

vector<PasswordContainer::AccountDetails> PasswordContainer::GetAccounts()
    const {
  return accounts_;
}

void PasswordContainer::SetCryptographerKey(const std::string& new_key) {
  cryptographer_.SetKey(new_key);
}

string PasswordContainer::GetCryptographerKey() const {
  return cryptographer_.GetKey();
}

void PasswordContainer::SetCryptographerOffset(size_t offset) {
  cryptographer_.SetOffset(offset);
}

void PasswordContainer::AddAccount(const string& account_name,
                                   const string& username,
                                   const string& password) {
  if (HasAccount(account_name)) {
    throw std::invalid_argument("Account already in container!");
  }

  if (account_name.empty() || username.empty() || password.empty()) {
    throw std::invalid_argument("Please pass in valid account information!");
  }

  // Creates and adds the new account to the rest of the accounts
  AccountDetails new_account;
  new_account.account_name = account_name;
  new_account.username = username;
  new_account.password = password;
  accounts_.push_back(new_account);
}

void PasswordContainer::DeleteAccount(const string& account_name) {
  if (!HasAccount(account_name)) {
    throw std::invalid_argument("No account with passed in name in container!");
  }

  // Erases the object with the passed in account_name
  auto account_iterator = FindAccount(account_name);
  accounts_.erase(account_iterator);
}

void PasswordContainer::ModifyAccount(const std::string& account_name,
                                      const std::string& username,
                                      const std::string& password) {
  if (!HasAccount(account_name)) {
    throw std::invalid_argument("No account with passed in name in container!");
  }

  if (account_name.empty() || username.empty() || password.empty()) {
    throw std::invalid_argument("Please pass in valid account information!");
  }

  // Changes the username and password of the account with account_name
  auto account = FindAccount(account_name);
  account->username = username;
  account->password = password;
}

std::istream& operator>>(std::istream& input, PasswordContainer& container) {
  // Code to get all data from the input file found here:
  // https://stackoverflow.com/questions/3203452/how-to-read-entire-stream-into-a-stdstring
  string encrypted_string(std::istreambuf_iterator<char>(input), {});
  string decrypted_string =
      container.cryptographer_.DecryptString(encrypted_string);

  container.AddAllData(decrypted_string);

  return input;
}

std::ostream& operator<<(std::ostream& output,
                         const PasswordContainer& container) {
  string data_representation = container.GenerateStringRepresentation();
  output << container.cryptographer_.EncryptString(data_representation);

  return output;
}

string PasswordContainer::GenerateStringRepresentation() const {
  string string_representation;

  // Loops through all accounts and adds their details to the final string
  for (const AccountDetails& account : accounts_) {
    string_representation += account.account_name + '\t' + account.username +
                             '\t' + account.password + '\n';
  }

  // Removes the trailing \n character from the string
  if (string_representation.size() != 0) {
    string_representation.pop_back();
  }

  return string_representation;
}

void PasswordContainer::AddAllData(const string& decrypted_string) {
  std::stringstream decrypted_stream(decrypted_string);
  string current_line;

  // Loops through all lines and adds the data from all of them
  while (getline(decrypted_stream, current_line, '\n')) {
    AddOneAccountData(current_line);
  }
}

void PasswordContainer::AddOneAccountData(const string& line_data) {
  string current_detail;
  std::stringstream line_stream(line_data);
  AccountDetails current_account;  // Creates a new AccountDetails object

  // Loops through all data in the current line
  for (size_t detail_index = 0; detail_index < kNumDetails; detail_index++) {
    // Throws an error if data is missing
    if (!getline(line_stream, current_detail, '\t')) {
      throw std::invalid_argument("Bad data passed in!");
    }

    // Adds the information to the AccountDetails based on what detail the
    // program currently is on
    switch (detail_index) {
      case kAccountNameIndex:
        current_account.account_name = current_detail;
        break;
      case kUsernameIndex:
        current_account.username = current_detail;
        break;
      case kPasswordIndex:
        current_account.password = current_detail;
        break;
    }
  }

  accounts_.push_back(current_account);
}

bool PasswordContainer::HasAccount(const std::string& account_name) {
  // Loops through all accounts and check if the name is equal to account_name
  for (const AccountDetails& account : accounts_) {
    if (account.account_name == account_name) {
      return true;
    }
  }

  return false;
}

std::vector<PasswordContainer::AccountDetails>::iterator
PasswordContainer::FindAccount(const std::string& account_name) {
  for (auto iterator = accounts_.begin(); iterator != accounts_.end();
       iterator++) {
    if (iterator->account_name == account_name) {
      return iterator;
    }
  }

  return accounts_.end();
}

}  // namespace passwordcontainer